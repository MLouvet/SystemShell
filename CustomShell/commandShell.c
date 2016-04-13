#include <stdlib.h>
#include <stdio.h>
#include "preliminaire.h"
#include "fonctions.h"
#include "commandShell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>

#define BUFFER_SIZE 100


void cd(char* nomRepertoire)
{
    int i =0, taille = nbOccurence(nomRepertoire,' ')+1;
    char cwd[BUFFER_SIZE] = "\0";
    getcwd(cwd,sizeof(cwd)); // On recupere le nom du chemin absolu du repertoire courant

    char** arguments = creerTableauBi(nomRepertoire);


    if(chdir(arguments[1]) == -1)
        printf("\nCD impossible : %s n existe pas\n",nomRepertoire);

    else
    {
        printf("\nCD reussie , nouveau repertoire : %s\n",getcwd(cwd,sizeof(cwd)));
    }

    for(i=0;i < taille ;i++)
        free(arguments[i]);

    free(arguments);
}

void exitShell()
{

}
