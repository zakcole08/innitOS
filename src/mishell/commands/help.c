#include <stdio.h>
#include "command.h"

int cmd_help(int argc, char **argv) {
	printf("innitOS v0.1\n");
  printf("help - show this menu\n");
  printf("pwd  - show current directory\n");
	printf("echo - print a string\n");
	return 0;
}
