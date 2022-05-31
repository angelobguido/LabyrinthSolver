#ifndef FILE_ROUTINES_H
#define FILE_ROUTINES_H

char* new_string();
char* get_filename(char* filepath);
void sys_remove_file(char* filepath);
void remove_file(int index);
void sys_rename_file(char* filepath, char* new_name);
void rename_file(int index, char* new_name);
int** read_text_file_to_matrix(char* filepath, int*rows, int*columns);
char* load_new_maze();

#endif
