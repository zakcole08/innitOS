#include <stdio.h>
#include <unistd.h>
#include "command.h"

int cmd_pwd(int argc, char **argv) {
	char buf[1024];
	if (getcwd(buf, sizeof(buf))) {
		printf("%s\n", buf);
		return 0;
	}
	else {
		return 1;
	}
}
