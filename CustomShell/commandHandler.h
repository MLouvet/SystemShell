#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "simpleio.h"
/* Chargé de gérer les entrées du Shell
 * 1 : Séparer chaque commande (pour les pipes)
 * 2 : Déterminer le flux de sortie
 * 3a: Si dernière commande, mettre son résultat dans le flux de sortie OU
 * 3b: Sinon, insérer le résultat de la commande à la seconde position des
 *     arguments de la commande suivante.
 *
 */

typedef struct command command;
struct command
{
	int argc;
	char** args;
	char* text;
	command* next;
	bool running;
	pid_t pid;
};

typedef struct input_t input_t;
struct input_t 
{
	char* text;			//Chaîne originale entrée
	FILE* outStream;	//stdout ou fichier
	command* firstCmd;	//Première commande dans la file d'attente
	command* last;
	pid_t pid;
};

//Le but principal de cette fonction est de découper la chaîne d'arguments séparés par des espaces
unsigned int splitArgs(const char string[], char *** splitStr, char separator);

//Fonctions associées aux commandes
command *commandInit(const char * argStr);
void commandFree(command* cmd);
void commandFreeAll(command* cmd);
//char* commandGetOutput(command *cmd);
char* getPath(const char relativePath[]);
//bool lanceProg(command *cmd);

//Fonctions associées à l'entrée dans son intégralité
input_t* inputInit(const char str[]);
void inputFree(input_t * input);
void inputExec(input_t * input);

//Variable globale
extern input_t* globalInput;

#include "CustomShell.h"
#endif // COMMAND_HANDLER_H
