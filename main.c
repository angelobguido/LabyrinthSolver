#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "file_routines.h"
#include "global_values.h"

int main() {
	int choice=0,fileIndex=0,localFlag = 0;;
	char ch, *newName,*pathToOpen = new_string();

	// displays theme screen until 'ENTER' key is pressed
	clear_screen();
	display_title_screen();
	while (getchar() != '\n') {
		clear_screen();
		display_title_screen();
	}
	
	/* MAIN MENU ENVIRONMENT */
	main_menu:
	choice=0;
	clear_screen();
	display_main_menu();

	// waits for user to select a function
	while (choice != 1 && choice != 2)
		scanf("%d", &choice);
	if (choice == 1)
		goto new_maze;
	else
		goto load_maze;


	/* NEW MAZE ENVIRONMENT */
	new_maze:
	clear_screen();
	display_new_maze_screen(); // this function maybe does too much things(input etc, it is not just a display function)
	// read the end of file_routines.c to see the dillema that implies on our structure, since this is printing only the
	// unsolved version of the maze
	// waits for user to press the 'ENTER' key to return to the main menu
	while (getchar() != '\n');
	goto main_menu;

	/* LOAD MAZE ENVIRONMENT */
	load_maze:
	clear_screen();
	display_maze_list_screen();

	ch = 0;
	do{
		ch = getchar();
		switch(ch){
			case 'o':
				scanf("%d", &fileIndex);
				pathToOpen = get_path_from_index(fileIndex);
				printf("\nExibindo o labirinto %d de path %s\n",fileIndex, pathToOpen );
				display_maze(pathToOpen);
				break;
			case 'r':
				scanf("%d", &fileIndex);
				printf("Digite o nome para o qual o arquivo deve ser renomeado\n");
				scanf("%s", newName);
				rename_file(fileIndex,newName);
				break;
			case 'd':
				scanf("%d",&fileIndex);
				remove_file(fileIndex);
				break;
			case 'M':
				localFlag = 1;
				break;
		}
	}	while(ch != 'M' && !localFlag);
	goto main_menu;

	return 0;
}
