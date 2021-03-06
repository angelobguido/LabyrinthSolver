#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "file_routines.h"
#include "global_values.h"
#include "maze.h"

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
	
	strcat(command, filepath);
	system(command);

	free(command);
}

void remove_file(int index) {
	DIR *folder;
	struct dirent *entry;
	int dir_index = 0;
	char *filepath = new_string();

	while(1) {
		// tries to open the directory
		if (IS_WIN) {
			folder = opendir(".\\mazes");
			strcpy(filepath, ".\\mazes\\");
		} 
		else {
			folder = opendir("./mazes");
			strcpy(filepath, "./mazes/");
		}
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir mazes");
	}

	// searches for the file and then deletes it
	while ((entry = readdir(folder))) {
		dir_index++;
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			dir_index--;

		if (dir_index == index) {
			strcat(filepath, entry -> d_name);
			sys_remove_file(filepath);
		}
	}
	
	// error handling -- bad index
	if (dir_index == 0) {
		printf("Could not find file with this index.\n");
		closedir(folder);
		return;
	}

	free(filepath);
	closedir(folder);
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
	
	strcat(command, filepath);
	strcat(command, divider);
	strcat(command, new_name);
	system(command);

	free(command);
}

void rename_file(int index, char* new_name) {
	DIR *folder;
	struct dirent *entry;
	int dir_index = 0;
	char *filepath = new_string();
	char *filepathOld = new_string();

	while(1) {
		// tries to open the directory
		if (IS_WIN) {
			folder = opendir(".\\mazes");
			strcpy(filepath, ".\\mazes\\");
		}
		else {
			folder = opendir("./mazes");
			strcpy(filepath, "./mazes/");
		}
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir mazes");
	}

	// searches for the file and then renames it 
	while ((entry = readdir(folder))) {
		dir_index++;
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
			dir_index--;

		if (dir_index == index) {
			strcpy(filepathOld,filepath);
			strcat(filepathOld, entry -> d_name);
			strcat(filepath, new_name);
			sys_rename_file(filepathOld, filepath);
		}
	}
	
	// error handling -- bad index
	if (dir_index == 0) {
		printf("Could not find file with this index.\n");
		closedir(folder);
		return;
	}

	free(filepath);
	free(filepathOld);
	closedir(folder);	
}

