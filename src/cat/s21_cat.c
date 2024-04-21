#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int index_file;
  flags _flags = read_flags(argc, argv, &index_file);
  if (!_flags.error) {
    for (int i = index_file; i < argc; i++) {
      functions(argv[i], _flags);
    }
  } else {
    printf("usage: cat [-benstuv] [file ...]");
  }

  return 0;
}

flags read_flags(int argc, char *argv[], int *index_file) {
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {NULL, 0, NULL, 0}};

  int current_flag = getopt_long(argc, argv, "bevEnstT", long_options, NULL);
  flags _flags = {0, 0, 0, 0, 0, 0, 0};
  for (; current_flag != -1;
       current_flag = getopt_long(argc, argv, "bevEnstT", long_options, NULL)) {
    switch (current_flag) {
      case 'b':
        _flags.b = 1;
        break;
      case 'e':
        _flags.e = 1;
        _flags.v = 1;
        break;
      case 'v':
        _flags.v = 1;
        break;
      case 'E':
        _flags.e = 1;
        break;
      case 'n':
        _flags.n = 1;
        break;
      case 's':
        _flags.s = 1;
        break;
      case 't':
        _flags.t = 1;
        _flags.v = 1;
        break;
      case 'T':
        _flags.t = 1;
        break;
      default:
        _flags.error = 1;
        break;
    }
  }
  *index_file = optind;
  return _flags;
}

void functions(char *name, flags _flags) {
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    int symbol = fgetc(file);
    int numbers = 1;
    int past_symbol = '\n';
    int past_symbol2 = '0';

    while (symbol != EOF) {
      int x = 0;
      if (_flags.s) cat_s(&symbol, &past_symbol, &past_symbol2, file, &x);
      if (x != 0) continue;
      if (_flags.b) cat_b(symbol, past_symbol, &numbers);
      if (_flags.n && !_flags.b) cat_n(past_symbol, &numbers);
      if (_flags.t) cat_t(&symbol);
      if (_flags.v) cat_v(&symbol);
      if (_flags.e && symbol == '\n') {
        printf("$%c", symbol);
      } else {
        putchar(symbol);
      }
      past_symbol2 = past_symbol;
      past_symbol = symbol;
      symbol = fgetc(file);
    }
    fclose(file);
  } else {
    printf("%s: No such file or directory", name);
  }
}

void cat_s(int *symbol, int *past_symbol, int *past_symbol2, FILE *file,
           int *x) {
  if (*past_symbol == '\n' && *symbol == '\n' && *past_symbol2 == '\n') {
    *past_symbol2 = *past_symbol;
    *past_symbol = *symbol;
    *symbol = fgetc(file);
    *x = *x + 1;
  }
}

void cat_b(int symbol, int past_symbol, int *numbers) {
  if (past_symbol == '\n' && symbol != '\n') {
    printf("%6d\t", *numbers);
    *numbers = *numbers + 1;
  }
}

void cat_n(int past_symbol, int *numbers) {
  if (past_symbol == '\n') {
    printf("%6d\t", *numbers);
    *numbers = *numbers + 1;
  }
}

void cat_t(int *symbol) {
  if (*symbol == '\t') {
    putchar('^');
    *symbol = 'I';
  }
}

void cat_v(int *symbol) {
  if (*symbol > 127 && *symbol < 160) {
    printf("M-^");
  }
  if ((*symbol < 32 && *symbol != '\n' && *symbol != '\t') || *symbol == 127) {
    printf("^");
  }
  if ((*symbol < 32 || (*symbol > 126 && *symbol < 160)) && *symbol != '\n' &&
      *symbol != '\t') {
    if (*symbol > 126) {
      *symbol = *symbol - 128 + 64;
    } else {
      *symbol += 64;
    }
  }
}