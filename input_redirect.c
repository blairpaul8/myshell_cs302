#include <stdio.h>
#include <stdlib.h>

int main() {
  char input[50];

  printf("Enter a word: ");

  fgets(input, sizeof(input), stdin);

  printf("%s\n", input);

  return 0;
}
