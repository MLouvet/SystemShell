#include "cp.h"

char *makePath(char *dir, char *file) // cree les chemins d'accès corrects
{
	char *res;
	if (dir[strlen(dir) - 1] != '/')
		asprintf(&res, "%s/%s", dir, file);
	else
		asprintf(&res, "%s%s", dir, file);
	return res;
}

int fileCopy(int ori, int copy, struct stat statOri)
{
	char buf[BUFSIZ];
	int n;

	fchmod(copy, statOri.st_mode);
	while ((n = read(ori, buf, BUFSIZ)) > 0)
		if (write(copy, buf, n) != n)
			return -1;
	return 1;
}

int copyFolderToFolder(char *source, char *dest, struct stat statOri)
{
	DIR* dp;
	struct dirent* d;
	command * cmd = NULL;
	char * str = NULL;

	dp = opendir(source);
	if (dp == NULL)
		return 0;

	while ((d = readdir(dp)) != NULL)
	{
		if ((d->d_ino != 0) && (!(strncmp(d->d_name, ".", 1) == 0 || strncmp(d->d_name, "..", 2) == 0)))
		{
			asprintf(&str, "cp %s %s", makePath(source, d->d_name), makePath(dest, d->d_name));
			cmd = commandInit(str);
			free(str);
			if (cp(cmd) == false)
			{
				commandFree(cmd);
				return 0;
			}
			else
				commandFree(cmd);
		}
	}
	closedir(dp);
	return 1;
}

int copyFileToFile(char *ori, char *cpy, struct stat statOri)
{
	int fdOri, fdCpy;
	int res;

	fdOri = open(ori, O_RDONLY);
	if (fdOri == -1)
	{
		fprintf(stderr, "\nOuverture impossible du fichier %s", ori);
		return 0;
	}

	fdCpy = open(cpy, O_WRONLY | O_CREAT | O_TRUNC, statOri.st_mode);
	if (fdCpy == -1)
	{
		fprintf(stderr, "\nOuverture impossible du fichier %s", cpy);
		close(fdOri);
		return 0;
	}

	res = fileCopy(fdOri, fdCpy, statOri);

	if (close(fdOri) == -1)
		return 0;
	if (close(fdCpy) == -1)
		return 0;
	if (res == -1)
		return 0;
	return 1;
}

int copyFileToFolder(char *sourcePath, char *copyPath, struct stat sourceStat)
{
	int res;
	char *nomFichier, *cheminCpy;
	nomFichier = strrchr(sourcePath, (int) '/');

	if (nomFichier != NULL)
		cheminCpy = makePath(copyPath, &(nomFichier[1]));
	else
		cheminCpy = makePath(copyPath, sourcePath);
	res = copyFileToFile(sourcePath, cheminCpy, sourceStat);
	free(cheminCpy);
	return res;
}

bool cp(command * cmd)
{
	if (cmd->argc < 3)
	{
		fprintf(stderr, "\nArguments insuffisants pour copier");
		return false;
	}

	struct stat sourceStat;
	struct stat copyStat;

	if (stat(cmd->args[1], &sourceStat) == -1)
	{
		fprintf(stderr, "\nAcces refuse a %s\n", cmd->args[1]);
		return false;
	}

	if (S_ISDIR(sourceStat.st_mode))
	{
		if (stat(cmd->args[2], &copyStat) == -1)
		{
			if (mkdir(cmd->args[2], sourceStat.st_mode) == -1)
			{
				fprintf(stderr, "Creation de dossier impossible %s\n", cmd->args[2]);
				return false;
			}
			copyFolderToFolder(cmd->args[1], cmd->args[2], sourceStat);
		}
		else if (S_ISDIR(copyStat.st_mode))	copyFolderToFolder(cmd->args[1], cmd->args[2], sourceStat);
		else fprintf(stderr, "Impossible de copier un dossier dans un fichier\n");
	}
	else
	{
		if ((stat(cmd->args[2], &copyStat) == -1) || S_ISREG(copyStat.st_mode))
			copyFileToFile(cmd->args[1], cmd->args[2], sourceStat);
		else
			copyFileToFolder(cmd->args[1], cmd->args[2], sourceStat);
	}

	return true;
}
