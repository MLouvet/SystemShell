#include "history.h"
#include <stdlib.h>
#include <string.h>

history newHistory()
{
	history h;
	h.first = NULL;
	h.last = NULL;
	h.size = 0;
}


void addEntry(history* h, const char str[])
{
	int strLength = 0;
	hist_entry* elem = NULL;

	//Allocation de l'élément
	//Sur échec, rien ne se passe
	elem = malloc(sizeof(hist_entry));
	if (elem == NULL) return;

	//Copie de la chaîne
	strLength = strlen(str);
	elem->entry = malloc((strLength + 1) * sizeof(char));
	if (elem->entry == NULL)
	{
		free(elem);
		return;
	}

	//Tout fonctionne, on ajoute le nouvel élément.
	strcpy(elem->entry, str);
	elem->entry[strLength] = '\0';
	elem->next = NULL;

	h->last->next = elem;
	h->last = elem;

}

void printHistory(const history h)
{
	hist_entry* elem = h.first;
	while (elem != NULL)
	{
		printf("\n%*d %s", h.size, elem->entry);
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

	}
}
