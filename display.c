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

//displays a txt cointaining a maze
void display_maze(char* filepath) {}

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
