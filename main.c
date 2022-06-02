#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "file_routines.h"
#include "global_values.h"

int main() {
	// displays theme screen until 'ENTER' key is pressed
	clear_screen();
	display_title_screen();
	while (getchar() != '\n') {
		clear_screen();
		display_title_screen();
	}
	
	/* MAIN MENU ENVIRONMENT */
	main_menu:
	clear_screen();
	display_main_menu();

	// waits for user to select a function
	int choice;
	while (choice != 1 && choice != 2)
		scanf("%d", &choice);
	if (choice == 1)
		goto new_maze;
	else
		goto load_maze;


	/* NEW MAZE ENVIRONMENT */
	new_maze:
	clear_screen();
	display_new_maze_screen();
	// waits for user to press the 'ENTER' key to return to the main menu
	while (getchar() != '\n');
	goto main_menu;

	/* LOAD MAZE ENVIRONMENT */
	load_maze:
	clear_screen();
	display_maze_list_screen();
	// maze selection
	goto main_menu;

	return 0;
}
