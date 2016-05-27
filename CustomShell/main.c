#include "CustomShell.h"
#include "history.h"
#include "CustomShell.h"
#include "simpleio.h"

//Normalement, plus besoin de toucher à ce fichier

int main()
{
	char* buf;

	//Initialisation des variables globales


	while (true)
	{
		buf = NULL;
		globalInput = NULL;
		printCurrContext();					//Affichage du dossier actif
		if ((buf = lireChaine()) == NULL)	//Lecture de la ligne de commande
		{
			puts("");						//Ctrl-D ferme stdin, cela correspond
			return EXIT_SUCCESS;			//à la fin du programme
		}
		if (isNullOrWhiteSpace(buf))
		{
			free(buf); 
			continue;
		}
		addEntry(&globalHistory, buf);		//Ajout de l'entrée à l'historique
		globalInput = inputInit(buf);		//Gestion de l'entrée
		inputExec(globalInput);				//Exécution de la série de commandes

		inputFree(globalInput);
		free(buf);
	}
	exit(EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
