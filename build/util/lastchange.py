#!/usr/bin/env python
# Copyright (c) 2012 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""
lastchange.py -- Chromium revision fetching utility.
"""

from __future__ import print_function

import re
import logging
import argparse
import os
import subprocess
import sys

class VersionInfo(object):
  def __init__(self, revision_id, full_revision_string, timestamp):
    self.revision_id = revision_id
    self.revision = full_revision_string
    self.timestamp = timestamp


def RunGitCommand(directory, command):
  """
  Launches git subcommand.

  Errors are swallowed.

  Returns:
    A process object or None.
  """
  command = ['git'] + command
  # Force shell usage under cygwin. This is a workaround for
  # mysterious loss of cwd while invoking cygwin's git.
  # We can't just pass shell=True to Popen, as under win32 this will
  # cause CMD to be used, while we explicitly want a cygwin shell.
  if sys.platform == 'cygwin':
    command = ['sh', '-c', ' '.join(command)]
  try:
    proc = subprocess.Popen(command,
                            stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE,
                            cwd=directory,
                            shell=(sys.platform=='win32'))
    return proc
  except OSError as e:
    logging.error('Command %r failed: %s' % (' '.join(command), e))
    return None


def FetchGitRevision(directory, git_log_filter):
  """
  Fetch the Git hash (and Cr-Commit-Position if any) for a given directory.

  Errors are swallowed.

  Args:
    git_log_filter: a string to be used for filtering git log result.

  Returns:
    A VersionInfo object or None on error.
  """
  hsh = ''
  git_args = ['log', '-1', '--format=%H %ct']
  if git_log_filter is not None:
    git_args.append('--grep=' + git_log_filter)
  proc = RunGitCommand(directory, git_args)
  if proc:
    output = proc.communicate()[0].strip()
    if proc.returncode == 0 and output:
      hsh, ct = output.split()
    else:
      logging.error('Git error: rc=%d, output=%r' %
                    (proc.returncode, output))
  if not hsh:
    return None
  pos = ''
  proc = RunGitCommand(directory, ['cat-file', 'commit', hsh.decode()])
  if proc:
    output = proc.communicate()[0]
    if proc.returncode == 0 and output:
      for line in reversed(output.splitlines()):
        if line.startswith(b'Cr-Commit-Position:'):
          pos = line.rsplit()[-1].strip()
          break
  return VersionInfo(hsh, '%s-%s' % (hsh, pos), int(ct))


def FetchVersionInfo(directory=None, git_log_filter=None):
  """
  Returns the last change (as a VersionInfo object)
  from some appropriate revision control system.
  """
  version_info = FetchGitRevision(directory, git_log_filter)
  if not version_info:
    version_info = VersionInfo('0', '0', 0)
  return version_info


def GetHeaderGuard(path):
  """
  Returns the header #define guard for the given file path.
  This treats everything after the last instance of "src/" as being a
  relevant part of the guard. If there is no "src/", then the entire path
  is used.
  """
  src_index = path.rfind('src/')
  if src_index != -1:
    guard = path[src_index + 4:]
  else:
    guard = path
  guard = guard.upper()
  return guard.replace('/', '_').replace('.', '_').replace('\\', '_') + '_'


def GetHeaderContents(path, define, version):
  """
  Returns what the contents of the header file should be that indicate the given
  revision.
  """
  header_guard = GetHeaderGuard(path)

  header_contents = """/* Generated by lastchange.py, do not edit.*/

#ifndef %(header_guard)s
#define %(header_guard)s

#define %(define)s "%(version)s"

#endif  // %(header_guard)s
"""
  header_contents = header_contents % { 'header_guard': header_guard,
                                        'define': define,
                                        'version': version }
  return header_contents


def WriteIfChanged(file_name, contents):
  """
  Writes the specified contents to the specified file_name
  iff the contents are different than the current contents.
  Returns if new data was written.
  """
  try:
    old_contents = open(file_name, 'r').read()
  except EnvironmentError:
    pass
  else:
    if contents == old_contents:
      return False
    os.unlink(file_name)
  open(file_name, 'w').write(contents)
  return True


def main(argv=None):
  if argv is None:
    argv = sys.argv

  parser = argparse.ArgumentParser(usage="lastchange.py [options]")
  parser.add_argument("-m", "--version-macro",
                    help="Name of C #define when using --header. Defaults to " +
                    "LAST_CHANGE.",
                    default="LAST_CHANGE")
  parser.add_argument("-o", "--output", metavar="FILE",
                    help="Write last change to FILE. " +
                    "Can be combined with --header to write both files.")
  parser.add_argument("--header", metavar="FILE",
                    help=("Write last change to FILE as a C/C++ header. "
                          "Can be combined with --output to write both files."))
  parser.add_argument("--revision-id-only", action='store_true',
                    help=("Output the revision as a VCS revision ID only (in "
                          "Git, a 40-character commit hash, excluding the "
                          "Cr-Commit-Position)."))
  parser.add_argument("--print-only", action='store_true',
                    help=("Just print the revision string. Overrides any "
                          "file-output-related options."))
  parser.add_argument("-s", "--source-dir", metavar="DIR",
                    help="Use repository in the given directory.")
  parser.add_argument("--filter", metavar="REGEX",
                    help=("Only use log entries where the commit message "
                          "matches the supplied filter regex. Defaults to "
                          "'^Change-Id:' to suppress local commits."),
                    default='^Change-Id:')
  args, extras = parser.parse_known_args(argv[1:])

  logging.basicConfig(level=logging.WARNING)

  out_file = args.output
  header = args.header
  git_log_filter=args.filter

  while len(extras) and out_file is None:
    if out_file is None:
      out_file = extras.pop(0)
  if extras:
    sys.stderr.write('Unexpected arguments: %r\n\n' % extras)
    parser.print_help()
    sys.exit(2)

  if args.source_dir:
    src_dir = args.source_dir
  else:
    src_dir = os.path.dirname(os.path.abspath(__file__))

  version_info = FetchVersionInfo(directory=src_dir,
                                  git_log_filter=git_log_filter)
  revision_string = version_info.revision
  if args.revision_id_only:
    revision_string = version_info.revision_id

  if args.print_only:
    print(revision_string)
  else:
    contents = "LASTCHANGE=%s\n" % revision_string
    if not out_file and not args.header:
      sys.stdout.write(contents)
    else:
      if out_file:
        committime_file = out_file + '.committime'
        out_changed = WriteIfChanged(out_file, contents)
        if out_changed or not os.path.exists(committime_file):
          with open(committime_file, 'w') as timefile:
            timefile.write(str(version_info.timestamp))
      if header:
        WriteIfChanged(header,
                       GetHeaderContents(header, args.version_macro,
                                         revision_string))

  return 0


if __name__ == '__main__':
  sys.exit(main())
