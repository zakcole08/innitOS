#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "command.h"

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

    int compiled_code = system("/usr/bin/gcc -static /tmp/jit.c -o /tmp/jit_bin && /tmp/jit_bin 2>&1");

    if (compiled_code != 0) {
        printf("innitOS: '%s' is neither a command nor valid C code.\n", argv[0]);
        return 127;
    }

    system("/tmp/jit_bin");

    unlink("/tmp/jit.c");
    unlink("/tmp/jit_bin");

    return 0;
}
