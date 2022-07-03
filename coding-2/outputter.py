#! /usr/bin/env python3

import sys

file_name = sys.argv[1].replace("input", "output")

with open(file_name) as file:
    for line in file:
        print(line, end="")
