#ifndef FILE_PARSER
#define FILE_PARSER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#define ONID "lamontap"

struct movie
{
    char *title;
    int year;
    char *langs[5];
    int num_langs;
    float rating;
    struct movie *next;
};

struct movie *create_movie(char*);
struct movie *read_csv(char*);
void process_file(char*);
void add_movies_by_year(char*, struct movie*);
int get_random();

#endif