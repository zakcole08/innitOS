/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 8192

int cat_fd(int fd) {
	char buf[BUF_SIZE];
	ssize_t n;

	while ((n = read(fd, buf, sizeof(buf))) > 0) {
		ssize_t total = 0;

		while (total < n) {
			ssize_t written = write(STDOUT_FILENO, buf + total, n - total);
				if (written < 0) {
					perror("write");
					return -1;
				}
				total += written;
		}
	}

	if (n < 0) {
		perror("read");
		return -1;
	}

	return 0;
}

int cmd_cat(int argc, char *argv[]) {
	if (argc == 1) {
		if (cat_fd(STDIN_FILENO) != 0) {
			return 1;
		}
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && argv[i][1] == '\0') {
			if (cat_fd(STDIN_FILENO) != 0) {
				return 1;
			}
			continue;
		}

		int fd = open(argv[i], O_RDONLY);
		if (fd < 0) {
				perror(argv[i]);
				continue;
		}

		if (cat_fd(fd) != 0) {
			close(fd);
			return 1;
		}

		if (close(fd) < 0) {
			perror("close");
			return 1;
		}
	}
	return 0;
}
