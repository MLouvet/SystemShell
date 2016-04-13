#include <stdlib.h>
#include <stdio.h>
#include "preliminaire.h"
#include "fonctions.h"
#include "commandShell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 100


void cd(char* arguments[])
{
	if (chdir(arguments[1]) == -1)
		printf("\nCD impossible : %s n existe pas\n", arguments[1]);
}

void exitShell()
{

}
