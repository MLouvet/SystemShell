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


void lanceProg(int argc, char* arguments[])
{
	char* cheminCMD = NULL;
	char* args = NULL;
	int i = 0;

	// Creation du chemin absolu
	strcat(cheminCMD, "./");
	strcat(cheminCMD, arguments[0]);
	arguments[0] = realloc(arguments[0], strlen(arguments[0] + 4) * sizeof(char));
	strcat(arguments[0], ".exe");

	for (int i = 1; i < argc; i++)
	{
		strcat(args, arguments[i]);
	}
	if (execlp(cheminCMD, args, NULL) == -1) // Si l'execution du nom de programme est incorrecte
		printf("\nErreur : %s n'existe pas\n", cheminCMD);
}

