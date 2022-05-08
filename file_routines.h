#ifndef FILE_ROUTINES_H
#define FILE_ROUTINES_H

char* new_string();
void sys_remove_file(char* filepath);
void sys_rename_file(char* filepath, char* new_name);
int** read_text_file_to_matrix(char* filepath, int*rows, int*columns);

#endif
