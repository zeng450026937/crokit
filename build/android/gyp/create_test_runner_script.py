#!/usr/bin/env python
#
# Copyright 2015 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Creates a script to run an android test using build/android/test_runner.py.
"""

import argparse
import os
import re
import sys

from util import build_utils

SCRIPT_TEMPLATE = """\
#!/usr/bin/env vpython
#
# This file was generated by build/android/gyp/create_test_runner_script.py

import os
import sys

def main():
  script_directory = os.path.dirname(__file__)

  def ResolvePath(path):
    \"\"\"Returns a normalized filepath given a path relative to this script.
    \"\"\"
    return os.path.normpath(os.path.join(script_directory, path))

  test_runner_path = ResolvePath('{test_runner_path}')
  test_runner_args = {test_runner_args}
  test_runner_path_args = {test_runner_path_args}
  for arg, path in test_runner_path_args:
    test_runner_args.extend([arg, ResolvePath(path)])

  os.execv(test_runner_path,
           [test_runner_path] + test_runner_args + sys.argv[1:])

if __name__ == '__main__':
  sys.exit(main())
"""


def _GenerateAdditionalApksErrorString(incremental_apks):
  err_string = ('Apks that are listed as additional_apks for '
      'another target cannot be incremental. Please add never_incremental to '
      'the following apks: %s')
  return err_string % ', '.join(a for a in incremental_apks)


def main(args):
  parser = argparse.ArgumentParser()
  parser.add_argument('--script-output-path',
                      help='Output path for executable script.')
  parser.add_argument('--test-runner-path',
                      help='Path to test_runner.py (optional).')

  # We need to intercept any test runner path arguments and make all
  # of the paths relative to the output script directory.
  group = parser.add_argument_group('Test runner path arguments.')
  group.add_argument('--additional-apk', action='append',
                     dest='additional_apks', default=[])
  group.add_argument('--additional-apk-list')
  group.add_argument('--additional-apk-incremental', action='append',
                     dest='additional_apks_incremental', default=[])
  group.add_argument('--apk-under-test')
  group.add_argument('--apk-under-test-incremental-install-json')
  group.add_argument('--executable-dist-dir')
  group.add_argument('--isolate-file-path')
  group.add_argument('--output-directory')
  group.add_argument('--runtime-deps-path')
  group.add_argument('--test-apk')
  group.add_argument('--test-jar')
  group.add_argument('--test-apk-incremental-install-json')
  group.add_argument('--coverage-dir')
  group.add_argument('--android-manifest-path')
  group.add_argument('--resource-zips')
  group.add_argument('--robolectric-runtime-deps-dir')
  args, test_runner_args = parser.parse_known_args(
      build_utils.ExpandFileArgs(args))

  def RelativizePathToScript(path):
    """Returns the path relative to the output script directory."""
    return os.path.relpath(path, os.path.dirname(args.script_output_path))

  test_runner_path = args.test_runner_path or os.path.join(
      os.path.dirname(__file__), os.path.pardir, 'test_runner.py')
  test_runner_path = RelativizePathToScript(test_runner_path)

  test_runner_path_args = []
  if args.additional_apk_list:
    args.additional_apks.extend(
        build_utils.ParseGnList(args.additional_apk_list))
  if args.additional_apks:
    test_runner_path_args.extend(
        ('--additional-apk', RelativizePathToScript(a))
        for a in args.additional_apks)
  if args.additional_apks_incremental:
    bad_additional_apks = [a for a in args.additional_apks_incremental
                           if a != 'None']
    if bad_additional_apks:
      raise Exception(_GenerateAdditionalApksErrorString(bad_additional_apks))
  if args.apk_under_test:
    test_runner_path_args.append(
        ('--apk-under-test', RelativizePathToScript(args.apk_under_test)))
  if args.apk_under_test_incremental_install_json:
    test_runner_path_args.append(
        ('--apk-under-test-incremental-install-json',
         RelativizePathToScript(
             args.apk_under_test_incremental_install_json)))
  if args.executable_dist_dir:
    test_runner_path_args.append(
        ('--executable-dist-dir',
         RelativizePathToScript(args.executable_dist_dir)))
  if args.isolate_file_path:
    test_runner_path_args.append(
        ('--isolate-file-path', RelativizePathToScript(args.isolate_file_path)))
  if args.output_directory:
    test_runner_path_args.append(
        ('--output-directory', RelativizePathToScript(args.output_directory)))
  if args.runtime_deps_path:
    test_runner_path_args.append(
        ('--runtime-deps-path', RelativizePathToScript(args.runtime_deps_path)))
  if args.test_apk:
    test_runner_path_args.append(
        ('--test-apk', RelativizePathToScript(args.test_apk)))
  if args.test_jar:
    test_runner_path_args.append(
        ('--test-jar', RelativizePathToScript(args.test_jar)))
  if args.test_apk_incremental_install_json:
    test_runner_path_args.append(
        ('--test-apk-incremental-install-json',
         RelativizePathToScript(args.test_apk_incremental_install_json)))
  if args.coverage_dir:
    test_runner_path_args.append(
        ('--coverage-dir', RelativizePathToScript(args.coverage_dir)))
  if args.android_manifest_path:
    test_runner_path_args.append(
        ('--android-manifest-path',
         RelativizePathToScript(args.android_manifest_path)))
  if args.resource_zips:
    test_runner_path_args.extend(
        ('--resource-zip', RelativizePathToScript(r))
        for r in build_utils.ParseGnList(args.resource_zips))
  if args.robolectric_runtime_deps_dir:
    test_runner_path_args.append(
        ('--robolectric-runtime-deps-dir',
         RelativizePathToScript(args.robolectric_runtime_deps_dir)))

  with build_utils.AtomicOutput(args.script_output_path) as script:
    script.write(SCRIPT_TEMPLATE.format(
        test_runner_path=str(test_runner_path),
        test_runner_args=str(test_runner_args),
        test_runner_path_args=str(test_runner_path_args)))

  os.chmod(args.script_output_path, 0750)


if __name__ == '__main__':
  sys.exit(main(sys.argv[1:]))
