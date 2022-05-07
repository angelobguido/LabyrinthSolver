#ifndef DISPLAY_H
#define DISPLAY_H

/* this directive is for the compiler to decide the user's operating system in order to use the correct
 * command in the system call contained in the function clear_screen()*/
#ifndef __unix__
	#define IS_WIN 0
#elif defined(_WIN32) || defined(WIN32)
	#define IS_WIN 1
#endif

void clear_screen();
void display_title_screen();
void display_main_menu();

#endif
