#include "commandHandler.h"

input_t* globalInput = NULL;

/* Charg� de g�rer les entr�es du Shell :
 *
 * 1 : S�parer chaque commande (pour les pipes)
 * 2 : D�terminer le flux de sortie
 * 3a: Si derni�re commande, mettre son r�sultat dans le flux de sortie OU
 * 3b: Sinon, ins�rer le r�sultat de la commande � la seconde position des
 *     arguments de la commande suivante.
 *
 */

 //S�pare une cha�ne d'arguments entr�e en un tableau d'arguments.
 //Entr�es :
 //	- string : Cha�ne d'arguments initiale.
 //	- splitStr : tableaux de cha�nes d'arguments. Sera �cras�
 //Retourne le nombre d'arguments dans le tableau.
unsigned int splitArgs(const char string[], char *** splitStr, char separator)
{
	int i = 0, j, nbArgs = 0;
	char buf[BUFSIZ];

	if (string == NULL) return nbArgs;

	//On lit toute la cha�ne, on r�cup�re chaque argument
	while (string[i] != '\0')
	{
		if (string[i] != separator)
		{
			//on a trouv� un argument, on le copie dans le buffer
			//en le transformant en cha�ne � part enti�re
			j = 0;
			while (string[i + j] != '\0' && string[i + j] != separator)
			{
				buf[j] = string[i + j];
				j++;
			}
			buf[j] = '\0';
			i += j;

			//Le mot est copi�, on alloue le tableau
			(*splitStr) = realloc(*splitStr, (nbArgs + 1) * sizeof(char**));

			(*splitStr)[nbArgs] = strdup(buf);

			nbArgs++;
		}
		else i++;
	}

	(*splitStr) = realloc(*splitStr, (nbArgs + 1) * sizeof(char**));
	(*splitStr)[nbArgs] = NULL;

	return nbArgs;
}

input_t* inputInit(const char str[])
{
	int i, argc = 0;
	char* temp = NULL;
	char** args = NULL;
	input_t *input = NULL;
	if ((input = malloc(sizeof(input_t))) == NULL)
	{
		fprintf(stderr, "\nErreur d'allocation pour la structure d'entree.");
		return input;
	}

	input->firstCmd = NULL;
	input->last = NULL;
	input->outStream = stdout;				//Sortie par d�faut
	input->text = strdup(str);				//Copie de la cha�ne entr�e
	input->pid = 0;

	//D�termination du flux de sortie
	argc = splitArgs(str, &args, '>');
	if (argc == 2 && (input->outStream = fopen(args[1], "w")) == NULL)
	{
		fprintf(stderr, "\nShell : erreur de syntaxe pr�s du symbole inattendu '\n'.");
		input->outStream = stdout;			//Flux de sortie invalide
	}
	temp = strdup(args[0]);
	free(args);
	args = NULL;

	if (input->text == NULL || argc == 0 || input->outStream == NULL)			//Flux de sortie invalide
	{
		free(input->text);
		return NULL;
	}

	//On compte le nombre de commandes
	argc = splitArgs(temp, &args, '|');		//D�coupage de la cha�ne d'entr�e

	//Construction des commandes
	for (i = 0; i < argc; i++)
	{
		if (input->firstCmd == NULL)
		{
			input->firstCmd = commandInit(args[i]);
			input->last = input->firstCmd;
		}
		else
		{
			input->last->next = commandInit(args[i]);
			input->last = input->last->next;
		}
	}
	free(temp);
	free(args);

	return input;
}

void inputFree(input_t* input)
{
	if (input == NULL) return;

	//On ferme l'�ventuel fichier dans lequel la sortie a �t� �crite
	if (input->outStream != stdout && fclose(input->outStream) == EOF)
		fprintf(stderr, "\n%s", "Echec de fermeture du fichier de sortie");
	//free(input->text);
	//puts("Text freed");
	commandFreeAll(input->firstCmd);
	//free(input);
}


