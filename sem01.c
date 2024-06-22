#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define MAX 6

sem_t A, B, C;

void *escribirA (void *nada) {
   int num;
   for (num = 0; num < MAX; num++) {
      sem_wait(&A);
      printf("A");
      fflush(stdout);
      sem_post(&B);
      sleep(random() % 3);
   }
   pthread_exit(NULL);
}

void *escribirB (void *nada) {
   int num;
   for (num = 0; num < MAX; num++) {
      sem_wait(&B);
      printf("B");
      fflush(stdout);
      sem_post(&C);
      sleep(random() % 2);
   }
   pthread_exit(NULL);
}

void *escribirC (void *nada) {
   int num;
   for (num = 0; num < MAX; num++) {
      sem_wait(&C);
      printf("C");
      fflush(stdout);
      sem_post(&A);
      sleep(random() % 2);
   }
   pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
   pthread_t th1, th2, th3;
   srandom(time(NULL));
   sem_init(&A, 0, 1);
   sem_init(&B, 0, 0);
   sem_init(&C, 0, 0);
   pthread_create(&th1, NULL, escribirA, NULL);
   pthread_create(&th2, NULL, escribirB, NULL);
   pthread_create(&th3, NULL, escribirC, NULL);
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   sem_destroy(&A);
   sem_destroy(&B);
   sem_destroy(&C);
   return 0;
}
