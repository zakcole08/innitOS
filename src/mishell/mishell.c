#include <stdio.h>
#include <string.h>
#include "command.h"

char *version = "v0.1";

Command cmd_list[] = {
	{"help", cmd_help, "Show help menu"},
	{"pwd",  cmd_pwd,  "Print working directory"},
	{NULL,   NULL,     NULL} 
};

int main() {
	char input[1024];
	printf("innitOS %s\n", version);
	while (1) {
		printf("> ");
		if (!fgets(input, sizeof(input), stdin)) break;
		input[strcspn(input, "\n")] = '\0';

		if (strlen(input) == 0) continue;

		int found = 0;
		for (int i = 0; cmd_list[i].name != NULL; i++) {
			if (strcmp(input, cmd_list[i].name) == 0) {
					cmd_list[i].func(0, NULL);
					found = 1;
					break;
			}
		}
		if (!found) {
			printf("Unknown command: %s\n", input);
		}
	}
	return 0;
}
