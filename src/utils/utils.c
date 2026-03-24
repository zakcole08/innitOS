#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int arg_limit = 64;

int exec(const char *command) {
	if (!command) return -1;

	char *cmd_copy = strdup(command);
	char *args[arg_limit];
	int i = 0;

	char *token = strtok(cmd_copy, " ");
	while (token != NULL && i < 63) {
			args[i++] = token;
			token = strtok(NULL, " ");
	}
	args[i] = NULL;

	if (i == 0) {
			free(cmd_copy);
			return -1;
	}

	pid_t pid = fork();
	if (pid == -1) {
			free(cmd_copy);
			return -1;
	}

	if (pid == 0) {
			execv(args[0], args); 
			perror("innitOS exec failed");
			_exit(127);
	}
	else {
		int status;
		waitpid(pid, &status, 0);
		free(cmd_copy);
			
		if (WIFEXITED(status)) {
			return WEXITSTATUS(status);
		}
		return -1;
	}
}
