#ifndef GLOBAL_VALUES_H
#define GLOBAL_VALUES_H

/* this directive is for the compiler to decide the user's operating system in order to use the correct
 * command in the system calls contained in the functions throughout the code*/
#ifdef __unix__
	#define IS_WIN 0
#elif _WIN32 || _WIN64
	#define IS_WIN 1
#endif

// default size declaration of strings
#define STRSIZE 100

#endif
