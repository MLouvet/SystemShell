#include "cat.h"

#define MAX_SIZE 1000

void cat(char* args[], int nbArgs)
{
	if (nbArgs >= 4 && !strcmp(args[2], "-")) { catfg(args, nbArgs); }
	else if (nbArgs >= 3 && !strcmp(args[1], "-n")) { cat_n(args, nbArgs); }
	else if (nbArgs >= 2) { catf(args, nbArgs); }
	else cat_main();
}

void cat_main()
{
	char* buf = NULL;
	while ((buf = lireChaine()) != NULL)
	{
		fprintf(stdout, "%s\n", buf);
		free(buf);
	}
}

void catf(char* args[], int nbArgs)
{
	char* nomFichier = args[1];
	char buffer[1000] = "";
	FILE* fd = fopen(nomFichier, "r");

	if (fd == NULL)
	{
		fprintf(stderr, "\nErreur ouverture fichier %s\n", nomFichier);
		exit(EXIT_FAILURE);
	}

	while (fgets(buffer, MAX_SIZE, fd))
		printf("%s", buffer);

	fclose(fd);
}


/* affiche en plus le numero de la ligne */
void cat_n(char* args[], int nbArgs)
{
	char* nomFichier = args[2];
	char buffer[1000] = "";
	FILE* fd = fopen(nomFichier, "r");

	if (!fd)
		fprintf(stderr, "\nErreur ouverture fichier %s\n", nomFichier);
	else
	{
		int i = 1;
		for (i = 1; fgets(buffer, MAX_BUF_SIZE, fd) != NULL; i++)
			fprintf(stdout, "\t%d %s", i, buffer);

		fclose(fd);
	}
}

/* affiche le premier fichier f , puis affiche ce qu'il y a d'entrée par l'utilisateur sur stdin, puis affiche le fichier g*/
void catfg(char* args[], int nbArgs)
{
	char* inputFile = args[1];
	char* outputFile = args[3];
	char* buffer = NULL;
	FILE* fdin = fopen(inputFile, "r");
	FILE* fdout = fopen(inputFile, "r");

	if (fdin == NULL || fdout == NULL)
	{
		fprintf(stderr, "\nErreur ouverture fichier %s ou %s", inputFile, outputFile);
		return;
	}

	buffer = ReadFile(fdin);
	fprintf(stdout, "%s\n", buffer);
	free(buffer);

	cat_main();

	buffer = ReadFile(fdout);
	fprintf(stdout, "%s\n", buffer);
	free(buffer);

	if (fclose(fdin) == EOF || fclose(fdout) == EOF)
		fprintf(stderr, "\nEchec de fermeture du fichier %s ou %s", inputFile, outputFile);
}
