#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *version = "v0.1";

int cmd_help() {
	printf("innitOS %s\n", version); 
	printf("help - see this help menu\n");
	printf("pwd - print the current working directory\n");
	return 0;
}

int cmd_pwd() {
	char buf[1024];
	getcwd(buf, sizeof(buf));
	printf("%s\n", buf);
	return 0;
}

int main() {
	char command[65536];
	printf("innitOS %s\n", version);
	while (1) {
		printf("> ");
		// Ensure input does not exceed buffer size
		if (fgets(command, sizeof(command), stdin) == NULL) {
			break;
		}
		// Remove trailing newline
		command[strcspn(command, "\n")] = '\0';

		// If command is empty, do nothing
		if (strcmp(command, "\0") == 0) {
				continue;
		}
		else if (strcmp(command, "help") == 0) {
				cmd_help();
		}
		else if (strcmp(command, "pwd") == 0) {
			cmd_pwd();
		}
		else {
			printf("%s does not exist as a command on this system\n", command);
		}
	}
	return 0;
}
