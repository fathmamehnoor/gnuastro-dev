# Create a mock image from cat2.txt:
#
#  - It doesn't have any random profiles, only the large profile from
#    cat1.txt. The central position is set to be on the same real
#    place as in cat1.txt
#
#
# See the Tests subsection of the manual for a complete explanation
# (in the Installing gnuastro section).
#
# Original author:
#     Mohammad Akhlaghi <akhlaghi@gnu.org>
# Contributing author(s):
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty.


# Preliminaries:
################
# Set the variabels (The executable is in the build tree). Do the
# basic checks to see if the executable is made or if the defaults
# file exists (basicchecks.sh is in the source tree).
prog=mkprof
execname=../src/$prog/ast$prog




# If the executable was not made (the user chose to not install this
# package), skip this test:
if [ ! -f $execname ]; then
    exit 77
fi





# Actual test script:
#####################
cat=$topsrc/tests/$prog/mkprofcat3.txt
$execname $cat --naxis1=100 --naxis2=100 --crpix2=-99