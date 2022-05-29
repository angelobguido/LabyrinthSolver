#include <stdio.h>
#include <stdlib.h>
#include "display.h"
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
	maze = read_text_file_to_matrix(char* filepath, &nrows, &ncols);

	//  this will loop through the matrix
	// that is already mapped with only 
	//-3,-2,-1,0 or 1 flags
	for(int i=0;i<nrows;i++){
		for(int j=0;j<ncols;j++){
			switch(maze[i][j]){
				case -3: 
					printf("*");
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
	
	char* filepath = load_new_maze();

	printf("  ____________________________________\n");
	printf("\n");	
	printf("\n");	
	printf("\n");	
	printf("###########################################\n");
	
	sleep(2);	

	display_maze(filepath);
}

// show the name of the maze files that are in the folder
void enlist_mazes();

void display_maze_list_screen() {

	printf("########## ACESSAR LABIRINTOS JÁ RESOLVIDOS ###########\n");
	printf("\n");
	printf("\n");

	enlist_mazes();

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("Aperte "j" para descer e "k" para subir a lista.\n"); // implementar
	printf("Aperte "r" e o número "X" para renomear o labirinto X.\n"); // implementar
	printf("Aperte "d" e o número "X" para deletar o labirinto X.\n"); // implementar
	printf("\n");
	printf("#######################################################\n");

}
