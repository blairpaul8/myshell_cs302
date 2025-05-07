#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  char input[50];

  fgets(input, sizeof(input), stdin);

  printf("\n");
  printf("From file Redirect: %s", input);
  printf("From argv[1]: %s", argv[1]);
  printf("\n");

  return EXIT_SUCCESS;
}
