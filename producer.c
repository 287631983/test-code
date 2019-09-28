#include "main.h"

void *producer(void *arg)
{
    while(1)
    {
        product_line.mtext = "Hello,world!"
        msgsnd(msg_id,product_line,strlen(product_line.mtext),0);
    }
}