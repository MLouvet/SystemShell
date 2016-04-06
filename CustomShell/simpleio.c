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
	fgets(buffer, MAX_BUF_SIZE, stdin);

	/* On remplace l'eventuel 'Entree' par '\0' */
	i = strlen(buffer) - 1;
	if (buffer[i] == '\n') buffer[i] = '\0';
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