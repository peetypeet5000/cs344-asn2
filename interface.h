#ifndef INTERFACE_DEF
#define INTERFACE_DEF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// For struct
#include "file_parser.h"

void user_menu(struct movie*);
void get_movies_year(struct movie*);
void get_movies_lang(struct movie*);
void get_movies_rating(struct movie*);
void free_list(struct movie*);

#endif