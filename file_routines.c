#include <stdlib.h>
#include <stdio.h>
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
char* load_new_maze() {}
