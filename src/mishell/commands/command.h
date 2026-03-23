#ifndef COMMAND_H
#define COMMAND_H

typedef int (*command_func)(int argc, char **argv);

typedef struct {
  char *name;
  command_func func;
  char *help_text;
} Command;

int cmd_help(int argc, char **argv);
int cmd_pwd(int argc, char **argv);
int cmd_echo(int argc, char **argv);

#endif
