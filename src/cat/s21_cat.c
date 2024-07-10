#include "s21_cat.h"

int main(int argc, char *argv[]) {
  option flags = {0, 0, 0, 0, 0, 0};
  if (!get_options(&flags, argc, argv)) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') output(&flags, argv[i]);
    }
  }
  return 0;
}

int get_options(option *flags, int argc, char *argv[]) {
  int j;
  int error = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] != '-' && !error) {
      j = 1;
      while (argv[i][j] != '\0') {
        if (argv[i][j] == 'b') {
          flags->b = 1;
        } else if (argv[i][j] == 'e') {
          flags->e = 1;
          flags->v = 1;
        } else if (argv[i][j] == 'v') {
          flags->v = 1;
        } else if (argv[i][j] == 'n') {
          flags->n = 1;
        } else if (argv[i][j] == 's') {
          flags->s = 1;
        } else if (argv[i][j] == 't') {
          flags->t = 1;
          flags->v = 1;
        } else if (argv[i][j] == 'E') {
          flags->e = 1;
        } else if (argv[i][j] == 'T') {
          flags->t = 1;
        } else {
          error = 1;
          printf("cat: illegal option -- %c\n", argv[i][j]);
          printf("usage:cat [-benstuv] [file ...]\n");
        }
        j++;
      }
    } else if (argv[i][0] == '-' && argv[i][1] == '-' && !error) {
      if (strcmp(argv[i], "--number-nonblank") == 0) {
        flags->b = 1;
      } else if (strcmp(argv[i], "--number") == 0) {
        flags->n = 1;
      } else if (strcmp(argv[i], "--squeeze-blank") == 0) {
        flags->s = 1;
      } else {
        error = 1;
        printf("cat: illegal option -- %c\n", '-');
        printf("usage:cat [-benstuv] [file ...]\n");
        break;
      }
    } else {
      continue;
    }
  }
  if (flags->b == 1 && flags->n == 1) flags->n = 0;
  return error;
}

void output(option *flags, char *file_name) {
  FILE *file;
  int prev_symbol = '\n', number_of_string = 1, empty_string = 1;
  int symbol;
  file = fopen(file_name, "r");
  if (file != NULL) {
    while ((symbol = fgetc(file)) != EOF) {
      if (flags->s && symbol == '\n' && prev_symbol == '\n') {
        empty_string++;
      } else {
        empty_string = 1;
      }
      if (empty_string < 3) {
        if (prev_symbol == '\n' && flags->b && symbol != '\n') {
          printf("%6d\t", number_of_string);
          number_of_string++;
        }
        if (prev_symbol == '\n' && flags->n) {
          printf("%6d\t", number_of_string);
          number_of_string++;
        }
        if (flags->t && symbol == '\t') {
          printf("^");
          symbol = 'I';
        }
        if (flags->e && symbol == '\n') {
          printf("$");
        }
        if (flags->v) {
          if (symbol >= 0 && symbol < 32 && symbol != 9 && symbol != 10) {
            printf("^");
            symbol += 64;
          } else if (symbol == 127) {
            printf("^");
            symbol -= 64;
          } else if (symbol > 127 && symbol < 160) {
            printf("M-^");
            symbol -= 64;
          }
        }
        printf("%c", symbol);
      }
      prev_symbol = symbol;
    }
  } else {
    printf("cat: %s: No such file or directory\n", file_name);
  }
  fclose(file);
}
