#define _GNU_SOURCE
#include "s21_grep.h"

int main(int argc, char *argv[]) {
  option flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  files file_names = {0, NULL};
  patterns pattern_names = {0, NULL};
  int error = get_options_patterns_files(&flags, &file_names, &pattern_names,
                                         argc, argv);
  if (!error) {
    output(&flags, &file_names, &pattern_names);
  } else if (error == -1) {
    printf(
        "\nusage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]\n"
        "    [-e pattern] [-f file] [--binary-files=value] [--color=when]\n"
        "    [--context[=num]] [--directories=action] [--label] "
        "[--line-buffered]\n"
        "    [--null] [pattern] [file ...]");
  }
  for (int i = 0; i < pattern_names.count_of_patterns; i++) {
    free(pattern_names.pattern[i]);
  }
  for (int i = 0; i < file_names.count_of_files; i++) {
    free(file_names.file[i]);
  }
  free(pattern_names.pattern);
  free(file_names.file);
  return 0;
}

int get_options_patterns_files(option *flags, files *file_names,
                               patterns *pattern_names, int argc,
                               char *argv[]) {
  int error = 0, flag_next_i = 0, j;
  for (int i = 1; i < argc && !error; i++) {
    flag_next_i = 0;
    if (argv[i][0] == '-') {
      j = 1;
      while (argv[i][j] != '\0' && !error) {
        switch (argv[i][j]) {
          case 'i':
            flags->i = 1;
            break;
          case 'v':
            flags->v = 1;
            break;
          case 'c':
            flags->c = 1;
            break;
          case 'l':
            flags->l = 1;
            break;
          case 'n':
            flags->n = 1;
            break;
          case 'h':
            flags->h = 1;
            break;
          case 's':
            flags->s = 1;
            break;
          case 'o':
            flags->o = 1;
            break;
          case 'e': {
            if (argv[i][j + 1] != '\0') {
              get_patterns(&argv[i][j + 1], pattern_names);
              j = strlen(argv[i]) - 1;
            } else {
              flag_next_i = 1;
              get_patterns(argv[i + 1], pattern_names);
            }
            flags->e = 1;
            break;
          }
          case 'f': {
            if (argv[i][j + 1] != '\0') {
              error = get_patterns_of_file(&argv[i][j + 1], pattern_names);
              j = strlen(argv[i]) - 1;
            } else {
              error = get_patterns_of_file(argv[i + 1], pattern_names);
              flag_next_i = 1;
            }
            flags->f = 1;
            break;
          }
          default:
            printf("grep: invalid option -- %c", argv[i][j]);
            error = -1;
            break;
        }
        j++;
      }
      if (flag_next_i) i++;
    } else {
      if (!(flags->e || flags->f)) {
        get_patterns(argv[i], pattern_names);
        flags->e = 1;
      } else {
        get_file_name(argv[i], file_names);
      }
    }
  }
  if (flags->c || flags->l) {
    flags->o = 0;
    flags->n = 0;
  }
  if (flags->v) flags->o = 0;
  return error;
}

void get_patterns(char *pat, patterns *pattern_names) {
  pattern_names->pattern =
      (char **)realloc(pattern_names->pattern,
                       (pattern_names->count_of_patterns + 1) * sizeof(char *));
  pattern_names->pattern[pattern_names->count_of_patterns] =
      (char *)malloc(strlen(pat) + 1);
  strcpy(pattern_names->pattern[pattern_names->count_of_patterns], pat);
  pattern_names->count_of_patterns++;
}

int get_patterns_of_file(char *file_name, patterns *pattern_names) {
  FILE *file;
  int error = 0;
  if ((file = fopen(file_name, "r")) == NULL) {
    printf("grep: %s: No such file or directory", file_name);
    error++;
  } else {
    while (1) {
      char pat[MAX_SIZE];
      if (fgets(pat, MAX_SIZE, file) == NULL) break;
      if (pat[strlen(pat) - 1] == '\n') pat[strlen(pat) - 1] = '\0';
      get_patterns(pat, pattern_names);
    }
    fclose(file);
  }
  return error;
}

void get_file_name(char *name, files *file_names) {
  file_names->file = (char **)realloc(
      file_names->file, (file_names->count_of_files + 1) * sizeof(char *));
  file_names->file[file_names->count_of_files] =
      (char *)malloc(strlen(name) + 1);
  strcpy(file_names->file[file_names->count_of_files], name);
  file_names->count_of_files++;
}

void output(option *flags, files *file_names, patterns *pattern_names) {
  int cflags, match, number_line, num_match_lines, flag_match;
  regex_t regex;
  regmatch_t pmatch[1];
  char *str = NULL;
  size_t size;
  cflags = REG_EXTENDED;
  if (flags->i) cflags = REG_ICASE;

  for (int i = 0; i < file_names->count_of_files; i++) {
    FILE *file = fopen(file_names->file[i], "r");
    if (file != NULL) {
      number_line = 0;
      num_match_lines = 0;
      while ((getline(&str, &size, file)) != -1) {
        number_line++;
        flag_match = 0;
        if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
        for (int j = 0; j < pattern_names->count_of_patterns; j++) {
          regcomp(&regex, pattern_names->pattern[j], cflags);
          match = regexec(&regex, str, 0, NULL, 0);
          regfree(&regex);
          if (!match) {
            flag_match = 1;
            break;
          }
        }
        if (flag_match && !flags->v) {
          num_match_lines++;
          if (!flags->c && !flags->l) {
            if (file_names->count_of_files > 1 && !flags->h)
              printf("%s:", file_names->file[i]);
            if (flags->n) printf("%d:", number_line);
            if (flags->o) {
              char *buff = str;
              for (int j = 0; j < pattern_names->count_of_patterns; j++) {
                regcomp(&regex, pattern_names->pattern[j], cflags);
                while ((regexec(&regex, buff, 1, pmatch, 0)) == 0) {
                  for (int k = (int)pmatch[0].rm_so; k < (int)pmatch[0].rm_eo;
                       k++) {
                    printf("%c", buff[k]);
                  }
                  buff += (int)pmatch[0].rm_eo;
                  printf("\n");
                }
                regfree(&regex);
              }
            } else {
              printf("%s\n", str);
            }
          }
        } else if (!flag_match && flags->v) {
          num_match_lines++;
          if (!flags->c && !flags->l) {
            if (file_names->count_of_files > 1 && !flags->h)
              printf("%s:", file_names->file[i]);
            if (flags->n) printf("%d:", number_line);
            printf("%s\n", str);
          }
        }
      }
      if (flags->l || flags->c) {
        if (flags->c) {
          if (flags->l) {
            if (file_names->count_of_files > 1 && !flags->h)
              printf("%s:", file_names->file[i]);
            if (num_match_lines) printf("%d\n", 1);
            if (!num_match_lines) printf("%d\n", 0);
          } else {
            if (file_names->count_of_files > 1 && !flags->h)
              printf("%s:", file_names->file[i]);
            printf("%d\n", num_match_lines);
          }
        }
        if (flags->l) {
          if (num_match_lines) printf("%s\n", file_names->file[i]);
        }
      }
      fclose(file);
    } else {
      if (!flags->s)
        printf("grep: %s: No such file or directory\n", file_names->file[i]);
    }
  }
  free(str);
}
