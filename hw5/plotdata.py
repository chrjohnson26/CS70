#!/usr/bin/python3

# This script reads tab-separated data from standard input and plots it
# using matplotlib.  The first column is assumed to be the x-axis, and
# subsequent columns are plotted as y-values.  Because it is designed to
# to show data about program performance, it is assumed that the x-axis
# is problem size, and the y-axis is time, space, or some other measure
# of performance.  Since how things scale with problem size usually
# matters, the plot is shown on a log-log scale.
#
# The first row of the input is assumed to be a header, and is used to
# label the plot.  The first column is assumed to be the x-axis label
# (although this can be overridden with the --xlabel option).  The
# and subsequent columns are used to label the lines (although this can
# be overridden with the --legend option).

# Usage: ./plotdata.py [options] < data.tsv
#   options:
#     --csv                       input is comma-separated instead of tab-separated
#     --transpose                 transpose the input data
#     --auto-transpose            guess whether to transpose the input data
#     --xlabel=LABEL              override label for the x-axis
#     --ylabel=LABEL              set label for the y-axis
#     --title=TITLE               set title for the plot
#     --legend=LABEL1,LABEL2,...  override labels for the lines
#     --markers                   show the data points as markers
#     --divide-by                 divide all values by this fomula (e.g. n^2)
#     --output=FILENAME           save plot to file instead of showing it
#     --show                      show plot (default if --output not given)
#     --help                      show this message and exit
#     --debug                     print debugging information

# Author: Melissa O'Neill <oneill@cs.hmc.edu>
# License: MIT

# (Keep column width to 80 characters for readability on GitHub.)

import sys
import re  # regular expressions
import argparse
from types import NoneType # option parsing
try:
    import matplotlib.pyplot as plt
except ImportError:
    # Okay, this is crazy, but here's what we do if we don't have matplotlib.
    # We forcibly install it for the user, and then re-run ourselves.
    print("Ooops, matplotlib isn't installed.  Let's fix that...", file=sys.stderr)
    import os
    os.system('pip3 install --user matplotlib')
    print("Okay, let's restart this script and do everything!", file=sys.stderr)
    try:
        os.execv("/usr/bin/python3", ["/usr/bin/python3"] + sys.argv)
    except OSError:
        print("Ooops, I couldn't restart myself.  Please re-run me manually.",
                file=sys.stderr)
    sys.exit(1)
import math
import csv

# Parse command-line options
parser = argparse.ArgumentParser(description='Plot data from standard input '
                                 'on a log-log scale.')
parser.add_argument('--csv', action='store_true',
                    help='input is comma-separated instead of tab-separated')
parser.add_argument('--transpose', action='store_true',
                    help='transpose the input data')
parser.add_argument('--auto-transpose', action='store_true',
                    help='guess whether to transpose the input data')
parser.add_argument('--xlabel', help='override label for the x-axis')
parser.add_argument('--ylabel', help='set label for the y-axis')
parser.add_argument('--title', help='set title for the plot')
parser.add_argument('--legend', help='comma-separated list of labels for lines')
parser.add_argument('--markers', action='store_true', help='show data points '
                    'as markers')
parser.add_argument('--divide-by', help='divide all values by this formula '
                    '(e.g. 1, n, n log n, n^2, etc.)')
parser.add_argument('--output', help='save plot to file instead of showing it')
parser.add_argument('--show', help='show plot (default if --output not given)',
                    action='store_true')
parser.add_argument('--debug', help='print debugging information',
                    action='store_true')
args = parser.parse_args()

# We generate a python function that will divide all values by the
# formula specified on the command line.
#
# We parse only the following formula
#   [SCALE] [n[^POWER]] [log n]
# where SCALE and POWER are floating-point numbers, and n is the x-axis value.
# For example, "n^2" or "1e-6 n log n" or "1".
# At least one of the three parts must be present

# Default to dividing by 1
if args.divide_by is None:
    args.divide_by = '1'

# Parse the formula
floatRE = r'[-+]?(?:\d*\.\d+|\d+)(?:[eE][-+]?\d+)?'
exprRE = (r'(?i)^\s*(?P<scale>' + floatRE + r')?'
          r'(\s*(?P<n>n)(\^(?P<power>' + floatRE + r'))?)?'
          r'(\s*(?P<logn>log\s+n))?\s*$')
if args.debug:
    print('exprRE =', exprRE)
m = re.match(exprRE, args.divide_by)
if args.debug:
    print('m =', m)
if m is None:
    # All the parts are optional so this should never happen
    print('Internal error: could not parse formula', args.divide_by)
    sys.exit(1)

# Extract the parts of the formula
scale = m.group('scale')
n = m.group('n')
power = m.group('power')
logn = m.group('logn')

