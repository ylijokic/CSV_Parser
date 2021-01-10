/*
    This file contains the main entry function of the program. This file utilizes the
    Movie.h file where the Movie struct is defined, as well as the menu.h file.

    There is one function in this file:
        4.) main()
*/
#include <time.h>

#include "Movie.h"
#include "menu.h"

/*
    Functionality: 
            Main function for program. Utilizes srand() function from time.h file to generate a time stamp 
            and then calls the displayMenu() function.
    Parameters:
            N/A
    Returns:
            Return exit status
*/
int main()
{
    srand(time(0));
    displayMenu();

    return EXIT_SUCCESS;
}