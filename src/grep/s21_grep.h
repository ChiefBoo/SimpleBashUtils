#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

typedef struct {
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int o;
  int e;
  int f;
} option;

typedef struct {
  int count_of_patterns;
  char **pattern;
} patterns;

typedef struct {
  int count_of_files;
  char **file;
} files;

int get_options_patterns_files(option *flags, files *file_names,
                               patterns *pattern_names, int argc, char *argv[]);
void get_patterns(char *pat, patterns *pattern_names);
int get_patterns_of_file(char *file_name, patterns *pattern_names);
void get_file_name(char *name, files *file_names);
void output(option *flags, files *file_names, patterns *pattern_names);

#endif  // SRC_GREP_S21_GREP_H_
