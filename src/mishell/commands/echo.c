#include <stdio.h>
#include <string.h>

extern int last_exit_status;

void print_usage() {
	printf("Usage: echo [STRING]\n");
}

int cmd_echo(int argc, char **argv) {
	if (argc < 1) {
		printf("\n");
	}
	if (argc > 2) {
		printf("echo: too many arguments\n");
		print_usage();
		return 1;	
	}
	if (strcmp(argv[1], "$?") == 0) {
		printf("%d\n", last_exit_status);
		return 0;
	}

	printf("%s\n", argv[1]);
	return 0;
}
