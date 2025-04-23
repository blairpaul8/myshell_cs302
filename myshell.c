#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIMITERS " \t\r\n\a"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BLUE "\033[34m"

int execute(char **args, int *token_count) {
  // char* command = "ls";
  pid_t pid;
  pid_t wpid;
  int status;
  int fd1;
  int stdout_id = 1;
  pid = fork();

  if (pid == 0) {
    for (int i = 0; i < *token_count; i++) {
      if (strncmp(args[i], ">", 1) == 0) {
        fd1 = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
        memmove(&args[i], &args[i + 2], (i + 1) * sizeof(args[0]));
        stdout_id = dup2(fd1, 1);
        break;
      }
    }
    close(fd1);
    execvp(args[0], args);

  } else if (pid < 0) {
    perror("Fork failed.\n");
    return 0;

  } else {
    wpid = wait(&status);
    // printf("parent waiting pid = %d\n", pid);
    // printf("  WIFEXITED:    %d\n", WIFEXITED(status));
  }

  return 1;
}

char **parse_input(char *input, int *token_count) {
  int num_tokens = 10;
  char **tokens;
  char *token;
  *token_count = 0;

  tokens = (char **)malloc(num_tokens * sizeof(char *));
  if (tokens == NULL) {
    perror("Failed to allocate memory for tokens");
    return EXIT_SUCCESS;
  }

  token = strtok(input, DELIMITERS);

  while (token != NULL) {
    if (*token_count >= num_tokens) {
      num_tokens *= 2;
      tokens = (char **)realloc(tokens, num_tokens * sizeof(char *));
    }
    tokens[*token_count] = token;
    (*token_count)++;
    token = strtok(NULL, DELIMITERS);
  }

  tokens[*token_count] = NULL;

  return tokens;
}

ssize_t get_input(char **input, size_t *buff, int delim) {
  *buff = 64;
  if (*input == NULL) {
    *input = (char *)malloc(*buff * sizeof(char));
  }
  int c;
  int i = 0;
  ssize_t len = 0;

  while ((c = getchar()) != '\n') {
    if (i >= *buff) {
      *buff += *buff;
      *input = (char *)realloc(*input, *buff * sizeof(char *));
    }
    (*input)[i] = c;
    i++;
    len++;
  }

  (*input)[len] = '\0';

  return len;
}

void sh_loop(void) {
  // Used for the prompt
  char cwd[1024];
  char *user = getlogin();
  char *input = NULL;
  size_t buff = 0;
  ssize_t linelen;
  char **args;
  int status;
  int token_count = 0;

  getcwd(cwd, sizeof(cwd));
  char *home = getenv("HOME");

  system("clear");
  do {
    if (home != NULL && (strncmp(home, cwd, strlen(home)) == 0)) {
      printf(GREEN "%s:" BLUE "~%s\n"
                   " >> " RESET,
             user, cwd + strlen(home));

    } else {
      printf(GREEN "%s:" BLUE "%s\n"
                   " >> " RESET,
             user, cwd);
    }

    linelen = get_input(&input, &buff, '\n');
    // printf("%s\n", input);
    args = parse_input(input, &token_count);
    status = execute(args, &token_count);
    free(input);
    free(args);
    input = NULL;

  } while (status);
}

int main() {

  sh_loop();

  return 0;
}
