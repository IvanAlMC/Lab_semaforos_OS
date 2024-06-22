#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t sem1, sem2;

int num = 10;

void *incrementa(void *nada) {
   int i;
   for (i = 0; i < 3; i++) {
      sem_wait(&sem1);
      num++;
      printf("Inc. Número = %d\n", num);
      sem_post(&sem2);
   }
   sleep(random() % 3);
   pthread_exit(NULL);
}

void *decrementa(void *nada) {
   int i;
   for (i = 0; i < 3; i++) {
    
      sem_wait(&sem2);
      num--;
      printf("Dec. Número = %d\n", num);
      sem_post(&sem1);
   }
    sleep(random() % 3);
   pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
   pthread_t th1, th2, th3;
   srandom(time(NULL));
   sem_init(&sem1, 0, 1);
   sem_init(&sem2, 0, 0);
   pthread_create(&th1, NULL, incrementa, NULL);
   pthread_create(&th2, NULL, decrementa, NULL);
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   sem_destroy(&sem1);
   sem_destroy(&sem2);
   return 0;
}
