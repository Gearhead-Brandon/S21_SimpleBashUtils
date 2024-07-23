#include "header_cat.h"

void print_file(char *filepath, opt *options) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  FILE *file = fopen(filepath, "r");
  if (file == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  while ((nread = getline(&line, &len, file)) != -1) {
    if (nread == 1 && (options->last_empty || options->last_eof) && options->s)
      continue;
    options->last_eof = 0;
    (nread == 1 && !options->hack) ? (options->last_empty = 1)
                                   : (options->last_empty = 0);
    prepend(options, line);
    file_print(options, line, nread);
  }
  (options->last_empty) ? (options->last_eof = 1) : (options->hack = 1);
  options->last_empty = 0;
  free(line);
  fclose(file);
}

void prepend(opt *options, char *line) {
  if ((options->n && !options->hack) && !(options->b && !strcmp(line, "\n"))) {
    printf("%6d\t", options->count++);
  }
  options->hack = 0;
}

void file_print(opt *options, const char *line, size_t len) {
  unsigned char c;
  for (int i = 0; (size_t)i < len; i++) {
    c = line[i];
    if ((options->t == 1) && c == '\t') {
      printf("^I");
    } else if ((options->e == 1) && c == '\n') {
      printf("$\n");
    } else if (options->v == 1) {
      v_flag(c);
    } else
      printf("%c", c);
  }
}

void v_flag(unsigned char c) {
  if (c == 9 || c == 10) {
    printf("%c", c);
  } else if (c >= 32 && c < 127) {
    printf("%c", c);
  } else if (c == 127) {
    printf("^?");
  } else if (c >= 128 + 32) {
    printf("M-");
    (c < 128 + 127) ? printf("%c", c - 128) : printf("^?");
  } else {
    (c > 32) ? printf("M-^%c", c - 128 + 64) : printf("^%c", c + 64);
  }
}