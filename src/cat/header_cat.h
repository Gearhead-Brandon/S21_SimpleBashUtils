#ifndef HEADER_FILE
#define HEADER_FILE
#define _GNU_SOURCE

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int v;
  int b;
  int e;
  int n;
  int s;
  int t;
  int count;
  int last_empty;
  int hack;
  int last_eof;
} opt;

void print_file(char *filepath, opt *options);
void prepend(opt *options, char *line);
void file_print(opt *options, const char *line, size_t len);
void v_flag(unsigned char c);

#endif