#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int error;
} flags;

flags read_flags(int argc, char *argv[], int *index_file);
void functions(char *name, flags _flags);
void cat_s(int *symbol, int *past_symbol, int *past_symbol2, FILE *file,
           int *x);
void cat_b(int symbol, int past_symbol, int *numbers);
void cat_n(int past_symbol, int *numbers);
void cat_t(int *symbol);
void cat_v(int *symbol);

#endif