#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int k;

int main() {

  int i;
  int j;

  j = 200;
  k = 300;

  printf("Before forking: j (Address 0x%lx) = %d k (Adress 0x%lx) = %d\n", (long unsigned int) &j, j, (long unsigned int) &k, k);

  i = fork();

  if (i > 0) {
    sleep(1);
    printf("Parents after forking: j (Address 0x%lx) = %d k (Adress 0x%lx) = %d\n", (long unsigned int) &j, j, (long unsigned int) &k, k);
  }
  else {
    j++;
    k++;
    printf("Child after forking: j (Address 0x%lx) = %d k (Adress 0x%lx) = %d\n", (long unsigned int) &j, j, (long unsigned int) &k, k);
    
  }
  return 0;
}
