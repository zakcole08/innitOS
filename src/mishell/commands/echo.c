/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
