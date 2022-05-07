#include <stdlib.h>
#include <string.h>
#include "file_routines.h"
#include "global_values.h"

char* new_string() {
	return (char*)calloc(STRSIZE, sizeof(char));
}

void sys_remove_file(char* filepath) {
	char* command = new_string();
	char win_cmd[] = "DEL ";
	char unix_cmd[] = "rm ";

	if (IS_WIN)
		strcpy(command, win_cmd);
	else
		strcpy(command, unix_cmd);
	
	system(strcat(command, filepath));
}

void sys_rename_file(char* filepath, char* new_name) {
	char* command = new_string();
	char win_cmd[] = "REN ";
	char unix_cmd[] = "mv ";
	char divider[] = " ";

	if (IS_WIN)
		strcpy(command, win_cmd);
	else
		strcpy(command, unix_cmd);
	
	system(strcat(strcat(strcat(command, filepath), divider), new_name));
}
