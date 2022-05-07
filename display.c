#include <stdio.h>
#include <stdlib.h>
#include "display.h"

/* this directive is for the compiler to decide the user's operating system in order to use the correct
 * command in the system call contained in the function clear_screen()*/
#ifndef __unix__
	#define IS_WIN 0
#elif defined(_WIN32) || defined(WIN32)
	#define IS_WIN 1
#endif

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
