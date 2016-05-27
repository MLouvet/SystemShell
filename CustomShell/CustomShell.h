#ifndef CUSTOM_SHELL_H
#define CUSTOM_SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#include "commandHandler.h"
#include "history.h"
#include "simpleio.h"
#include "touch.h"
#include "cp.h"
#include "cat.h"

/* Charg� de g�rer le fonctionnement basique du Shell :
* 1 : Affichage du conxtexte actuel : user@machine:repertoire_courant$
* 2 : Lecture de l'entr�e -> Transformation en succession de commande dans commandHandler
* 3 : Ajout de l'entr�e � l'historique
* 4 : Puis ex�cution des commandes ->
*
*/


//Le but de cette fonction est d'afficher user@machine:repertoire/courant
void printCurrContext();
//Reproduit le comportement de la fonction CD
void cd(command * cmd);

void exitShell(command * cmd);


char *get_current_dir_name(void);
int gethostname(char *name, size_t len);

bool selectEarlyFunction(command * cmd);
void selectFunction(bool commandAlreadyDone, char path[], command * cmd);



#endif // CUSTOM_SHELL_H