int** read_text_file_to_matrix(char* filepath, int* rows, int* columns){
	int**matrix = NULL;
	int x=0, y=0;
	int i, j;
	int max_columns = 0;
	int max_rows = 1;
	char ch;
	FILE* ptr = fopen(filepath, "r");

	matrix = (int**)malloc(sizeof(int*));
	matrix[0] = NULL;

	while(max_columns = (max_columns>x) ? (max_columns) : (x), (ch=fgetc(ptr))!=EOF ) {
		switch(ch) {
		case 'I':
			matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
			matrix[y][x] = -1;
			// printf("%c ", 'I');
			x++;
			break;
		case 'F':
			matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
			matrix[y][x] = -2;
			// printf("%c ", 'F');
			x++;
			break;
		case ' ':
			matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
			matrix[y][x] = 0;
			// printf("%c ", ' ');
			x++;
			break;
		case '\n':y++;
			max_rows = y+1;
			matrix = (int**)realloc(matrix, sizeof(int*)*max_rows);
			matrix[y] = NULL;
			// printf("%c", '\n');
			x = 0;
			break;
		default:
			matrix[y] = (int*)realloc(matrix[y], sizeof(int)*(x+1));
			matrix[y][x] = -3;
			// printf("%c ", '#');
			x++;
			break;
		}
	}

	for(i=0;i<max_rows;i++){
		matrix[i] = (int*)realloc(matrix[i], sizeof(int)*max_columns);
		for(j=0;j<max_columns;j++){
			if(matrix[i][j]!=-1 &&matrix[i][j] != -2 && matrix[i][j] != -3){
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
	DIR* folder;

	scanf("%s", filepath);
	//printf("\nTrying to get the name of the filepath %s\n", filepath);

	char *filename = get_filename(filepath);
	//printf("\nTrying to cocatenate the path with the filename %s\n", filename);
	if (IS_WIN){
		strcpy(path,".\\mazes\\");
		strcat(path,filename);
	}
	else{
		strcpy(path,"./mazes");
		strcat(path,filename);
	}

	while(1) {
		// tries to open the directory
		if (IS_WIN) {
			folder = opendir(".\\mazes");
		}
		else {
			folder = opendir("./mazes");
		}
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir mazes");
	}
	//printf("\nTrying to open the full path %s\n",path);
	// opens new file to be saved
	FILE *file = fopen(path, "w");
	if (file == NULL) {
		printf("Could not load file");
		return NULL;
	}

	//printf("\nTrying to read text file to matrix with path %s\n", filepath);
	maze = read_text_file_to_matrix(filepath, &nrows, &ncols);
	// printf("\nWe got this matrix for the maze:\n");
	// for(int i=0;i<nrows;i++){
	// 	for(int j=0;j<ncols;j++){
	// 		printf("%d ", maze[i][j]);
	// 	}
	// 	printf("\n");
	// }


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
	free(filepath);

	return path;
}

char *get_path_from_index(int fileIndex){
	DIR *folder;
	struct dirent *entry;
	int dir_index = 0,i_files=0;
	char *filepath = new_string();

	while(1) {
		// tries to open the directory
		if (IS_WIN) {
			folder = opendir(".\\mazes");
			strcpy(filepath, ".\\mazes\\");
		}
		else {
			folder = opendir("./mazes");
			strcpy(filepath, "./mazes/");
		}
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir mazes");
	}

	while ((entry = readdir(folder))) {
		i_files++;
		//printf("\non first if on iteration %d with entry->d_name \n%s", i_files,entry->d_name);
		if(entry->d_name[0] == '.'){
			i_files--;
			continue;
		}
		//printf("\noff first if on iteration %d with entry->d_name \n%s", i_files,entry->d_name);
		if(i_files == fileIndex){
			strcat(filepath, entry ->d_name);
			break;
		}
		
	}

	return filepath;
}

// This function is still not integrated with the system
// its purpose is to solve a maze from a filepath, meaning it would integrate solve_maze()
// with the file_routines (it is not intended to use maze.c functions inside display.c, so i created this)
// but if it returns a maze, the display_maze would need a file, 
// so it would be needed to create another function (print_maze?)
// we also need to think about if the user will save the solved maze somewhere everytime or not
// if it does, the main will have to save or call some function to save it
// if it does not(seems to make more sense), we need to implement more UI so that the user gives a path to create a file
// creating files may be tricky and we need to get this right, so i didnt finish this funciton yet

int **solve_mazeFromfile(char * pathOriginalMaze, int* lines, int*columns){
	int **maze;
	maze = read_text_file_to_matrix(pathOriginalMaze,lines,columns);
	solve_maze(maze,*lines,*columns);
	FILE*ptr = fopen(pathOriginalMaze, "w");

	for(int i = 0; i < (*lines); i++){//prints maze in .txt file
		for(int j = 0; j < (*columns); j++){
			switch(maze[i][j]){
				case -3: 
					fprintf(ptr, "#");
					break;
				case -2: 
					fprintf(ptr, "F");
					break;
				case -1: 
					fprintf(ptr, "I");
					break;
				case 1: 
					fprintf(ptr, ".");
					break;
				case 0: 
					fprintf(ptr, " ");
					break;
			}
		}	
		fprintf(ptr, "\n");	
	}
	fclose(ptr);
	
	return maze;
}


//Takes care of file routines within random maze creation
int** random_maze(int randomMazeRows, int randomMazeCols){

	int** randomMaze;

	randomMaze = create_random_maze(randomMazeRows, randomMazeCols);//Creates the random maze

	return randomMaze;
}


void create_gen_maze_file(char* filename, int**genMaze,  int genMazeRows, int genMazeCols){
	DIR *folder;
	FILE *maze;
	char *path = new_string();
	
	while(1) {
		// tries to open the directory
		if (IS_WIN) {
			folder = opendir(".\\gen_mazes");
		}
		else {
			folder = opendir("./gen_mazes");
		}
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir gen_mazes");
	}

	if (IS_WIN){
		strcpy(path,".\\gen_mazes\\");
		strcat(path,filename);
	}
	else{
		strcpy(path,"./gen_mazes/");
		strcat(path,filename);
	}

	maze = fopen(path, "w");//creates new gen maze file

	if(maze == NULL){
        // File not created hence exit 
        printf("Unable to create file.\n");
	}

	for(int i = 0; i < genMazeRows; i++){//prints maze in .txt file
		for(int j = 0; j < genMazeCols; j++){
			switch(genMaze[i][j]){
				case -3: 
					fprintf(maze, "#");
					break;
				case -2: 
					fprintf(maze, "F");
					break;
				case -1: 
					fprintf(maze, "I");
					break;
				case 0: 
					fprintf(maze, " ");
					break;
			}
		}	
		fprintf(maze, "\n");	
	}
	fclose(maze);

}

void free_matrix(int**matrix, int rows){
    int i;
    for(i=0;i<rows;i++){
        free(matrix[i]);
    }
    free(matrix);
}