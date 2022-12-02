#Brokkenify

### Introduction
Tired of getting flamed because you forgot to write ++c instead of c++, or you used an int instead of a size_t in a loop?

Fear no more! This program is designed to scan your exercises for anything that does not comply with Brokken's C++ styles.

### How to use
Simply download the python file and run the following in the same directory as your homework set:

    python3 test.py {homework_dir}


### How does it work?
The program is a simple python script that works with regular expressions to check each file. For each rule/abbreviation the file will be scanned again for the given regex. This is a quick and dirty approach that is not efficient, though that should not matter for its use case.

Note that this means that this program cannot catch everything. See [the abbreviations](./abbreviations.md) for more details.


### Similar projects
These are similar projects, though they seem to be unfinished and abandoned:
- https://github.com/pieter/brokkenbundle
- https://github.com/jmdejong/brokkenize

