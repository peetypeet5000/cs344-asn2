#include "file_parser.h"

/* Parse the current line which is space delimited and create a
*  movie struct with the data in this line
*/
struct movie *create_movie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));

    // For use with strtok_r
    char *saveptr;
    char *langptr;

    // Get title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // Get year
    token = strtok_r(NULL, ",", &saveptr);
    // Convert to an int
    int year_int = atoi(token);
    currMovie->year = year_int;

    // Get lang array
    token = strtok_r(NULL, ",", &saveptr);
    // Allocate space for the array excluding the []
    char* lang_array = calloc(strlen(token) - 1, sizeof(char));
    // Copy string without first and last char
    strncpy(lang_array, token + 1, strlen(token) - 2);

    // Get first language token
    int lang_num = 0;
    token = strtok_r(lang_array, ";", &langptr); 
    // Keep tokenizing until no more
    while(token != NULL) {
        // Allocated space, copy in, get next token
        currMovie->langs[lang_num] = calloc(strlen(token) + 1, sizeof(char));
        strcpy(currMovie->langs[lang_num++], token);
        token = strtok_r(NULL, ";", &langptr);
    }
    // Save the number of languages in the struct
    currMovie->num_langs = lang_num;
    free(lang_array);

    

    // Get rating
    token = strtok_r(NULL, ",", &saveptr);
    // Convert to a float
    float rating_float = atof(token);
    currMovie->rating = rating_float;

    // Set the next node to NULL in the newly created movies entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of movies by parsing data from
* each line of the specified file.
*/
struct movie *read_csv(char *filePath)
{
    // Open the specified file for reading only
    FILE *moviesFile = fopen(filePath, "r");

    char *currLine = NULL;
    int num_lines = 0;
    size_t len = 0;
    ssize_t nread;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    //Skip first line
    nread = getline(&currLine, &len, moviesFile);

    // Read the file line by line
    while ((nread = getline(&currLine, &len, moviesFile)) != -1)
    {
        // Get a new movie node corresponding to the current line
        struct movie *newNode = create_movie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }

        //Increment # lines read
        num_lines++;
    }

    free(currLine);
    fclose(moviesFile);

    printf("Processed file %s and parsed data for %i movies\n\n", filePath, num_lines);
    return head;
}



void process_file(char* file) {
    char parent_dir_name[28];
    int random_val = get_random();

    // Read given file and create linked list
    struct movie* list = read_csv(file);

    // Format parent directory name and create dir
    sprintf(parent_dir_name, "%s.movies.%d", ONID, random_val);
    mkdir(parent_dir_name, 750);

    // Open new directory
    DIR* movies_dir = opendir(file);

    // Add movie text files
    add_movies_by_year(parent_dir_name, list);


}


void add_movies_by_year(char* dir, struct movie* list) {
    struct movie* curr = list;
    char file_name[37];
    char file_line[256];

    // Loop thru list for each valid year 
    for(int i = 1900; i < 2022; i++) {
        // Loop thru list, keep track of highest
        while (curr != NULL) {
            // If the year is found
            if(curr->year == i) {
                sprintf(file_name, "%s/%d.txt", dir, i);
                int year_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 640);

                // Print any errors
                if(year_file == -1){
                    perror("Error");
                    exit(1);
	            }

                // Write movie to file
                sprintf(file_line, "%s\n", curr->title);
                int bytes = write(year_file, file_line, strlen(file_line));
                int len = strlen(file_line);
                printf("printed %d bytes len %d", bytes, len);

                // Close file
                close(year_file);
            }
        // Move to next node in list
        curr = curr->next;
        }

        // Reset to head of list
        curr = list;
    }
    printf("\n");
}


int get_random() {
    // Seed function
    srand(time(NULL));

    int random = rand();

    // Use modulus to get in range
    random = random % 100000;

    return random;
}