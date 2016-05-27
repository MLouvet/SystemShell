#ifndef TOUCH_H_INCLUDED
#define TOUCH_H_INCLUDED

#define _XOPEN_SOURCE /* Pour glibc2 */
#define __USE_XOPEN
#define _GNU_SOURCE

#include <string.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <utime.h>
#include <unistd.h>
#include "commandHandler.h"

void touch(command * cmd);
void touchDisp(command * cmd);
//char* parseToDate(char * args[]);

#endif // TOUCH_H_INCLUDED
