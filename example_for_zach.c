#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *arg = argv[1];

  printf("%s\n", arg);

  char from_file[1024];

  fgets(from_file, 1024, stdin);

  printf("from file: %s\n", from_file);

  return EXIT_SUCCESS;
}
