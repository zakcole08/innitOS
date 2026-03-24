#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int cmd_cd(int argc, char **argv) {
	char *dir_name = argv[1];
	
	DIR* dir = opendir(dir_name);
	if (dir) {
		// dir exists
		closedir(dir);
	}
	else if (errno == ENOENT) {
		printf("FAILURE: No such directory.\n");
	} else {
		printf("FAILURE: Could not open %s", dir_name);
	}
	if (chdir(argv[1]) != 0) {
		printf("FAILURE: Could not change into directory \"%s\". Check the path and permissions", dir_name);
	}
	return 0;
}


