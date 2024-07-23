#ifndef HEADERGREP_FILE
#define HEADERGREP_FILE
#define _GNU_SOURCE

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 1024

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

  int files_count;
  char pattern[BUFSIZE];
  int error;
} Options;

void get_data(Options *options, int argc, char **argv);
int search_for_matches(char *string, char *pattern, int flag);
void print_o(char *string, int flag, Options options, char *filename,
             int line_number);
void print_file(Options *options, char *filename);
void collect_pattern_for_others(char **argv, Options *options);
int options_flags(Options options, int flag_);
void collect_patterns_for_e_f(Options *options, char *regex);
void collect_patterns_from_file(Options *options, char *filename);
void print_filename(Options options, char *filename);
void print_line_number(Options options, int line_number);

#endif