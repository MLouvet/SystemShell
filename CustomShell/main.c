#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <dirent.h>
#include "preliminaire.h"
#include "fonctions.h"
#include "commandShell.h"

#define BUFFER_SIZE 100

int main()
{
    lancerShell();



    return EXIT_SUCCESS;
}
