#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "command.h"
#include "../../utils/utils.h"

int cmd_compile(int argc, char **argv) {
	char code[1024] = {0};
	for (int i = 0; i < argc; i++) {
			strcat(code, argv[i]);
			strcat(code, " ");
	}

	FILE *f = fopen("/tmp/jit.c", "w");
	if (!f) {
			printf("Error: Could not create temporary file.\n");
			return 1;
	}

	fprintf(f, "#include <stdio.h>\nint main() { %s; return 0; }\n", code);
	fclose(f);

	int status = exec("/usr/bin/gcc -static /tmp/jit.c -o /tmp/output");
	if (status == 0) {
		exec("/tmp/output");
	}
	else {
		printf("GCC exited with error code %d\n", status);
	}
	return 0;
}
