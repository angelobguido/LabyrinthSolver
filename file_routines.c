#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file_routines.h"
#include "global_values.h"

char* new_string() {
	return (char*)calloc(STRSIZE, sizeof(char));
}

char* get_filename(char* filepath) {
	char* filename = new_string();
	int slashes = 0, i, j, last_index;

	// counts how many slashes there are in the string
	for (i = 0; filepath[i] != '\0'; i++) {
		if (IS_WIN) {
			if (filepath[i] == 92)
				last_index = i;
		}
		else {
			if (filepath[i] == 47)
				last_index = i;
		}
	}

	// copies file's name to filename
	j = 0;
	for (i = last_index; filepath[i-1] != '\0'; i++)
		filename[j++] = filepath[i];

	return filename;
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

int** read_text_file_to_matrix(char* filepath, int*rows, int*columns){
	int**matrix = NULL;
	int x=0, y=0;
	int i, j;
	int max_columns = 0;
	int max_rows = 1;
	char ch;
	FILE* ptr = fopen(filepath, "r");

	matrix = (int**)malloc(sizeof(int*));

	while(max_columns = (max_columns>x)?(max_columns):(x),(ch=fgetc(ptr))!=EOF){
		switch(ch){
			case 'I': matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
					  matrix[y][x] = -1;
					  x++;
					  break;
			case 'F': matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
					  matrix[y][x] = -2;
					  x++;
					  break;
			case ' ': matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
					  matrix[y][x] = 0;
					  x++;
					  break;
			case '\n':y++;
					  max_rows = y+1;
					  matrix = (int**)realloc(matrix, sizeof(int*)*max_rows);
					  x = 0;
					  break;
			default:  matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
					  matrix[y][x] = -3;
					  x++;
					  break;
		}
	}
	
	for(i=0;i<max_rows;i++){
	    matrix[i] = (int*)realloc(matrix[i], sizeof(int)*max_columns);
	    for(j=0;j<max_columns;j++){
	        if(matrix[i][j]!=-1&&matrix[i][j]!=-2&&matrix[i][j]!=-3){
	            matrix[i][j]=0; 
	        }
	    }
	}
	
	*columns = max_columns;
	*rows = max_rows;

    fclose(ptr);
	
	return matrix;
}

/* function used to get new mazes in the option 'carregar novo labirinto' ;
 * the maze is saved in ./mazes folder already processed with the correct chars ;
 * returns the filepath to the new loaded maze */
char* load_new_maze() {
	int nrows, ncols, **maze;
	char *path = new_string();
	char *filepath = new_string();

	scanf("%s", filepath);

	char *filename = get_filename(filepath);
	if (IS_WIN)
		path = strcat(".\\mazes\\",filename);
	else
		path = strcat("/mazes/",filename);
	
	// opens new file to be saved
	FILE *file = fopen(path, "w");
	if (file == NULL) {
		printf("Could not load file");
		return NULL;
	}

	maze = read_text_file_to_matrix(filepath, &nrows, &ncols);

	//  this will loop through the matrix
	// that is already mapped with only 
	//-3,-2,-1,0 or 1 flags
	for(int i = 0; i < nrows; i++){
		for(int j = 0; j < ncols; j++){
			switch(maze[i][j]){
				case -3: 
					fprintf(file, "#");
					break;
				case -2: 
					fprintf(file, "F");
					break;
				case -1: 
					fprintf(file, "I");
					break;
				case 0: 
					fprintf(file, " ");
					break;
				case 1:
					fprintf(file, ".");
					break;
			}
		}	
		fprintf(file, "\n");	
	}

	fclose(file);

	return path;
}
