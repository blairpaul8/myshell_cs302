#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PARSE_DELIM " \t\r\n\a"

char** parse_input(char *input) {
	int buffsize = 64;
	int position = 0;
	char **tokens = malloc(buffsize * sizeof(char*));
	char* token;

	if (!tokens) {
		fprintf(stderr, "parse_input allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, PARSE_DELIM);
	while (token != NULL) {
		tokens[position] = token;
		position++;


		if (position >= buffsize) {
			buffsize += buffsize;
			tokens = realloc(tokens, buffsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "reallocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, PARSE_DELIM);
	}
	
	tokens[position] = NULL;

	return tokens;
}

int execute(const char** args)  {
  
  return -1;
}

char* get_input(char* input) {
  int c;
  int i = 0;
  int len = 0;

  while ((c = getchar()) != '\n') {
    input[i] = c;
    i++;
    len++;
  }
  
  input[len] = '\0';
  
	return input;
}

void print_input(char* input) {
  int i = 0;
  while (input[i] != '\0') {
    printf("%c", input[i]);
    i++;
  }
  printf("\n");
}

void sh_loop(void) {
	//Used for the prompt
	char cwd[1024];
	char *user = getlogin();
  int buff = 1000;
	char* input;
  input = (char*)malloc(buff * sizeof(char));
	char** args;
	int status;

	getcwd(cwd, sizeof(cwd));
	system("clear");
	do {
		printf("%s: %s\n >> ",user, cwd);

		input = get_input(input);
    print_input(input);
		//args = parse_input(input);
		//status = execute(args);

		free(input);
		free(args);

	} while (status);

}

int main() {

	sh_loop();


	return 0;
}
