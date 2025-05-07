#include "hash_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Builtin command function to execute change directory cd
int cmd_cd(char **args) {
  int result;

  if (args[1] == NULL || (strcmp(args[1], "~") == 0)) {
    char *home = getenv("HOME");
    result = chdir(home);
    return 1;
  } else if (strcmp(args[1], "..") == 0) {
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    int len = strlen(cwd);

    for (int i = len - 1; i >= 0; i--) {
      if (cwd[i] == '/') {
        cwd[i] = '\0';
        break;
      }
    }
    result = chdir(cwd);

    return 1;
  } else {
    result = chdir(args[1]);
    if (result != 0) {
      printf("The directory: \"%s\" does not exist\n", args[1]);
    }
    return 1;
  }

  return 1;
}

// Builtin cmd function to print the man page.
int cmd_help(char **args) {
  // printf("Calling help\n");

  FILE *fd;
  fd = fopen("data/man.txt", "r");
  char line[256];

  while (fgets(line, 256, fd)) {
    printf("%s", line);
  }

  fclose(fd);
  return 1;
}

// Builtin cmd function to exit the shell
int cmd_exit(char **args) { return 0; }

// Builtin cmd function for echo
int cmd_echo(char **args) {
  while (*args) {
    printf("%s ", *args);
    args++;
  }

  printf("\n");
  return 1;
}

// Parallel Arrays used for the hash map.
char *cmds[] = {"cd", "exit", "help", "echo"};
int (*builtin_cmds[])(char **) = {cmd_cd, cmd_exit, cmd_help, cmd_echo};

// Hash function
unsigned int hash(char *cmd) {
  int length = strlen(cmd);
  unsigned int hash_value = 0;

  // hash algorithm
  for (int i = 0; i < length; i++) {
    hash_value += cmd[i];
    hash_value = hash_value * cmd[i];
  }
  hash_value = (hash_value + length) % NUM_BUILTINS;

  return hash_value;
}

int lookup(char *cmd) {
  int index = hash(cmd);

  // Linear collision resolution
  for (int i = 0; i < NUM_BUILTINS; i++) {
    int probe = (i + index) % NUM_BUILTINS;

    if (strcmp(cmds[probe], cmd) == 0) {
      return probe;
    }
  }
  return -1;
}
