#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t occupied;
sem_t free;
pthread_mutex_t time_lock;

int *arrive_times, *washing_times, *patiences;
int global_time;

void* clock(void *arg)
{
    while (1)
    {
        sleep(1);
        pthread_mutex_lock(&time_lock);
        global_time++;
        pthread_mutex_unlock(&time_lock);
    }
}

void* student(int *arg)
{
    int index = *arg;
    
    sleep(arrive_times[index]);

    sem_wait(&free);
    sem_post(&occupied);
    sleep(washing_times[index]);
    sem_post(&free);
    sem_wait(&occupied);
}