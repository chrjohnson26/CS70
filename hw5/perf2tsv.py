#!/usr/bin/python3

# This Python script takes human-readable performance data from stdin
# and converts it to TSV format on stdout.  It is intended to be used in
# a pipeline with ./listperf which measures the performance of our IntList
# class and the C++ standard library list classes.
#
# usage: ./perf2tsv.py [options] < listperf.out > listperf.tsv
#
# options:
#   -h, --help   show this help message and exit
#   --time       output time data (default)
#   --space      output space data
#   --transpose  rows are sizes, columns are data
#   --csv        output as CSV instead of TSV
#   --divide-by  divide all values by this fomula (e.g. n^2 log n)
#
# You are not required to understand the code in this file, but you are
# welcome to read it and ask questions about it.

import sys
import re
import argparse
import math

# Parse command-line arguments

parser = argparse.ArgumentParser()
parser.add_argument("--time", action="store_true",
                    help="output time data (default)")
parser.add_argument("--space", action="store_true",
                    help="output space data")
parser.add_argument("--transpose", action="store_true",
                    help="rows are sizes, columns are data")
parser.add_argument("--csv", action="store_true",
                    help="output as CSV instead of TSV")
parser.add_argument("--divide-by", type=str,
                    help="divide all values by this fomula (e.g. n^2 log n)")

args = parser.parse_args()

if args.time and args.space:
    print("Error: only one of --time and --space may be specified.")
    sys.exit(1)

if not args.time and not args.space:
    args.time = True

# We generate a python function that will divide all values by the
# formula specified on the command line.
#
# We parse only the following formulas
#   n[^NUMBER] [log n]
# where NUMBER is a positive integer.

if args.divide_by:
    m = re.match(r"n(\^(\d+))?( log n)?", args.divide_by)
    if not m:
        print("Error: invalid --divide-by formula, requires n[^NUMBER] [log n]")
        sys.exit(1)
    if m.group(2):
        exponent = int(m.group(2))
    else:
        exponent = 1
    if m.group(3):
        def divideBy(n):
            return n ** exponent * math.log(n)
    else:
        def divideBy(n):
            return n ** exponent
else:
    def divideBy(n):
        return 1


# Read the input into a list of lines.

lines = sys.stdin.readlines()

# Figure out all the sizes used

sizes = set()
for line in lines:
    match = re.search(r"size (\d+)", line)
    if match:
        sizes.add(int(match.group(1)))

sizes = sorted(sizes)

# We'll store the data in a dictionary mapping from the name of the
# data structure to another dictionary mapping from the size to the
# value.

valueForListKind = {}
listKind = None

# Now read the data into the dictionary.

size = None
for line in lines:
    # Use a regular expression to see if we got a new set of measurements.
    match = re.search(r"^Measuring (.*):", line)
    if match:
        listKind = match.group(1)
        valueForListKind[listKind] = {}
        continue
    # Use a regular expression to extract the size from the line, if present.
    # Otherwise, we'll just keep using the previous size.
    match = re.search(r"size (\d+)", line)
    if match:
        size = int(match.group(1))
    if args.time:
        # Use a regular expression to extract the time from the line, if present.
        # We use a slightly complicated regular expression to match any float
        # value, including scientific notation.
        match = re.search(r"(\d+(\.\d*)?([eE][+-]?\d+)?) µs", line)
        if match:
            time = float(match.group(1))
            if size is None:
                print(f'Error: time value "{time}" on line "{line}" has no size.', file=sys.stderr)
                sys.exit(1)
            valueForListKind[listKind][size] = time
    else: # args.space
        # Use a regular expression to extract the space from the line, if present.

        match = re.search(r"(\d+) bytes", line)
        if match:
            space = int(match.group(1))
            valueForListKind[listKind][size] = space

# Now print the data in TSV or CSV format.

isTSV = not args.csv
tab = "\t" if isTSV else ","

# The names of the data structures and tests may contain commas, so we
# need to quote them when outputting CSV.

def maybeQuote(s):
    if isTSV:
        return s
    else:
        return '"' + s.replace('"', '""') + '"'

if not args.transpose:
    print("Test", tab.join(map(str, sizes)), sep=tab)

    for listKind in valueForListKind:
        print(maybeQuote(listKind), end="")
        for size in sizes:
            divisor = divideBy(size)
            # We may not have data for every size for every data structure.
            # If we don't, just print a blank.
            if size in valueForListKind[listKind]:
                value = valueForListKind[listKind][size] / divisor
                print(tab, value, end="", sep="")
            else:
                print(tab, "-" if isTSV else "", end="", sep="")
        print()

else:  # args.transpose
    kinds = [maybeQuote(listKind) for listKind in valueForListKind]
    print("size", tab.join(kinds), sep=tab)

    for size in sizes:
        print(size, end="")
        divisor = divideBy(size)
        for listKind in valueForListKind:
            # We may not have data for every size for every data structure.
            # If we don't, just print a blank.
            if size in valueForListKind[listKind]:
                value = valueForListKind[listKind][size] / divisor
                print(tab, value, end="", sep="")
            else:
                print(tab, "-" if isTSV else "", end="", sep="")
        print()
