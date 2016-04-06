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

//Le but principal de cette fonction est de d�couper la cha�ne d'arguments s�par�s par des espaces
unsigned int splitArgs(const char * string, char *** splitStr);
void cd(int argc, char* argv[]);
