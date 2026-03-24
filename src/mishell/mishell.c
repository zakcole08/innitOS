/*
Zak Cole, innitOS
Copyright (C) 2026 Zak Cole

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "command.h"

#define TABLE_SIZE 64

// Global vars
char *version = "v0.1";
int last_exit_status = 0;

Command *hash_table[TABLE_SIZE];

unsigned int hash(char *name) {
    unsigned int h = 5381;
    int c;
    while ((c = *name++)) {
        h = ((h << 5) + h) + c;
    }
    return h % TABLE_SIZE;
}

void hash_insert(char *name, command_func func, char *help) {
    unsigned int index = hash(name);

    Command *new_cmd = malloc(sizeof(Command));
    new_cmd->name = name;
    new_cmd->func = func;
    new_cmd->help_text = help;

    while (hash_table[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
    }
    
    hash_table[index] = new_cmd;
}

Command* hash_lookup(char *name) {
    unsigned int index = hash(name);
    unsigned int start_index = index;

    while (hash_table[index] != NULL) {
        if (strcmp(hash_table[index]->name, name) == 0) {
            return hash_table[index];
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == start_index) break; // We searched the whole table
    }
    return NULL;
}

int main() {
	// initialise hashtable to NULL
	for(int i = 0; i < TABLE_SIZE; i++) hash_table[i] = NULL;
	
	hash_insert("help", cmd_help, "Show help menu");
	hash_insert("pwd", cmd_pwd, "Print working directory");
	hash_insert("echo", cmd_echo, "Print a string");
	hash_insert("compile", cmd_compile, "Compile and run the C code in the shell");
	hash_insert("ls", cmd_ls, "List files and directories");
	hash_insert("cat", cmd_cat, "Concatenate file / Show file contents");

	char input[1024];
	printf("innitOS %s\n", version);
	while (1) {
		printf("> ");
		if (!fgets(input, sizeof(input), stdin)) {
			break;
		}
		
		// strip trailing newline char
		input[strcspn(input, "\n")] = '\0';

		if (strlen(input) == 0) {
		 	continue;
		}

		int arg_limit = 64;
		char *argv[arg_limit];
		int argc = 0;
		char *token = strtok(input, " ");

		while (token != NULL && argc < arg_limit) {
			argv[argc++] = token;
			token = strtok(NULL, " ");
		}
		// Add null terminator to arg list
		argv[argc] = NULL;
		
		Command *cmd = hash_lookup(argv[0]);
		if (cmd) {
			last_exit_status = cmd->func(argc, argv);
		}
		else {
			//printf("Unknown command: %s\n", input);
			last_exit_status = cmd_compile(argc, argv);
		}
	}
	return 0;
}
