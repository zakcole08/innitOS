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
#include "utils/utils.h"


int main(){
    printf("innit loaded successfully, innit\n");

		signal(SIGCHLD, SIG_IGN);

		if (mount("proc", "/proc", "proc", 0, NULL) == 0 ) {
			printf("[OK] Mounted /proc\n");
		}
		else {
			printf("[FAIL] Could not mount /proc");
		}
		
		if (mount("sysfs", "/sys", "sysfs", 0, NULL) == 0) {
			printf("[OK] Mounted /sys\n");
		}
		else {
			printf("[FAIL] Could not mount /sys");
		}

		if (mount("devtmpfs", "/dev", "devtmpfs", 0, NULL) == 0) {
			printf("[OK] Mounted /dev\n");
		}
		else {
			printf("[FAIL] Could not mount /dev");
		}
			

    while(1) {
			exec("/bin/mishell");
		}
}
