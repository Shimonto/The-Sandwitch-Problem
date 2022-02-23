
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


int b=0,c=0,s=0,p=1,sig=1;


sem_t m;


void *senior()
{

    if(b==0 && c==0 && s==0 && sig == 1)
    {
    	sem_wait(&m);

        printf("Progress %d : \n", p);
        p++;
        printf("b = ");
        scanf("%d",&b);
        printf("c = ");
        scanf("%d",&c);
        printf("s = ");
        scanf("%d",&s);

        printf("\n senior places ");
        if(b==1) printf("bread ");
        if(c==1) printf("cheese ");
        if(s==1) printf("sausage ");

        sig = 0;



        sem_post(&m);

    }

}


void *junior1()
{
    //bread
    sem_wait(&m);
    if(b==0 && sig==0)
    {
        b=1;
        printf(" junior1 has bread and gets the other ingredients !! \n");
        sig = 1;
    }
    sem_post(&m);
}

void *junior2()
{
//cheese
    sem_wait(&m);
    if(c==0 && sig==0 )
    {
        c=1;
        printf(" junior2 has cheese and gets the other ingredients !! \n");
       sig = 1;

    }
    sem_post(&m);

}

void *junior3()
{
// sausage
    sem_wait(&m);
    if(s==0 && sig==0)
    {
        s=1;
        printf(" junior3 has sausage and gets the other ingredients !! \n");
        sig = 1;

    }
    sem_post(&m);

}

int main()
{
    int i;
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    pthread_t t4;

    if (sem_init(&m, 0, 1) == -1)
    {
        perror("Could not initialize mylock semaphore");
        exit(1);
    }

    // Let us create three threads
    for(i=0; i<3; i++)
    {
        pthread_create(&t1, NULL, senior, NULL);
        pthread_create(&t2, NULL, junior1, NULL);
        pthread_create(&t3, NULL, junior2, NULL);
        pthread_create(&t4, NULL, junior3, NULL);
        b=0;
        c=0;
        s=0;
    }

    pthread_exit(NULL);
    return 0;
}
