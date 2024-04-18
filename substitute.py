#!/usr/bin/python3

import sys
import os
import argparse

def terminate(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)
    exit(1)

def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)

parser = argparse.ArgumentParser(description="replaces #substitute \"file\" line with contents of file")
parser.add_argument(
    "-i", "--infile", type=argparse.FileType("r", encoding="UTF-8"), help="input file path, default = stdin", default=sys.stdin
)

parser.add_argument(
    "-o", "--outfile", type=argparse.FileType("w", encoding="UTF-8"), help="output file path, default = stdout", default=sys.stdout
)

args = parser.parse_args()

infile_dirname = os.path.dirname(os.path.abspath(args.infile.name)) if args.infile != sys.stdin else os.getcwd()
eprint("Relative paths in infile will be expanded relative to", infile_dirname)
with args.outfile as outfile, args.infile as infile:
    for line in infile:
        if line.strip().startswith("#substitute "):
            tokens = line.strip().split()
            if len(tokens) != 2:
                outfile.write(line)
                continue
            if tokens[1][0] != '"' or tokens[1][-1] != '"':
                outfile.write(line)
                continue
            file_token = tokens[1][1:-1]
            if not os.path.isabs(file_token):
                file_path = os.path.join(infile_dirname, file_token)
            else:
                file_path = file_token
            eprint("Subsituting", file_path)
            if not os.path.isfile(file_path):
                terminate(f"Failed to open {file_path}")
            with open(file_path, "r") as subs_file:
                outfile.write(subs_file.read())
            outfile.write("\n")
        else:   
            outfile.write(line)