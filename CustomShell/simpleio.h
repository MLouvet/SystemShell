#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUF_SIZE 512

/* Les commentaires de description ne sont pas dans l'en-tete mais dans le .c */
char* lireChaine();
int lireEntier();
int lireEntierEntre(int min, int max);