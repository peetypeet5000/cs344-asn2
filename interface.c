#include "interface.h"

// Driver function for the user menu, runs forever
//until user selects '4' to exit.
void file_menu() {
    bool good = false;
    char* file;
    int selection = 0;

    // Delcare dir* var, open current directory 
    DIR* working_dir =  opendir(".");
    struct dirent *aDir;

    // Infitintly loop menu until a valid selection is made
    while(good == false) {
        printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\n");
        printf("Enter a choice from 1 to 3: ");
        scanf ("%d", &selection);

        switch(selection) {
            // Get largest file
            case 1:
                file = get_largest_file(working_dir, &good);
                break;
            // Get smallest file
            case 2:
                file = get_smallest_file(working_dir, &good);
                break;
            // Get custom file
            case 3:
                file = get_named_file(working_dir, &good);
                break;
            // Invalid Choice
            default:
                printf("\nYou entered an incorrect choice. Try again.\n");
                good = false;
                break;
        }

        // Rewind dir for the next loop if nessesary
        rewinddir(working_dir);
    }

    // If file sucessfully found, process it
    printf("\nNow processing the chosen file named %s\n", file);
    process_file(file);

    // Close the dir we opened
    closedir(working_dir);
}


// Loops thru given dir and finds largest file
// using the stat() function
// good is passed by ref to record if it was sucessful
char* get_largest_file(DIR* dir, bool* good) {
    struct dirent* file;
    struct stat file_stat;
    long long int biggest_size = 0;
    char* biggest_name;

    // Read each file in directory
    while((file = readdir(dir)) != NULL){
        // If the first part of the name matches the prefix, check it
        if((strncmp(file->d_name, "movies_", strlen("movies_")) == 0) && (is_csv(file->d_name) == true)) {
            stat(file->d_name, &file_stat);
            
            // If given file is largest, record it
            if(file_stat.st_size > biggest_size) {
                biggest_name = file->d_name;
                biggest_size = file_stat.st_size;
            }
        }

    }

    // If a file was found, return it
    if(biggest_size > 0) {
        *good = true;
        return biggest_name;
    } else {
        printf("No matching files found\n");
        *good = false;
        return "";
    }
}


// Loops thru given dir and finds smallest file
// using the stat() function
char* get_smallest_file(DIR* dir, bool* good) {
    struct dirent* file;
    struct stat file_stat;
    long long int smallest_size = 0;
    char* smallest_name;

    // Read each file in directory
    while((file = readdir(dir)) != NULL){
        // If the first part of the name matches the prefix, check it
        if((strncmp(file->d_name, "movies_", strlen("movies_")) == 0) && (is_csv(file->d_name) == true)) {
            stat(file->d_name, &file_stat);
            
            // If given file is smallest or the first one, record it
            if(file_stat.st_size < smallest_size || smallest_size == 0) {
                smallest_name = file->d_name;
                smallest_size = file_stat.st_size;
            }
        }

    }

    // If a file was found, return it
    if(smallest_size > 0) {
        *good = true;
        return smallest_name;
    } else {
        // If not found, print error and return nothing
        printf("No matching files found\n");
        *good = false;
        return "";
    }
}



// Accepts user inputs then loops thru
// given dir to check if file exists. If so, returns name
char* get_named_file(DIR* dir, bool* good) {
    char user_input[255];
    struct dirent* file;
    struct stat file_stat;

    printf("\nEnter the complete file name: ");
    scanf ("%s", user_input);

    // Read each file in directory
    while((file = readdir(dir)) != NULL){
        // If the file in the directory matches the user input, return it
        if((strncmp(file->d_name, user_input, strlen(file->d_name)) == 0) && strlen(user_input) == strlen(file->d_name)) {
            *good = true;
            return file->d_name;
        }

    }

    // If nothing was found, print error
    printf("\nThe file %s was not found. Try again.\n", user_input);
    *good = false;
    return "";

}



// Checks that the extension on a file
// name is .csv
bool is_csv(char* file) {
    // Find the last occurance of the . in a name
    char* file_end = strrchr(file, '.');
   
   // If it's not at the end of the file, check the last 4 characters are .csv
   if(file_end != NULL) {
        if(strncmp(file_end, ".csv", 4) == 0) {
            return true;
        }
   }

    return false;
}

