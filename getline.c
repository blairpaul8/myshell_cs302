#include <stdio.h>
#include <stdlib.h>

int main() {
  int buff = 1000;
  char input[buff];
  int c;

  int i = 0;
  int len = 0;

  while ((c = getchar()) != '\n') {
    input[i] = c;
    i++;
    len++;
  }
  
  for (int i = 0; i < len; i++) {
    printf("%c", input[i]);

  }
  printf("\n");




}
