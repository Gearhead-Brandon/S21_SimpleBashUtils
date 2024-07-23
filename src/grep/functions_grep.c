#include "s21_grep.h"

void get_data(Options *options, int argc, char **argv) {
  char short_options[] = "e:ivclnhsf:o";

  int flag;
  while ((flag = getopt(argc, argv, short_options)) != -1) {
    switch (flag) {
      case 'e':
        collect_patterns_for_e_f(options, optarg);
        printf("optarg == %s\n", optarg);
        options->e = 1;
        break;
      case 'i':
        options->i = 1;
        break;
      case 'v':
        options->v = 1;
        break;
      case 'c':
        options->c = 1;
        break;
      case 'l':
        options->l = 1;
        break;
      case 'n':
        options->n = 1;
        break;
      case 'h':
        options->h = 1;
        break;
      case 's':
        options->s = 1;
        break;
      case 'f':
        collect_patterns_from_file(options, optarg);
        break;
      case 'o':
        options->o = 1;
        break;
      case '?':
        fprintf(stderr, "Invalid options in %s\n", argv[0]);
        exit(1);
    }
  }

  if (options->l) options->c = options->o = 0;
  if (options->c) options->o = 0;
  if (options->v && options->o) options->error = 1;
}

void collect_pattern_for_others(char **argv, Options *options) {
  if (!options->e && !options->f) {
    strcpy(options->pattern, argv[optind++]);
  }
}

int options_flags(Options options, int flag_) {
  int flag = flag_;
  if (options.i) {
    flag |= REG_ICASE;
  }

  if (options.e || options.f || options.o) {
    flag |= REG_EXTENDED;
  }
  return flag;
}

void collect_patterns_for_e_f(Options *options, char *regex) {
  if (!options->e && !options->f) {
    strcpy(options->pattern, regex);
  } else {
    strcat(options->pattern, "|");
    strcat(options->pattern, regex);
  }
}

void collect_patterns_from_file(Options *options, char *filename) {
  FILE *fp = NULL;
  char *line = NULL;

  if ((fp = fopen(filename, "r")) == NULL) {
    if (!options->s)
      fprintf(stderr, "s21_grep: %s No such file or directory\n", filename);
  } else {
    int len = 0;
    size_t size = 0;

    while ((len = getline(&line, &size, fp)) != -1) {
      if (line[len - 1] == '\n') line[len - 1] = '\0';
      collect_patterns_for_e_f(options, line);
      options->f = 1;
    }
    if (line) free(line);
  }

  if (fp) fclose(fp);
}

void print_file(Options *options, char *filename) {
  int flag = options_flags(*options, REG_NEWLINE);
  FILE *fp;

  if ((fp = fopen(filename, "r")) == NULL) {
    if (!options->s)
      fprintf(stderr, "s21_grep: %s No such file or directory\n", filename);

  } else {
    int line_number = 0;
    int count_match_lines = 0;

    int len;
    char *line = NULL;
    size_t size = 0;
    char last_char;

    while ((len = getline(&line, &size, fp)) != -1) {
      last_char = line[strlen(line) - 1];
      line_number++;

      int is_match = !search_for_matches(line, options->pattern, flag);

      if (options->v) is_match = !is_match;

      if (is_match) count_match_lines++;

      if (is_match && options->l && !options->error) {
        printf("%s\n", filename);
        break;
      }
      if (options->o && !options->c && !options->l && !options->error) {
        print_o(line, flag, *options, filename, line_number);
      }
       //printf("here2\n");
      if (is_match && !options->c && !options->error && !options->o) {  // match
        //printf("here\n");
        print_filename(*options, filename);
        print_line_number(*options, line_number);

        printf("%s", line);  // last new line
        if (last_char != '\n') printf("\n");
      }
    }

    if (options->c && !options->l) {  // C FLAG H FLAG
      // last_char = line[len - 1];
      if (options->files_count > 1 && !options->h) printf("%s:", filename);

      printf("%d", count_match_lines);
      //  printf("%d\n", line[0]);
      if (last_char != '\n' || len == -1) printf("\n");
    }

    if (line) free(line);
  }  // else = file access

  if (fp) fclose(fp);
}

int search_for_matches(char *string, char *pattern, int flag) {
  regex_t reg;
  int status = regcomp(&reg, pattern, flag);
  if (!status) status = regexec(&reg, string, 0, NULL, 0);
  regfree(&reg);
  return status;
}

void print_o(char *string, int flag, Options options, char *filename,
             int line_number) {
  int status;
  regex_t reg;
  regcomp(&reg, options.pattern, flag);
  char *str = string;
  regmatch_t pmatch[100];
  status = regexec(&reg, str, 1, pmatch, 0);
  while (status == 0) {
    print_filename(options, filename);
    print_line_number(options, line_number);

    printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
           str + pmatch[0].rm_so);
    str += pmatch[0].rm_eo;
    status = regexec(&reg, str, 1, pmatch, 0);
  }

  regfree(&reg);
  // return status;
}

void print_filename(Options options, char *filename) {
  if (options.files_count > 1 && !options.h) {  // files_count H FLAG
    printf("%s:", filename);
  }
}

void print_line_number(Options options, int line_number) {
  if (options.n) {  // N FLAG
    printf("%d:", line_number);
  }
}
