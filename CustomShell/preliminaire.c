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


void lancerShell(){

char ligne[BUFFER_SIZE];
char nomDir[300];
int test=0;


printf("\n%s > ", getcwd(nomDir,300)); // Affiche le chemin absolu du repertoire courant

while(fgets(ligne,BUFFER_SIZE,stdin) != NULL) // tant qu'on a une ligne de commande et pas de ctrl + d ( qui retourne 0 )
    {

        char* positionEntree = NULL;
        positionEntree = strchr(ligne,'\n'); // on cherche le retourne a la ligne

        // s il y a un retourne a la ligne ( uniquement en fin de chaine) , on le supprime
        if(positionEntree != NULL)
            *positionEntree = '\0';

        pid_t pid;
        pid = fork();

        if (pid < 0) //  erreur lors du fork
        {
            printf("\n Erreur fork");
            exit(EXIT_FAILURE);
        }

        if(pid == 0) // on cherche à executer le programme de la ligne de cmd dans le processus fils
        {
            printf("\n%s",strstr(ligne,"cd"));
            if(strstr(ligne,"cd") != NULL)
                cd(ligne);


            else
                lanceProg(ligne);


           // waitpid(-1,NULL,0); // Le pere attend la fin de l'execution de la ligne de commande rentree du fils
            //printf("\n%s > ", getcwd(nomDir,300));
        }
        else
                waitpid(-1,NULL,0); // Le pere attend la fin de l'execution de la ligne de commande rentree du fils


        printf("\n%s > ", getcwd(nomDir,300));
        }
}


void lanceProg(char* nomProg)
{
        char* cheminCMD = NULL;
        int i =0;

        if(strchr(nomProg,' ') == NULL)
        {
                char* cheminCMD = malloc((strlen(nomProg) + 1) * sizeof(char)); // Allocation d'une chaine de caractere pour le chemin absolu

                // Creation du chemin absolu
                strcat(cheminCMD,"./");
                strcat(cheminCMD,nomProg);

                if(execlp(cheminCMD,nomProg, NULL) == -1) // Si l'execution du nom de programme est incorrecte
                        printf("\nErreur : %s n'existe pas\n",cheminCMD);

                free(cheminCMD);

        }

        else
        {
                char** arguments = creerTableauBi(nomProg);
                cheminCMD = malloc(strlen(arguments[0]+1)*sizeof(char));
                int taille = nbOccurence(nomProg,' ') +1;

                // Creation du chemin absolu
                strcat(cheminCMD,"./");
                strcat(cheminCMD,arguments[0]);
                arguments[0] = realloc(arguments[0], strlen(arguments[0] + 4) * sizeof(char));
                strcat(arguments[0],".exe");
                //afficheTab(arguments, taille);


                if(execvp(cheminCMD,arguments) == -1) // Si l'execution du nom de programme est incorrecte
                {
                        printf("\nErreur : %s n'existe pas\n",cheminCMD);

                }

                free(cheminCMD);
                for(i=0;i < taille-1;i++)
                        free(arguments[i]);

                free(arguments);
        }

}