# At least one of the three parts must be present
if scale is None and n is None and logn is None:
    print('Error: invalid formula for --divide-by: ' + args.divide_by)
    print('expecting [SCALE] [n[^POWER]] [log n], valid examples:')
    print('  n^2, 1e-6 n log n, 1')
    sys.exit(1)

# Generate the python code for the function
expr = ''
if scale is not None:
    expr += scale
if n is not None:
    if scale is not None:
        expr += ' * '
    expr += 'n'
    if power is not None:
        expr += '**' + power
if logn is not None:
    if scale is not None or n is not None:
        expr += ' * '
    expr += 'math.log(n)'
if args.debug:
    print('Dividing by', expr)
code = 'def divide_by(n, v): return v / (' + expr + ')'
if args.debug:
    print('Generated code:', code)
exec(code)
# Essentially, this code dynamically generates a function like this:
# def divide_by(n, v):
#     return v / (scale * n**power * math.log(n))

# Read data from standard input, initially loading it into rawdata, a list of
# lists.  Each sublist is a row of the input data.  We need to handle
# the input being either tab-separated or comma-separated.  Afterwards, we'll
# transpose the data if necessary and deal with any header row present.

rawdata = []
reader = csv.reader(sys.stdin, delimiter=',' if args.csv else '\t')
for row in reader:
    rawdata.append(row)

# For --auto-transpose, we guess whether to transpose the data by looking at
# the first column, specifically, where there ought to be data points.  If
# we don't see data, it can't be x-axis values, so we transpose the data.

if args.auto_transpose:
    # Just look at the second line, since the first line is usually a header
    # row and we don't want to transpose if that's the case.
    try:
        float(rawdata[1][0])
    except ValueError:
        args.transpose = True
    except IndexError:
        # Something is wrong with the input data
        print('Error: input data has no second row', file=sys.stderr)
        sys.exit(1)


# Transpose the data if necessary.

if args.transpose:
    rawdata = list(map(list, zip(*rawdata)))

# If the first row is a header, use it to label the plot and remove it from
# the data.  Otherwise, we'll demand that the user specify the legend labels
# and an x-axis label.
labels = []
if re.match(r'^\D', rawdata[0][0]):
    # We have a header row
    labels = rawdata[0]
    del rawdata[0]
else:
    # No header row
    if args.legend is None or args.xlabel is None:
        print('Error: no header row, so --legend and --xlabel are required',
                file=sys.stderr)
        sys.exit(1)
# Potentially replace the x-axis label with the user's choice
if args.xlabel:
    labels[0] = args.xlabel
# Potentially replace the legend labels with the user's choices
if args.legend:
    labels[1:] = args.legend.split(',')
if args.debug:
    print('labels:', labels)

# Convert the rawdata to floats in a similar list of lists, data, and use 
# our divide_by function to divide all values by the formula specified on 
# the command line.  We issue warnings if any values can't be converted 
# to floats or data is missing.

numcols = len(labels)
if args.debug:
    print('labels:', labels)
    print('numcols:', numcols)

data = [[] for i in range(numcols)]
for row in rawdata:
    for i in range(numcols):
        value = None
        try:
            value = float(row[i])
        except ValueError:
            # Ignore lines with non-numeric values
            if args.debug:
                print('Ignoring unparsable value: ', fields[i])
        except IndexError:
            # Ignore lines with too few columns
            if args.debug:
                print('Column', i, 'is missing')
        if value is None:
            if i == 0:
                # Missing x-axis value, that's a problem
                print('Error: missing x-axis value in row', row, 'raw data:',
                        repr(row[i]), file=sys.stderr)
                sys.exit(1)
            else:
                # Missing y-axis value, just use None, as matplotlib will
                # ignore it
                data[i].append(None)
            continue
        if value is not None:
            # Add to data after dividing by the formula when it isn't the
            # x-axis value
            if i == 0:
                data[0].append(value)
            else:
                xvalue = data[0][-1]
                data[i].append(divide_by(xvalue, value))

# Debugging output
if args.debug:
    for i in range(numcols):
        print('data[{}]:'.format(i), data[i])

# Plot the data on a log-log scale.  We'll also add grid lines to make
# it easier to read the plot, but make them light and dotted so they
# don't obscure the data.

for i in range(1, numcols):
    if args.markers:
        plt.plot(data[0], data[i], ':o', label=labels[i])
    else:
        plt.plot(data[0], data[i], label=labels[i])
plt.xscale('log')
plt.yscale('log')



plt.xlabel(labels[0])
if args.ylabel:
    plt.ylabel(args.ylabel)
if args.title:
    plt.title(args.title)
plt.legend()
plt.grid(True, which='major', linestyle=':')

# Save the plot to a file or show it on the screen.
if args.output:
    plt.savefig(args.output)
if args.show or not args.output:
    plt.show()
