#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <stdbool.h>
#include <string.h>

#define NUM_BUILTINS 3
int cmd_cd(char** args);
int cmd_man(char** args);
int cmd_exit(char** args);
int cmd_echo(char** args);

extern char* cmds[];
extern int (*builtin_cmds[])(char**);

int lookup(char* cmd);
unsigned int hash(char* cmd);


#endif // !HASH_MAP_H
