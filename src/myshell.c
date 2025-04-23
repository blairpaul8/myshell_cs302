#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "hash_map.h"

#define DELIMITERS " \t\r\n\a"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define CLEAR "\033[H"

int execute(char** args) {
  int builtin_index = lookup(args[0]);
  if (builtin_index != -1) {
    return builtin_cmds[builtin_index](args);
    return 1;
  }

  pid_t pid;
  pid_t wpid;
  int status;

  pid = fork(); 

  //printf("ppid = %d\n", pid);  
  //printf("pid = %d\n", pid);  

  if (pid ==  0) {
    //printf("pid = %d\n", pid);  
    execvp(args[0], args);
  }
  else if (pid < 0) {
    perror("Fork failed.\n");
    return 0;
  }
  else {
    wpid = wait(&status);
    //printf("parent waiting pid = %d\n", pid);  
    //printf("  WIFEXITED:    %d\n", WIFEXITED(status));
  }

  return 1;
}

char** parse_input(char *input) {
  int num_tokens = 10;
  char** tokens;
  char* token;
  int token_count = 0;

  tokens = (char**)malloc(num_tokens * sizeof(char*));
  if (tokens == NULL) {
    perror("Failed to allocate memory for tokens");
    return EXIT_SUCCESS;
  }
  
  token = strtok(input, DELIMITERS);

  while (token != NULL) {
    if (token_count >= num_tokens) {
      num_tokens *= 2;
      tokens = (char**)realloc(tokens, num_tokens * sizeof(char*));
    }
    tokens[token_count] = token;
    token_count++;
    token = strtok(NULL, DELIMITERS);
  }

  tokens[token_count] = NULL;

  /*printf("Tokens:\n");
  printf("   ");
  for (int i = 0; i < token_count; i++) {
    printf("%s, ", tokens[i]);
  }
  printf("\n");
 */ 
  return tokens;
}

ssize_t get_input(char** input, size_t *buff, int delim) {
  *buff = 64;
  if (*input == NULL) {
    *input = (char*)malloc(*buff * sizeof(char));
  }
  int character;
  int i = 0;
  ssize_t len = 0;

  while ((character = getchar()) != '\n') {
    if (i >= *buff) {
      *buff += *buff;
      *input = (char*)realloc(*input, *buff * sizeof(char*));

    }
    (*input)[i] = character;
    i++;
    len++;
  }
  
  (*input)[len] = '\0';
   
	return len;
}

void sh_loop(void) {
	//Used for the prompt
	char cwd[1024];
	char *user = getlogin();
	char* input = NULL;
  size_t buff = 0;
  ssize_t linelen;
	char** args;
	int status;

  system("clear");
	do {
	  getcwd(cwd, sizeof(cwd));
    char* home = getenv("HOME");

    if (home != NULL && (strncmp(home, cwd, strlen(home)) == 0)) {
		  printf(GREEN "%s:" BLUE "~%s\n"" >> " RESET,user, cwd + strlen(home));

    }
    else {
		  printf(GREEN "%s:" BLUE "%s\n"" >> " RESET,user, cwd);
    }

		linelen = get_input(&input, &buff, '\n');
    //printf("%s\n", input);
		args = parse_input(input);
		status = execute(args);
    

	} while (status);
	free(input);
	free(args);

}

int main() {

	sh_loop();

	return 0;
}
