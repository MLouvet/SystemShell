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
/* Charg� de g�rer les entr�es du Shell
 * 1 : S�parer chaque commande (pour les pipes)
 * 2 : D�terminer le flux de sortie
 * 3a: Si derni�re commande, mettre son r�sultat dans le flux de sortie OU
 * 3b: Sinon, ins�rer le r�sultat de la commande � la seconde position des
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
	char* text;			//Cha�ne originale entr�e
	FILE* outStream;	//stdout ou fichier
	command* firstCmd;	//Premi�re commande dans la file d'attente
	command* last;
	pid_t pid;
};

//Le but principal de cette fonction est de d�couper la cha�ne d'arguments s�par�s par des espaces
unsigned int splitArgs(const char string[], char *** splitStr, char separator);

//Fonctions associ�es aux commandes
command *commandInit(const char * argStr);
void commandFree(command* cmd);
void commandFreeAll(command* cmd);
//char* commandGetOutput(command *cmd);
char* getPath(const char relativePath[]);
//bool lanceProg(command *cmd);

//Fonctions associ�es � l'entr�e dans son int�gralit�
input_t* inputInit(const char str[]);
void inputFree(input_t * input);
void inputExec(input_t * input);

//Variable globale
extern input_t* globalInput;

#include "CustomShell.h"
#endif // COMMAND_HANDLER_H
