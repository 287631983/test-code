#ifndef _MAIN_H
#define _MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
struct msgbuf
{
    long mtype;
    char mtext[200];
}product_line;
void *producer(void *arg);
void *consumer(void *arg);
#endif
