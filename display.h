#ifndef DISPLAY_H
#define DISPLAY_H

void clear_screen();
void display_title_screen();
void display_main_menu();
void display_maze(char* filepath);
void display_solved_maze(char* filepath);
void display_new_maze_screenStart();
void display_new_maze_screenEnd();
void enlist_mazes();
void display_maze_list_screen();
void display_maze_from_matrix(int **maze,int nrows,int ncols);
void display_rand_maze_gen_size_selection();
void display_loading_screen();

#endif
