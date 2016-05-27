#ifdef 0
#ifndef JOBS_H_INCLUDED
#define JOBS_H_INCLUDED

#include <termios.h>
#include <signal.h>
#include "CustomShell.h"
#include "stdbool.h"

/*
    Struct representant une liste de jobs (input_t)
*/
typedef struct t_job t_job;
struct t_job
{
    input_t* job;
    t_job* previous;
    t_job* next;
};

typedef struct jobList jobList;
struct jobList
{
    t_job* first;
    t_job* last;
};


t_job* findJob(pid_t job_pid, jobList* jList);

void ps(jobList* jlist);
void jobs(jobList* jList);

bool isForeground(int fileDescriptor, t_job* job_entry);
void fg(jobList* jList, t_job* job_entry);

void changeFirstOrder(jobList* jList, t_job* job_entry1, t_job* job_entry2);



#endif // JOBS_H_INCLUDED
#endif