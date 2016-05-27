#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include "commandHandler.h"

char *makePath(char *dir, char *file);
int fileCopy(int ori, int copy, struct stat statOri);
int copyFolderToFolder(char *source, char *dest, struct stat statOri);
int copyFileToFile(char *ori, char *cpy, struct stat statOri);
int copyFileToFolder(char *sourcePath, char *copyPath, struct stat sourceStat);
bool cp(command * cmd);