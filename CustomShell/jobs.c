#ifdef 0
#include "jobs.h"

/* Parcourt la liste de job pour trouver le job correspondant au pid donné */
t_job* findJob(pid_t job_pid, jobList* jList)
{
    if(jList == NULL)
    {
        fprintf(stderr,"\nErreur, aucun job en cours");
        return NULL;
    }

    else
    {
        t_job* i;
        for(i = jList->first->job; i->job != NULL ; i = i->next)
        {
            if(i->job->pid == job_pid)
                return i;
        }
        return NULL;
    }
}


/* affiche la liste des processus en cours dans le shell*/
void ps(jobList* jlist)
{
    t_job* i;
    command* j;

    /* Parcourt la liste de t_job pour lire chaque job (input_t) */
    for(i = jlist->first; i->job != NULL; i = i->next)
    {
        /* Lis les commandes dans chaque job */
        for(j = i->job->firstCmd; j->text != NULL; j = j->next)
        {
            fprintf(stdout,"\t%d\t%s\n",j->pid, j->text);
        }
    }
}

void jobs(jobList* jList)
{
    t_job* i;

    for(i = jList->first; i->job != NULL ; i = i->next)
    {
        fprintf(stdout, "\t%d\t%s",i->job->pid, i->job->text);
    }
}



bool isForeground(int fileDescriptor, t_job* job_entry)
{
    if( job_entry->job->pid !=tcgetpgrp(fileDescriptor))
        return true;
    else
        return false;
}

/* Met en foreground un job qui est en background d'apres la sortie */
void fg(jobList* jList, t_job* job_entry)
{
    if(isForeground(/*job_entry->job->outStream*/ stdout, job_entry))
    {
        fprintf(stdout,"\nNew job in Foreground : %s",job_entry->job->text);
        changeFirstOrder(jList,jList->first,job_entry);

        // Il faudrait une fonction pour lancer l'input_t deja initialisee
    }
}

/* Change l'ordre de deux jobs s'ils sont dans la meme liste */
void changeFirstOrder(jobList* jList, t_job* job_entry1, t_job* job_entry2)
{
    /* Si les jobs appartiennent bien a la bonne liste */
    if( (findJob(job_entry1->job->pid, jList) != NULL) && (findJob(job_entry2->job->pid, jList) != NULL) )
    {
        t_job* temp = malloc(sizeof(t_job));

        // Initialisation du tampon qui copie job2
        temp->job = job_entry2->job;
        temp->previous = job_entry2->previous;
        temp->next = job_entry2->next;

        // modification du job2 par job1
        job_entry2->previous = job_entry1->previous;
        job_entry2->next = job_entry1->next;

        // modification du job1 par temp
        job_entry1->previous = temp->previous;
        job_entry1->next = temp->next;

        free(temp);
    }

    else
        fprintf(stderr,"\nErreur, le(s) job(s) n'est (ne sont) pas dans la liste");
}
#endif