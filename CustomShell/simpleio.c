#include "simpleio.h"

/* Renvoie une chaine lue au clavier, de taille maximale MAX_BUF_SIZE */
char* lireChaine()
{
	char * buffer = NULL;
	unsigned int i;

	/* Allocation */
	buffer = (char *)malloc(sizeof(char) * MAX_BUF_SIZE);
	if (buffer == NULL) return buffer;

	/* Recuperation de la chaine */
	if (fgets(buffer, MAX_BUF_SIZE, stdin) == NULL) return NULL;

	/* On remplace l'eventuel 'Entree' par '\0' */
	i = strlen(buffer) - 1;
	if (i >= 0 && buffer[i] == '\n') buffer[i] = '\0';
	return buffer;
}

/* Retourne un entier lu au clavier avec verification de la validite du format */
int lireEntier()
{
	int entierLu;
	int nbEntiersLus;

	do
	{
		nbEntiersLus = scanf("%d", &entierLu);
		if (nbEntiersLus != 1) puts("Erreur de format: veuillez saisir un unique entier.");

		/* vidage du reste du tampon (si plusieurs entiers ou saisie invalide) */
		while (getchar() != '\n');
	} while (nbEntiersLus != 1);
	return entierLu;
}

/* Retourne un entier compris entre deux bornes (inclues). */
int lireEntierEntre(int min, int max)
{
	int result;

	/* Eventuelle inversion des bornes */
	if (max < min)
	{
		min += max;
		max = min - max;
		min -= max;
	}

	/* Lecture tant qu'en dehors des bornes */
	do
	{
		result = lireEntier();
		if (result < min || result > max) printf("Erreur de bornes : la valeur saisie doit être comprise entre %d et %d\n", min, max);
	} while (result < min || result > max);
	return result;
}


char* ReadFile(FILE *file)
{
	char *buffer = NULL;
	struct stat st;

	if (file == NULL) return NULL;

	fstat(fileno(file), &st);													//Statistiques du fichier
	buffer = malloc(sizeof(char) * (st.st_size + 1));					//On alloue une chaîne de la taille du fichier
	if (buffer == NULL)
	{
		fprintf(stderr, "\nEchec d'allocation pour la lecture d'un fichier");
		return NULL;
	}
	if (fread(buffer, st.st_size, st.st_size, file) > st.st_size)	//On lit l'intégralité du fichier
	{
		free(buffer);													//Erreur dans la lecture, on
		buffer = NULL;													//libère la mémoire utilisée
		fprintf(stderr, "\nErreur de lecture du fichier");
		return NULL;
	}

	buffer[st.st_size] = '\0';											//On formate la chaîne correctement
	return buffer;
}

bool isNullOrWhiteSpace(const char str[])
{
	if (str == NULL) return true;

	int size = strlen(str);
	for (int i = 0; i < size; i++)
		if (str[i] != ' ')
			return false;

	return true;
}
