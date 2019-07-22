#!/usr/bin/python

"""Download node library"""

import optparse
import tarfile
import sys
import urllib
import semver

def main(args):
  usage = ('usage: %prog [options] version\n')
  parser = optparse.OptionParser(usage)
  parser.add_option('-v', '--version',
                    help='Specify the version to downlaod.')

if __name__ == '__main__':
  sys.exit(main(sys.argv))
