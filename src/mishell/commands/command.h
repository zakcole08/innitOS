#ifndef COMMAND_H
#define COMMAND_H

typedef void (*command_func)(int argc, char **argv);

typedef struct {
  char *name;
  command_func func;
  char *help_text;
} Command;

void cmd_help(int argc, char **argv);
void cmd_pwd(int argc, char **argv);

#endif
