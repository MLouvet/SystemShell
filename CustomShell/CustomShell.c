#include "CustomShell.h"

void printCurrContext()
{
	char hostName[BUFSIZ];
	gethostname(hostName, BUFSIZ - 1);
	hostName[BUFSIZ - 1] = '\0';
	//Affichage de l'utilisateur et du dossier
	fprintf(stdout, "%s@%s:%s$ ", getlogin(), hostName, get_current_dir_name());
}

void cd(command * cmd)
{
	char* wD = NULL;

	if (cmd->argc == 1 || (cmd->argc >= 2 && strcmp(cmd->args[1], "~") == 0))
	{
		if (chdir(getenv("HOME")) == -1)
			fprintf(stderr, "\nCD impossible : %s n existe pas\n", getenv("HOME"));
	}
	else if (chdir(cmd->args[1]) == -1)
		fprintf(stderr, "\nCD impossible : %s n existe pas\n", cmd->args[1]);

	//Modification de la variable d'environnement
	wD = getcwd(NULL, 0);
	setenv("PWD", wD, 1);
	free(wD);
}

void exitShell(command * cmd)
{
	if (cmd->argc == 1)
		exit(0);
	else
		exit(atoi(cmd->args[1]));
}

bool selectEarlyFunction(command * cmd)
{
	bool b = false;
	if (cmd->argc >= 1 && (strcmp(cmd->args[0], "exit") == 0 || strcmp(cmd->args[0], "quit") == 0)) { exitShell(cmd); b = true; }
	if (cmd->argc >= 1 && (strcmp(cmd->args[0], "cd") == 0)) { cd(cmd); b = true; }
	if (cmd->argc >= 1 && (strcmp(cmd->args[0], "history") == 0 || cmd->args[0][0] == '!')) { handleHistory(&globalHistory, cmd); b = true; }	//History [n] ou !n
	return b;
}

void selectFunction(bool commandAlreadyDone, char path[], command * cmd)
{
	bool b = false;
	if (cmd->argc >= 2 && strcmp(cmd->args[0], "touch") == 0) { touch(cmd); b = true; }
	if (cmd->argc >= 3 && strcmp(cmd->args[0], "cp") == 0) { cp(cmd); b = true; }
	if (cmd->argc >= 1 && strcmp(cmd->args[0], "cat") == 0) { cat(cmd->args, cmd->argc); b = true; }

	if (!b)
		if (execv(path, cmd->args) == -1 && commandAlreadyDone == false)
			fprintf(stderr, "Commande inconnue ou syntaxe incorrecte.\n");
}
