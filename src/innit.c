/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/
	
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mount.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    printf("innit loaded successfully, innit\n");

		signal(SIGCHLD, SIG_IGN);

		mount("proc", "/proc", "proc", 0, NULL);
		mount("sysfs", "/sys", "sysfs", 0, NULL);

    while(1) {
			execl("/bin/mishell", "mishell", NULL);
		}
}
