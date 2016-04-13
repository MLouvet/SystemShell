#pragma once



//File simplement cha�n�e simple pour l'historique
typedef struct hist_entry hist_entry;
struct hist_entry
{
	char* entry;
	hist_entry* next;
};

//T�te de file pour l'historique, avec un pointeur sur la fin pour ajouter rapidement.
typedef struct history history;
struct history
{
	hist_entry* first;
	hist_entry* last;
	int size;
};

//Cr�� et retourne un nouvel historique vide.
history newHistory();

//Ajoute une entr�e � l'historique
//Entr�es :
//	- h		: Historique � modifier
//	- str	: cha�ne � ajouter � l'historique
void addEntry(history* h, const char str[]);

//Affiche l'historique dans l'ordre chronologique
//Entr�e :
//	- h : Historique � afficher
void printHistory(const history h);

//Vide dans son int�gralit� l'historique.
//Entr�e :
//	- h : Historique � vider.
void clearHistory(history h);