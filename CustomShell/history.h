#ifndef HISTORY_H
#define HISTORY_H

#include "CustomShell.h"
#include "commandHandler.h"
#include <stdlib.h>
#include <string.h>

//File simplement chaînée simple pour l'historique
typedef struct hist_entry hist_entry;
struct hist_entry
{
	char* entry;
	hist_entry* next;
};

//Tête de file pour l'historique, avec un pointeur sur la fin pour ajouter rapidement.
typedef struct history history;
struct history
{
	hist_entry* first;
	hist_entry* last;
	unsigned int size;
};

//Créé et retourne un nouvel historique vide.
history newHistory();

//Ajoute une entrée à l'historique
//Entrées :
//	- h		: Historique à modifier
//	- str	: chaîne à ajouter à l'historique
void addEntry(history* h, const char str[]);

//Affiche les n dernières entrées de l'historique
//Entrée :
//	- h : Historique à afficher
//	- n : Nombre d'entrées à afficher
void historyLastN(const history h, unsigned int n);

//Affiche la n-ième entrée de l'historique puis l'exécute
//Entrée :
//	- h : Historique à afficher
//	- n : Entrée à afficher
void repeatHistoryEntry(history* h, unsigned int n);


//Affiche l'historique dans l'ordre chronologique
//Entrée :
//	- h : Historique à afficher
void printHistory(const history h);

//Vide dans son intégralité l'historique.
//Entrée :
//	- h : Historique à vider.
void clearHistory(history h);

//Fonction chargée de gérer l'historique
void handleHistory(history* h, command * cmd);

int getLength(int i);


//Historique global
extern history globalHistory;
#endif