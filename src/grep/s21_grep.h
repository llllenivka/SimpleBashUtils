#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_PATTERN 10000

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int error;
  char pattern[SIZE_PATTERN];
  int count_flags;
} flags;

flags read_flags(int argc, char **argv);
int count_flags(int argc, char *argv[]);
void open_file_for_pattern(char buff[SIZE_PATTERN]);
void matching_line(regex_t *preg, char *line, regmatch_t match, int argc,
                   char *name, int num, flags _flags, int *count);
void not_matching_line(regex_t *preg, char *line, regmatch_t match, int argc,
                       char *name, int num, flags _flags, int *count);
void output_for_o(regmatch_t match, char *line, regex_t *preg, int num,
                  flags _flags);
void reg_comp_for_e_f(flags _flags, char *argv[], int argc, regex_t *preg);
void comp_pattern(int argc, char *argv[], flags _flags, regex_t *preg);
void file_open(char **name, int argc, flags _flags, regex_t *preg);
void grep_functions(int argc, FILE *file, flags _flags, regex_t *preg,
                    char *name);
void output_line(int argc, flags _flags, char *name, char *line, int num);
void output_for_c(int count, int argc, flags _flags, char *name);
void output_for_l(int count, char *name);
void number_line(int num);

#endif