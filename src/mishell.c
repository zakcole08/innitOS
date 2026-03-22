#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmd_help() {
	printf("help - see this help menu\n");
	return 0;
}

int main() {
	char command[65536];
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
		else {
			printf("%s does not exist as a command on this system\n", command);
		}
	}
	return 0;
}
