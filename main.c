#include "main.h"
sem_t sem_p,sem_c;
int msg_id;
int main(int argc,char *argv[])
{
    int i;
    key_t key;
    pthread_t thread[2];
    void *(*thread_p[2])(void *) = {producer,consumer};
    int ret;

    sem_init(&sem_p,0,0);
    sem_init(&sem_c,0,0);

    key = ftok("/",0x01);
    msg_id = msgget(key,IPC_CREAT | 0666);
    if(msg_id == -1)
    {
        perror("msgget");
        exit(1);
    }
    for(i = 0;i < 2;i ++)
    {
        ret = pthread_create(&thread[i],NULL,thread_p[i],NULL);
        if(ret != 0)
        {
            perror("pthread_create");
            exit(0);
        }
    }
    pthread_join(thread[0],NULL);
    pthread_join(thread[1],NULL);
    msgctl(msg_id,IPC_RMID,NULL);
    sem_close(&sem_p);
    sem_close(&sem_c);
    return 0;
}