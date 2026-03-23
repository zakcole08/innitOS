/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

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
