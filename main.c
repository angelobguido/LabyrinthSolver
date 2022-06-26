#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "file_routines.h"
#include "global_values.h"

int main() {
	int exit = 0;

	// displays theme screen until 'ENTER' key is pressed
	clear_screen();
	display_title_screen();
	while (getchar() != '\n') {
		clear_screen();
		display_title_screen();
	}

	while(exit!=1){
		int choice=0;
		clear_screen();
		display_main_menu();

		// waits for user to select a function
		while (choice != 1 && choice != 2 && choice != 3 && choice != 4) 
			scanf(" %d", &choice);

		switch(choice){
			//new maze
			case 1:{
				clear_screen();
				display_new_maze_screenStart(); 
				char* newMazePath = load_new_maze();
				display_new_maze_screenEnd();

				if (IS_WIN)
					system("Sleep(2)");
				else
					system("sleep 2");

				printf("%s", newMazePath);
				printf("\nExibindo o labirinto a ser resolvido:\n");
				display_maze(newMazePath);

				int newMazeRows, newMazeCols;
				int ** newMaze = solve_mazeFromfile(newMazePath,&newMazeRows,&newMazeCols);

				printf("\nExibindo o labirinto resolvido:\n");
				display_maze_from_matrix(newMaze, newMazeRows, newMazeCols);
				getchar(); // this getchar stops the program from going back to main_menu (?)

				// Solve maze from file already saves the result in it
				
				// waits for user to press the 'ENTER' key to return to the main menu
				do{
					printf("\n\t\tAperte ENTER para voltar ao menu principal\n");
				}while(getchar() != '\n');
				
				free_matrix(newMaze, newMazeRows);
				free(newMazePath);
			} break;

			//load maze
			case 2:{
				int fileIndex = 0;
				char* pathToOpen = NULL;
				char* newName = new_string();

				int exitSub = 0;
				char ch = '\0';
				
				while(exitSub!=1){
					clear_screen();
					display_maze_list_screen();	
					scanf(" %c", &ch);
					switch(ch){
						case 'o':
							scanf("%d", &fileIndex);
							pathToOpen = get_path_from_index(fileIndex);
							printf("\nExibindo o labirinto %d de path %s\n",fileIndex, pathToOpen );
							display_solved_maze(pathToOpen);
							getchar();
							do{
								printf("\n\t\tAperte ENTER para voltar\n");
							}while(getchar() != '\n');
							break;
						case 'r':
							scanf("%d", &fileIndex);
							printf("Digite o nome para o qual o arquivo deve ser renomeado\n");
							scanf(" %s", newName);
							rename_file(fileIndex,newName);
							break;
						case 'd':
							scanf("%d",&fileIndex);
							remove_file(fileIndex);
							break;
						case 'M':
							exitSub = 1;
							break;
					}
				
				}
				
				free(newName);
				free(pathToOpen);

			} break;

			//gen maze
			case 3:{
				char*new_randomMaze_Name = new_string();
				int ** new_randomMaze = NULL;
				int randomMazeRows, randomMazeCols;

				clear_screen();

				printf("Digite o nome do arquivo do seu novo labirinto no formato <nome.txt>: "); //Defines random maze name
				scanf("%s", new_randomMaze_Name);

				clear_screen();
				display_rand_maze_gen_size_selection(); //Define random maze size

				printf("N° de linhas: ");
				scanf("%d", &randomMazeRows);

				printf("N° de colunas: ");
				scanf("%d", &randomMazeCols);
				
				getchar(); //receives a new line char
				clear_screen();

				new_randomMaze = random_maze(randomMazeRows, randomMazeCols); //Creates random maze

				create_gen_maze_file(new_randomMaze_Name, new_randomMaze, randomMazeRows, randomMazeCols);//saves maze in txt
				display_loading_screen();
				clear_screen();
				printf("\nO labirinto gerado foi:\n");
				printf("\n");

				display_maze_from_matrix(new_randomMaze, randomMazeRows, randomMazeCols);//prints maze

				do{
					printf("\n\t\tAperte ENTER para voltar ao menu principal\n");
				}while(getchar() != '\n');

			}break;
			
			//exit
			case 4:{
				exit = 1;
			} break;
		}
	}


	return 0;
}