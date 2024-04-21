#include "s21_grep.h"

int main(int argc, char *argv[]) {
  flags _flags = read_flags(argc, argv);
  regex_t preg_storage;
  regex_t *preg = &preg_storage;

  _flags.count_flags = count_flags(argc, argv);

  if (!_flags.error && optind < argc) {
    if (_flags.e || _flags.f)
      reg_comp_for_e_f(_flags, argv, argc, preg);
    else
      comp_pattern(argc, argv, _flags, preg);
  }

  return 0;
}

int count_flags(int argc, char *argv[]) {
  int count = 0;
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-') {
      count++;
      if (strchr(argv[i], 'e') != NULL) count++;
      if (strchr(argv[i], 'f') != NULL) count++;
    }
  }
  return count;
}

void open_file_for_pattern(char buff[SIZE_PATTERN]) {
  char *file_name = optarg;
  strcpy(buff, "");
  FILE *file_pattern = fopen(file_name, "r");
  if (file_pattern != NULL) {
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file_pattern) > 0) {
      strcat(buff, line);
      if (buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '|';
    }
    free(line);
    fclose(file_pattern);
  } else
    printf("grep: %s: No such file or directory", file_name);
}

flags read_flags(int argc, char **argv) {
  char buff[SIZE_PATTERN] = {0};
  int current_flag = getopt_long(argc, argv, "e:icvlnhsf:o", NULL, NULL);
  flags _flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
  for (; current_flag != -1;
       current_flag = getopt_long(argc, argv, "e:icvlnhsf:o", NULL, NULL)) {
    switch (current_flag) {
      case 'e':
        _flags.e = 1;
        _flags.count_flags += 2;
        strcat(_flags.pattern, optarg);
        strcat(_flags.pattern, "|");
        break;
      case 'i':
        _flags.i = 1;
        break;
      case 'v':
        _flags.v = 1;
        break;
      case 'c':
        _flags.c = 1;
        break;
      case 'l':
        _flags.l = 1;
        break;
      case 'n':
        _flags.n = 1;
        break;
      case 'h':
        _flags.h = 1;
        break;
      case 's':
        _flags.s = 1;
        break;
      case 'f':
        _flags.f = 1;
        open_file_for_pattern(buff);
        strcat(_flags.pattern, buff);
        break;
      case 'o':
        _flags.o = 1;
        break;
      default:
        _flags.error = 1;
        break;
    }
  }
  return _flags;
}

void reg_comp_for_e_f(flags _flags, char *argv[], int argc, regex_t *preg) {
  if (_flags.pattern[strlen(_flags.pattern) - 1] == '|')
    _flags.pattern[strlen(_flags.pattern) - 1] = '\0';
  regcomp(preg, _flags.pattern,
          _flags.i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);
  for (char **name = &argv[optind]; name != &argv[argc]; ++name) {
    if (**name == '-') continue;
    file_open(name, argc, _flags, preg);
  }
  regfree(preg);
}

void comp_pattern(int argc, char *argv[], flags _flags, regex_t *preg) {
  char **pattern = &argv[1];
  char **end = &argv[argc];

  for (; pattern[0][0] == '-' && pattern != end; ++pattern)
    ;

  regcomp(preg, *pattern, _flags.i ? REG_EXTENDED | REG_ICASE : REG_EXTENDED);

  for (char **name = pattern + 1; name != end; ++name) {
    if (**name == '-') continue;
    file_open(name, argc, _flags, preg);
  }

  regfree(preg);
}

void file_open(char **name, int argc, flags _flags, regex_t *preg) {
  FILE *file = fopen(*name, "r");

  if (file != NULL) {
    grep_functions(argc, file, _flags, preg, *name);

    fclose(file);
  } else {
    if (!_flags.s) printf("grep: %s: No such file or directory\n", *name);
  }
}

void grep_functions(int argc, FILE *file, flags _flags, regex_t *preg,
                    char *name) {
  int num = 0;
  char *line = NULL;
  size_t len = 0;
  regmatch_t match;
  int count = 0;

  while (getline(&line, &len, file) > 0) {
    ++num;
    if (_flags.v) {
      not_matching_line(preg, line, match, argc, name, num, _flags, &count);
    } else {
      matching_line(preg, line, match, argc, name, num, _flags, &count);
    }
  }
  if (_flags.c) {
    output_for_c(count, argc, _flags, name);
  }
  if (_flags.l) output_for_l(count, name);
  free(line);
}

void matching_line(regex_t *preg, char *line, regmatch_t match, int argc,
                   char *name, int num, flags _flags, int *count) {
  if (!regexec(preg, line, 1, &match, 0)) {
    *count = *count + 1;
    if (!_flags.c && !_flags.l) {
      if (!_flags.e && !_flags.f && (argc - _flags.count_flags - 2 > 1) &&
          !_flags.h && _flags.o)
        printf("%s:", name);
      else if ((_flags.e || _flags.f) && (argc - _flags.count_flags - 1 > 1) &&
               !_flags.h && _flags.o)
        printf("%s:", name);
      if (_flags.o) {
        output_for_o(match, line, preg, num, _flags);
      } else
        output_line(argc, _flags, name, line, num);
    }
  }
}

void not_matching_line(regex_t *preg, char *line, regmatch_t match, int argc,
                       char *name, int num, flags _flags, int *count) {
  if (regexec(preg, line, 1, &match, 0)) {
    *count = *count + 1;
    if (!_flags.c && !_flags.l) {
      output_line(argc, _flags, name, line, num);
    }
  }
}

void output_line(int argc, flags _flags, char *name, char *line, int num) {
  if (!_flags.e && !_flags.f && (argc - _flags.count_flags - 2 > 1) &&
      !_flags.h)
    printf("%s:", name);
  else if ((_flags.e || _flags.f) && (argc - _flags.count_flags - 1 > 1) &&
           !_flags.h)
    printf("%s:", name);
  if (_flags.n) number_line(num);
  printf("%s", line);
  if (line[strlen(line) - 1] != '\n') printf("\n");
}

void output_for_c(int count, int argc, flags _flags, char *name) {
  if (!_flags.e && !_flags.f && (argc - _flags.count_flags - 2 > 1) &&
      !_flags.h)
    printf("%s:", name);
  else if ((_flags.e || _flags.f) && (argc - _flags.count_flags - 1 > 1) &&
           !_flags.h)
    printf("%s:", name);
  if (_flags.l && count > 0)
    printf("1");
  else
    printf("%d", count);
  printf("\n");
}

void output_for_l(int count, char *name) {
  if (count) {
    printf("%s", name);
    printf("\n");
  }
}

void number_line(int num) { printf("%d:", num); }

void output_for_o(regmatch_t match, char *line, regex_t *preg, int num,
                  flags _flags) {
  if (_flags.n && _flags.o) number_line(num);
  printf("%.*s\n", (int)(match.rm_eo - match.rm_so), line + match.rm_so);
  char *remaining = line + match.rm_eo;
  while (!regexec(preg, remaining, 1, &match, 0)) {
    printf("%.*s\n", (int)(match.rm_eo - match.rm_so), remaining + match.rm_so);
    remaining = remaining + match.rm_eo;
  }
}
