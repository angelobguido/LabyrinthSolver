#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "display.h"
#include "file_routines.h"
#include "global_values.h"

// clears the console
void clear_screen() {
	if (IS_WIN)
		system("cls");
	else
		system("clear");
}

// displays the title screen
void display_title_screen() {

	printf("    ____  _____ ____   ___  _ __     _______ ____   ___  ____    ____  _____    \n");
	printf("   |  _ \\| ____/ ___| / _ \\| |\\ \\   / / ____|  _ \\ / _ \\|  _ \\  |  _ \\| ____|   \n");
	printf("   | |_) |  _| \\___ \\| | | | | \\ \\ / /|  _| | | | | | | | |_) | | | | |  _|     \n");
	printf("   |  _ <| |___ ___) | |_| | |__\\ V / | |___| |_| | |_| |  _ <  | |_| | |___    \n");
	printf("   |_| \\_\\_____|____/ \\___/|_____\\_/  |_____|____/ \\___/|_| \\_\\ |____/|_____|   \n");
	printf("                                                                                \n");
	printf("            _        _    ____ ___ ____  ___ _   _ _____ ___  ____              \n");
	printf("           | |      / \\  | __ )_ _|  _ \\|_ _| \\ | |_   _/ _ \\/ ___|             \n");
	printf("           | |     / _ \\ |  _ \\| || |_) || ||  \\| | | || | | \\___ \\             \n");
	printf("           | |___ / ___ \\| |_) | ||  _ < | || |\\  | | || |_| |___) |            \n");
	printf("           |_____/_/   \\_\\____/___|_| \\_\\___|_| \\_| |_| \\___/|____/             \n");
	printf("                                                                                \n");
	printf("					                                                            \n");
	printf("                         APERTE \"ENTER\" PARA INICIAR                             \n");

}

// displays the main menu
void display_main_menu() {

	printf("## BEM-VINDO AO RESOLVEDOR DE LABIRINTOS ##\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("* Escolha um opção:\n");
	printf("   1. Carregar um novo labirinto\n");
	printf("   2. Acessar labirintos já resolvidos\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("###########################################\n");

}

//displays a txt on screen cointaining a maze
void display_maze(char* filepath) {
	int nrows, ncols, **maze;
	maze = read_text_file_to_matrix(filepath, &nrows, &ncols);

	//  this will loop through the matrix
	// that is already mapped with only 
	//-3,-2,-1,0 or 1 flags
	for(int i=0;i<nrows;i++){
		for(int j=0;j<ncols;j++){
			switch(maze[i][j]){
				case -3: 
					printf("#");
					break;
				case -2: 
					printf("F");
					break;
				case -1: 
					printf("I");
					break;
				case 0: 
					printf(" ");
					break;
				case 1:
					printf(".");
					break;
			}
		}	
		printf("\n");	
	}

	return;
}

// displays new maze screen
void display_new_maze_screen() {
	printf("####### CARREGAR UM NOVO LABIRINTO ########\n");
	printf("\n");	
	printf("\n");	
	printf(" * Digite o caminho para o arquivo:\n");
	printf("  ____________________________________\n");
	printf("  ");

	char* filepath = load_new_maze();

	printf("  ____________________________________\n");
	printf("\n");	
	printf("\n");	
	printf("\n");	
	printf("###########################################\n");
	
	if (IS_WIN)
		system("Sleep(2000)");
	else
		system("sleep(2)");

	display_maze(filepath);
	printf("\n\t\tAperte ENTER para voltar ao menu principal\n");
}

// show the name of the maze files that are in the folder
void enlist_mazes() {
	DIR *folder;
	struct dirent *entry;
	int n_files = 0;

	while(1) {
		// tries to open the directory
		if (IS_WIN)
			folder = opendir(".\\mazes");
		else
			folder = opendir("./mazes");
		// if directory doesn't exist, creates it
		if (folder != NULL)
			break;
		system("mkdir mazes");
	}

	// reads and prints the name of the files in the folder
	while ((entry = readdir(folder))) {
		n_files++;
		if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
			n_files--;
			continue;
		}
		printf("%d: %s\n", n_files, entry->d_name);
	}

	closedir(folder);
}

void display_maze_list_screen() {

	printf("########## ACESSAR LABIRINTOS JÁ RESOLVIDOS ###########\n");
	printf("\n");
	printf("\n");

	enlist_mazes();

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Aperte \"j\" para descer e \"k\" para subir a lista.\n"); // implementar
	printf("Aperte \"r\" e o número \"X\" para renomear o labirinto X.\n"); // implementar
	printf("Aperte \"d\" e o número \"X\" para deletar o labirinto X.\n"); // implementar
	printf("\n");
	printf("#######################################################\n");

}
