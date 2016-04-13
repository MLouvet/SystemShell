#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonctions.h"

#define BUFFER_SIZE 100

char** creerTableauBi(char* chaine)
{
    if(chaine == NULL)
    {
        printf("\nPas de chaine");
        //return exit(EXIT_FAILURE);
    }



   int i=0 , j=0 , k=0 , l=0 ;
   char buff[BUFFER_SIZE] = "\0"; //buffer pour la chaine

   i = nbOccurence(chaine, ' ') + 2; // on conçoit que le nb d espace peut indiquer nb+2 mots dans la chaine

   char** tab = malloc(i * sizeof(char*));

   if(tab == NULL)
        printf("\nERROR DANS MALLOC TAB PRINCIPAL\n");



    for(j=0; j < i-1; j++) // on lit toute la chaine
    {
        while(chaine[k] != ' ' && chaine[k] !=  '\0') // Tant qu on ne rencontre pas d espace , on met les caractères dans le buffer
        {
            buff[l] = chaine[k];
            k++;
            l++;
        }

        k++;
        buff[l] = '\0';
        l =0 ;
        tab[j] = alloueTabChar(buff,strlen(buff));
        buff[0] = '\0';
        //memset(buff,0,strlen(buff));
    }

    //on creer le dernier pointeur vers null
    tab[j] = NULL;

    return tab;

}


char* alloueTabChar(char* chaine, int taille)
{
    char* newTab = malloc(taille * sizeof(char));

    if(newTab == NULL)
        printf("\n ERREUR MALLOC CHAR*\n");

    strcpy(newTab,chaine);
    return newTab;
}


int nbOccurence(char* chaine,char leChar)
{
    int i =0, compte =0;

    for(i=0; i < strlen(chaine); i++)
    {
        if(chaine[i] == leChar)
            compte++;
    }

    return compte;

}

void afficheTab(char** tab,int taille)
{
    int i =0;

        for(i=0; i < taille ; i++)
    {
        printf("arg %d : %s\n",i, tab[i]);
    }

}
