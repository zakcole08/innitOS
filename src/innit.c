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
