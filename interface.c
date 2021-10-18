#include "interface.h"

#define FILE_PREFIX = "movies_"
#define ONID = "lamontap"

// Driver function for the user menu, runs forever
//until user selects '4' to exit.
void file_menu() {
    bool good = true;
    char* file;
    int selection = 0;

    // Delcare dir* var, open current directory 
    DIR* working_dir =  opendir(".");
    struct dirent *aDir;

    printf("\nWhich file you want to process?\nEnter 1 to pick the largest file\nEnter 2 to pick the smallest file\nEnter 3 to specify the name of a file\n\n");
    printf("Enter a choice from 1 to 3: ");
    scanf ("%d", &selection);

    switch(selection) {
        // Get largest file
        case 1:
            file = get_largest_file(working_dir);
            break;
        // Get smallest file
        case 2:
            file = get_smallest_file(working_dir);
            break;
        // Get custom file
        case 3:
            break;

        // Invalid Choice
        default:
            printf("\nYou entered an incorrect choice. Try again.\n");
            good = false;
            break;
    }

    //If file sucessfully found, process it
    if(good == true) {
        printf("Now processing the chosen file named %s", file);
        //process_file(file);

        // Clear string memory
        //free(file);
    }
}


char* get_largest_file(DIR* dir) {
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
        return biggest_name;
    } else {
        printf("No matching files found\n");
        return "";
    }
}



char* get_smallest_file(DIR* dir) {
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
        return smallest_name;
    } else {
        printf("No matching files found\n");
        return "";
    }
}



bool is_csv(char* file) {
    char* file_end = strrchr(file, '.');
   
   if(file_end != NULL) {
        if(strncmp(file_end, ".csv", 4) == 0) {
            return true;
        }
   }


    return false;
}

