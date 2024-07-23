#include "header_cat.h"

int main(int argc, char *argv[]) {
  opt options = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
  int c;
  const struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {NULL, 0, NULL, 0}};
  while ((c = getopt_long(argc, argv, "benstvETV", long_options, NULL)) != -1) {
    if (c == -1) break;
    switch (c) {
      case 'b':
        options.b = options.n = 1;
        break;
      case 'e':
        options.e = options.v = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'E':
        options.e = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 't':
        options.t = options.v = 1;
        break;
      case 'T':
        options.t = 1;
        break;
      default:
        fprintf(stderr, "Try 'cat --help' for more information.\n");
        exit(EXIT_FAILURE);
    }
  }
  while (optind < argc) {
    char *filepath = argv[optind++];
    (access(filepath, F_OK) != 0)
        ? fprintf(stderr, "%s: %s: No such file or directory\n", "cat",
                  filepath)
        : print_file(filepath, &options);
  }
  return 0;
}