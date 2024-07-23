#include "s21_grep.h"

int main(int argc, char **argv) {
  Options options = {0};

  if (argc < 2) {
    fprintf(stderr, "Usage: s21_grep [OPTION]... PATTERNS [FILE]...\n");
    return 1;
  }

  get_data(&options, argc, argv);
  collect_pattern_for_others(argv, &options);

  options.files_count = argc - optind;
  //printf("optind = %d argc = %d\n", optind, argc);

  while (optind < argc) {
    printf("argv = %s\n", argv[optind]);
    print_file(&options, argv[optind++]);
  }

  return 0;
}
