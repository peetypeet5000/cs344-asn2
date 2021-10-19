#ifndef INTERFACE_DEF
#define INTERFACE_DEF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// For struct
#include "file_parser.h"

void file_menu();
void user_menu(struct movie*);
char* get_largest_file(DIR*, bool*);
char* get_smallest_file(DIR*, bool*);
char* get_named_file(DIR*, bool*);
bool is_csv(char*);

#endif