#ifndef SIMPLEIO_H
#define SIMPLEIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>

#define MAX_BUF_SIZE 512

/* Les commentaires de description ne sont pas dans l'en-tete mais dans le .c */
char* lireChaine();
int lireEntier();
int lireEntierEntre(int min, int max);
char* ReadFile(FILE *file);
bool isNullOrWhiteSpace(const char str[]);

//Porototype non-défini d'une fonction POSIX
char *strdup(const char *s);
FILE *popen(const char *command, const char *type);
int pclose(FILE *stream);
int asprintf(char **strp, const char *fmt, ...);
#endif // !SIMPLEIO_H

