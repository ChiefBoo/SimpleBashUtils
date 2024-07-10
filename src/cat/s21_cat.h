#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int v;
  int n;
  int s;
  int t;
} option;

int get_options(option *flags, int argc, char *argv[]);
void output(option *flags, char *file_name);

#endif  // SRC_CAT_S21_CAT_H_
