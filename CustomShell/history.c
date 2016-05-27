#include "history.h"

history globalHistory;

history newHistory()
{
	history h;
	h.first = NULL;
	h.last = NULL;
	h.size = 0;
	return h;
}


void addEntry(history* h, const char str[])
{
	if (h == NULL || str == NULL) return;

	hist_entry* elem = NULL;

	elem = malloc(sizeof(hist_entry));	//Allocation de l'élément
	elem->entry = NULL;
	elem->next = NULL;


	if (elem == NULL) return;			//Sur échec, rien ne se passe
	elem->entry = strdup(str);			//Copie de la chaîne
	if (elem->entry == NULL)
	{
		free(elem);
		return;
	}

	//Tout fonctionne, on ajoute le nouvel élément à l'historique.
	if (h->last != NULL) h->last->next = elem;
	else h->first = elem;
	h->last = elem;
	h->size++;

}

void historyLastN(const history h, unsigned int n)
{
	hist_entry* elem = h.first;
	int size = getLength(h.size);
	for (unsigned int i = 0; elem != NULL && i < h.size; i++)
	{
		if (h.size - n <= i) fprintf(stdout, "%*d %s\n", size, i - n + 1, elem->entry);
		elem = elem->next;
	}
}

void repeatHistoryEntry(history* h, unsigned int n)
{
	hist_entry* elem = h->first;
	unsigned int i;
	if (h == NULL) return;

	//Afficher l'entrée
	for (i = 0; elem != NULL && i < h->size; i++)
	{
		if (i == n) { fprintf(stdout, "%s\n", elem->entry); break; }
		else elem = elem->next;
	}

	if (i >= h->size)
	{
		fprintf(stderr, "\nEntree introuvable");
		return;
	}

	//Insérer l'entrée dans l'historique
	addEntry(h, elem->entry);

	//Exécuter l'entrée
	input_t * input = inputInit(elem->entry);
	inputExec(input);
	free(input);
}

void printHistory(const history h)
{
	hist_entry* elem = h.first;
	int size = getLength(h.size);

	for (int i = 0; elem != NULL && i < h.size; i++)
	{
		fprintf(stderr, "%*d %s\n", size, i, elem->entry);
		elem = elem->next;
	}
}

void clearHistory(history h)
{
	hist_entry* elem = h.first;
	hist_entry* temp;
	while (elem != NULL)
	{
		temp = elem->next;
		free(elem);
		elem = temp;
	}
}

void handleHistory(history* h, command * cmd)
{
	//Trois cas valides :
	//1 : !n
	//2 : history
	//3 : history nb

	int n = 0;
	int i = 0;
	char* temp = NULL;

	if (strcmp(cmd->args[0], "history") == 0)
	{
		if (cmd->argc == 1)	printHistory(*h);
		else
		{
			n = atoi(cmd->args[1]);
			if (n >= 0 && strcmp(cmd->args[1], "0") != 0) historyLastN(*h, n);
			else fprintf(stderr, " : argument numerique strictement positif necessaire.\n");
		}
	}
	else
	{
		//Copie de la chaîne de caractères après '!'
		temp = malloc(sizeof(char) * strlen(cmd->args[0]));
		if (temp == NULL) return;

		while (cmd->args[0][i + 1] != '\0') { temp[i] = cmd->args[0][i + 1]; i++; }
		temp[i] = '0';

		if (n >= 0) repeatHistoryEntry(h, n);
		else fprintf(stderr, " : entree non trouvee.\n");
	}
}

int getLength(int i)
{
	int size;
	char* temp = NULL;

	asprintf(&temp, "%d", i);
	size = strlen(temp);
	free(temp);

	return size;
}