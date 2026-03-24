/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int cmd_ls(int argc, char *argv[]) {
	const char *path;
	DIR *dir;
	struct dirent *entry;

	if (argc > 1) {
		path = argv[1];
	} else {
		path = ".";
	}

	dir = opendir(path);
	if (dir == NULL) {
		perror("opendir");
		return 1;
	}

	errno = 0;
	while ((entry = readdir(dir)) != NULL) {
		printf("%s\n", entry->d_name);
	}

	if (errno != 0) {
		perror("readdir");
		closedir(dir);
		return 1;
	}

	if (closedir(dir) == -1) {
		perror("closedir");
		return EXIT_FAILURE;
	}

	return 0;
}
