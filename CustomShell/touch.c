#include "touch.h"

/*  Modifie les dates d'access et de modification d'un fichier

	-Entree : tableau d'arguments , notamment s'il y a le parametre -d ou non , le nb d'arguments
*/
void touch(command * cmd)
{
	struct stat sb;
	struct utimbuf temps;
	FILE* f = NULL;

	if (cmd->argc >= 3 && strcmp(cmd->args[1], "-d") == 0) touchDisp(cmd);

	//Mise à jour de la date du fichier
	if ((f = fopen(cmd->args[1], "a")) == NULL)
	{
		fprintf(stderr, "\nImpossible d'ouvrir ou de creer le fichier %s.", cmd->args[1]);
		return;
	}

	if (stat(cmd->args[1], &sb) == -1)
	{
		fprintf(stderr, "\nImpossible d'acceder aux informations du fichier %s.", cmd->args[1]);
		return;
	}

	temps.modtime = time(0);
	temps.actime = time(0);
	if (utime(cmd->args[1], &temps) == -1)
		fprintf(stderr, "\nErreur de mise à jour du fichier %s.", cmd->args[1]);

	if (fclose(f) == EOF)
		fprintf(stderr, "\nImpossible de fermeture du fichier %s.", cmd->args[1]);
}

void touchDisp(command * cmd)
{
	struct stat sb;
	FILE * f = NULL;

	if ((f = fopen(cmd->args[2], "a")) == NULL)
	{
		fprintf(stderr, "\nImpossible d'ouvrir ou de creer le fichier %s.", cmd->args[2]);
		return;
	}

	if (stat(cmd->args[1], &sb) == -1)
	{
		fprintf(stderr, "\nImpossible d'acceder aux informations du fichier %s.", cmd->args[2]);
		return;
	}

	printf("Dernier acces au fichier         : %s", ctime(&sb.st_atime));
	printf("Derniere modification du fichier : %s", ctime(&sb.st_mtime));

	if (fclose(f) == EOF)
		fprintf(stderr, "\nImpossible de fermeture du fichier %s.", cmd->args[2]);
}




//void touch(command * cmd)
//{
//	int fd = -1;				// id du fichiier a ouvrir
//	struct stat statFichier;	//pour lire et obtenir les droits du fichier
//	char* nomFichier;			// facilite l'utilisation du nom de fichier
//	struct timeval date[2];		//  type de time.h utilise pour modifier des valeurs de temps, comme la date d'acces et de modification
//	struct tm tmDate;			// struct de date
//	time_t nDate;				// struct temps en secondes
//
//	/*  S'il y a un argument a touch ou non, il faut selectionner le bon emplacement du nom de fichier*/
//	if (cmd->argc > 2)
//		nomFichier = cmd->args[cmd->argc - 1];
//
//	else
//		nomFichier = cmd->args[1];
//
//	if ((fd = open(nomFichier, O_RDONLY | O_WRONLY)) == -1)  //  ouverture du fichier
//	{
//		if ((fd = creat(nomFichier, O_CREAT | O_WRONLY | S_IRUSR | S_IWUSR)) == -1)    //  creation du fichier
//		{
//			printf("\nErreur ouverture fichier %s \n", nomFichier);
//			exit(EXIT_FAILURE);
//		}
//	}
//
//	else
//	{
//		if (stat(nomFichier, &statFichier) < 0)   //  acces droits
//		{
//			printf("\nErreur acces droits fichier %s\n", nomFichier);
//			exit(EXIT_FAILURE);
//		}
//		else            // S'il y a l'argument -d , on modifie la date avec celle entree par l'utilisateur
//			if (cmd->argc > 3)
//			{
//				char* newDate = parseToDate(cmd->args);
//				strptime(newDate, "%Y-%m-%d %H:%M:%S", &tmDate); //  convertit le string en tm
//				nDate = mktime(&tmDate);    //  convertit tm en time_t
//				date[0].tv_sec = nDate;     // on ajoute le time_t pour les date d'acces et de modification
//				date[1].tv_sec = nDate;
//				date[0].tv_usec = 0;        // les millisecondes ne sont pas representees par time_t , on met par defaut 0...
//				date[1].tv_usec = 0;
//				utimes(nomFichier, date);    //modifie les dates d'acces et de modification
//			}
//			else
//				futimens(fd, NULL);  // Sinon, modifie les dates par la date et l'heure actuelle données par defaut grace a NULL
//
//		close(fd);  // ferme le fichier
//	}
//}

///*  Recupere l'argument de date en string pour en former un nouveau plus facile a utiliser avec strptime()
//	-Entree : tableau d'arguments
//	-Sortie : chaine de caracteres
//
//	RQ : L format de date a ecrire par l'utilisateur est "  'YYYY-MM-DD/HH:MM:SS' "
//*/
//char* parseToDate(char * args[])
//{
//	char* oldDate = args[2];        // recupere la date en string
//	char* fullDate = NULL;      // futur string qui contiendra la date correcte
//	int i = 1, oldLen = strlen(oldDate);
//
//	fullDate = malloc((oldLen - 1)*sizeof(char));
//	if (fullDate == NULL) { printf("\nErreur malloc fulldate"); }
//
//	for (i = 1; i < oldLen - 1; i++)
//		fullDate[i - 1] = oldDate[i];
//
//	fullDate[i] = '\0';
//	fullDate[10] = ' ';       // on remplace le '\' par un espace , il se situe en 11eme place dans le string
//	return fullDate;
//}

