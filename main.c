#include "main.h"

/*
Checks the provided command line argument, starts functions
to process file & start user interactive menu
*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies_sample_1.csv\n");
        return EXIT_FAILURE;
    }
    //Read in movied
    struct movie *list = process_file(argv[1]);

    // Start interactive menu
    user_menu(list);
    
    return EXIT_SUCCESS;
}