#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#ifdef WIN32
#include <Windows.h>
#else
#include <unistd.h>
char *get_current_dir_name(void);
#endif 

#define ARG_SEPARATOR ' '  //TEST

//Prototypes

//Le but principal de cette fonction est de découper la chaîne d'arguments séparés par des espaces
unsigned int splitArgs(const char * string, char *** splitStr);
void cd(int argc, char* argv[]);
