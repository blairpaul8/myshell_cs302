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
			tokens = realloc(buffsize * sizeof(char*));
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

}

char* get_input() {
	int buffsize = 0;
	char *line = NULL;

	if (getline(&line, &buffsize, stdin) == -1) {
		if (feof(stdin)) {
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else {
			perror("Readlin");
			exit(EXIT_FAILURE);
		}
	}
	return line;
}

void sh_loop(void) {
	//Used for the prompt
	char cwd[1024];
	char *user = getlogin();

	char* input;
	char** args;
	int status;

	getcwd(cwd, sizeof(cwd));
	system("clear");
	do {
		printf("%s: %s > ",user, cwd);

		input = get_input(input);
		args = parse_input(input);
		status = execute(args);

		free(input);
		free(args);

	} while (status);

}

int main() {

	sh_loop();


	return 0;
}
