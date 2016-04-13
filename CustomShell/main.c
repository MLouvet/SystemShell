#include <stdio.h>
#include <stdlib.h>
#include "preliminaire.h"
#include "CustomShell.h"
#include "simpleio.h"

#ifndef WIN32
#include <unistd.h>
#include <sys/wait.h>

#else
typedef int pid_t;
#endif // WIN32

#define BUFFER_SIZE 100

char* get_current_dir_name();

int main(int argc, char* argv[])
{
	char* buf;
	char ** splitBuf = NULL;
	int nbArgs = 0;


	while (true)
	{
		printf("\n%s > ", get_current_dir_name()); // Affiche le chemin absolu du repertoire courant

		if ((buf = lireChaine()) == NULL || strlen(buf) == 0)			return EXIT_SUCCESS;
		nbArgs = splitArgs(buf, &splitBuf);
		free(buf);

		//On a récupéré les différents arguments,
		//on fait des choses avec.
		for (int i = 0; i < nbArgs; i++)
			printf("\nArg(%d) = %s", i, splitBuf[i]);

		pid_t pid;
		pid = fork();
		if (pid < 0) //  erreur lors du fork
		{
			printf("\n Erreur fork");
			exit(EXIT_FAILURE);
		}

		//Sélection du programme
		if (pid == 0) // on cherche à executer le programme de la ligne de cmd dans le processus fils
		{

			if (splitBuf[0] == "cd") cd(splitBuf);
			else
				lanceProg(nbArgs, splitBuf);
		}
		else
			waitpid(-1, NULL, 0); // Le pere attend la fin de l'execution de la ligne de commande rentree du fils
		//printf("\n%s > ", get_current_dir_name()); // Affiche le chemin absolu du repertoire courant

	}
	return EXIT_SUCCESS;
}