void inputExec(input_t * input)
{
	int pfd[2];
	pid_t pid;
	char* path = NULL;
	int fd_in = 0;
	bool commandAlreadyDone;
	command *cmd = input->firstCmd;

	commandAlreadyDone = selectEarlyFunction(cmd);

	while (cmd != NULL)
	{
		path = getPath(cmd->args[0]);
		if (pipe(pfd) == -1) { printf("\nEchec de creation du tuyau."); return; }
		if ((pid = fork()) < 0) { printf("\nEchec de creation d'un autre processus."); return; }
		else
		{
			if (pid != 0)					//Parent
			{
				wait(NULL);					// Le pere attend la fin de l'execution de la ligne de commande rentree du fils
				close(pfd[1]);				//On ferme le c�t� �criture
				fd_in = pfd[0];				//On m�morise le c�t� lecture
				cmd = cmd->next;			//Passage � la commande suivante
			}
			else																	//Enfant
			{
				dup2(fd_in, STDIN_FILENO);											//On connecte l'entr�e � stdin
				if (cmd->next != NULL)												//S'il y a d'autres commandes
					dup2(pfd[1], STDOUT_FILENO);										//On lie le c�t� �criture � stdout
				else																//Si c'est la derni�re commande
					dup2(fileno(input->outStream), STDOUT_FILENO);						//On remplace stdout par la sortie voulue
				close(pfd[0]);														//Fermeture du c�t� �criture
				//execv(path, cmd->args);												//Ex�cution du processus
				selectFunction(commandAlreadyDone, path, cmd);
				exit(EXIT_FAILURE);
			}
		}
		free(path);
		path = NULL;
	}
}

command *commandInit(const char * argStr)
{
	if (argStr == NULL) return NULL;

	command * cmd = NULL;

	cmd = malloc(sizeof(command));
	if (cmd == NULL)
	{
		fprintf(stderr, "\nEchec d'allocation memoire pour la structure d'une commande");
		return NULL;
	}

	cmd->argc = 0;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->text = NULL;
	cmd->running = false;
	cmd->pid = 0;

	cmd->argc = splitArgs(argStr, &cmd->args, ' ');
	if (cmd->argc == 0 || cmd->args == NULL)
	{
		fprintf(stderr, "\nEchec de decoupage pour la creation d'une cmde.");
		free(cmd);
	}

	cmd->args = realloc(cmd->args, (cmd->argc + 1) * sizeof(char*));

	if (cmd->args == NULL)
	{
		fprintf(stderr, "\nEchec d'allocation memoire pour les arguments d'une commande");
		free(cmd);
		return NULL;
	}
	cmd->args[cmd->argc] = NULL;			//Liste d'arguments termin�e par "NULL"
	cmd->text = strdup(argStr);
	return cmd;
}

void commandFree(command* cmd)
{
	if (cmd == NULL) return;
	if (cmd->text != NULL) { free(cmd->text); cmd->text = NULL; }
	for (int i = 0; i <= cmd->argc; i++) { free(cmd->args[i]); }
	free(cmd->args);
	free(cmd);
}

void commandFreeAll(command* cmd)
{
	if (cmd == NULL) return;
	commandFreeAll(cmd->next);
	commandFree(cmd);
}

char* getPath(const char relativePath[])
{
	FILE* f = NULL;
	char** paths = NULL;
	char *cmdPath = NULL;
	int nbPaths = 0, i;
	nbPaths = splitArgs(getenv("PATH"), &paths, ':');
	for (i = 0; i < nbPaths; i++)
	{
		//path + "/" + relativePath
		asprintf(&cmdPath, "%s/%s", paths[i], relativePath);
		if ((f = fopen(cmdPath, "r")) != NULL)
		{
			fclose(f);
			for (i = 0; i < nbPaths; i++)
				free(paths[i]);
			free(paths);
			return cmdPath;
		}
		else
			free(cmdPath);
	}
	for (i = 0; i < nbPaths; i++)
		free(paths[i]);
	free(paths);
	return NULL;
}
