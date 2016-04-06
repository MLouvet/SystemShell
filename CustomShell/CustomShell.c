#include "CustomShell.h"
#include "simpleio.h"

int main(int argc, char* argv[])
{
	char* buf;
	char ** splitBuf = NULL;
	int nbArgs = 0;
	while (true)
	{
		/*if ((buf = lireChaine()) == NULL || strlen(buf) == 0)
			return 0;*/
			//nbArgs = splitArgs(buf, &splitBuf);
		nbArgs = splitArgs("a bb  ccc dddd  eeeee   ", &splitBuf);
		for (int i = 0; i < nbArgs; i++)
		{
			printf("\nArg(%d) = %s", i, splitBuf[i]);
		}
	} 
}

unsigned int splitArgs(const char string[], char *** splitStr)
{
	int i = 0, j, nbArgs = 0;
	char buf[512];

	if (string == NULL) return nbArgs;

	//On lit otute la chaîne, on récupère chaque argument
	while (string[i] != '\0')
	{
		if (string[i] != ARG_SEPARATOR)
		{
			//on a trouvé un argument, on le copie dans le buffer
			nbArgs++;
			j = 0;
			while (string[i + j] != '\0' && string[i + j] != ARG_SEPARATOR)
			{
				buf[j] = string[i + j];
				j++;
			}
			buf[j] = '\0';
			i += j;

			//Le mot est copié, on alloue le buffer
			(*splitStr) = realloc(*splitStr, nbArgs * sizeof(char**));
			(*splitStr)[nbArgs - 1] = malloc((j + 1) * sizeof(char));
			strcpy((*splitStr)[nbArgs - 1], buf);
			printf("\n#####%d : %s,", nbArgs - 1, (*splitStr)[nbArgs - 1]);
		}
		else i++;
	}



	return nbArgs;
}

void cd(int argc, char * argv[])
{
	char * currentDir = NULL;

#ifdef WIN32 //Windows
	currentDir = malloc(BUFSIZ * sizeof(char));
	GetCurrentDirectoryA(BUFSIZ, currentDir);
#else
	currentDir = get_current_dir_name();
#endif
}
