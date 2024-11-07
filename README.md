# SimpleBashUtils

The **SimpleBashUtils** project is a set of text manipulation utilities implemented in the C programming language.The main utilities to be developed within the project include:
- **cat** - for outputting file contents.
- **grep** - for searching strings by pattern in files.

The project is focused on learning the basics of developing command line utilities, as well as using a structured approach to programming.

## Contents
1. [Program Features](#program-features)
    - [cat](#cat)
    - [grep](#grep)
2. [Requirements](#requirements)
2. [Build](#build)
3. [Use](#use) 
3. [Testing](#testing)

## Program Features

### cat

- The `cat` utility has been developed with support for the following flags (including GNU versions):

| № | Options | Description |
|--------|--------|--------|
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines |
| 2 | -e assumes and -v (GNU only: -E is the same, but without -v) | also displays end-of-line characters as $ |
| 3 | -n (GNU: --number) | numbers all output lines |
| 4 | -s (GNU: --squeeze-blank) | compresses multiple adjacent blank lines |
| 5 | -t assumes and -v (GNU: -T is the same but without -v) | also displays tabs as ^I |
- Combinations of flags for the `cat` utility are supported.
- The source, header, and build files are located in src/cat/.
- The final executable file is located in the src/cat/ directory and is called s21_cat


### grep

- The `grep` utility has been developed with support for the following flags:

| № | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | Template |
| 2 | -i | Ignores case differences. |
| 3 | -v | Inverts the meaning of matching. |
| 4 | -c | Outputs only the number of matching strings. |
| 5 | -l | Only displays matching files. |
| 6 | -n | Precedes each line of output with the line number from the input file. |
| 7 | -h | Outputs matching lines without preceding them with file names. |
| 8 | -s | Suppresses error messages about non-existent or unreadable files. |
| 9 | -f file | Retrieves regular expressions from a file. |
| 10 | -o | Prints only matching (non-empty) parts of a matching string. | |
- Supported flag combinations for the `grep` utility
- The regex library is used for regular expressions 
- The source, header and assembly files are located in the src/grep/ directory.
- The final executable is located in the src/grep/ directory and is called s21_grep.

## Requirements

Program Requirements:
- Language: C++17
- Compiler: GCC (GNU Compiler Collection)
- Build system: Makefile
- Libraries: regex

## Build

1. Cloning the repository:
```
git clone https://github.com/llllenivka/SimpleBashUtils
cd SimpleBashUtils
```
2. Build with Makefile:
- cat: Open a terminal in the project directory and run the command:
```
cd src/cat
make
```
- grep: Open a terminal in the project directory and execute the command:
```
cd src/grep
make
```
3. to clear all compiled files:
```
cd src/cat
make clean
cd ...
cd grep
make clean
```

## Use

- cat:
```
./s21_cat [OPTION] [FILE]...
```
- grep:
```
./s21_grep [options] template [file_name]
```
## Testing

- cat:
```
cd src/cat
make test
```
- grep:
```
cd src/grep
make test
```