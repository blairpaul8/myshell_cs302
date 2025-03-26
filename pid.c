#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  printf("My pid = %d My parents PID = %d\n", getpid(), getppid());
  return 0;

}

