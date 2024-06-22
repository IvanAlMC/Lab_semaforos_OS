#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t A, B;

void *escribirA (void *p) {
   int i;
   for (i = 0; i < 5; i++) {
      sem_wait(&A);
      printf("A");
      fflush(stdout);
      sem_post(&B);
      sleep(random() % 3);
   }
   pthread_exit(NULL);
}

void *escribirB (void *p) {
   int i;
   for (i = 0; i < 5; i++) {
      sem_wait(&B);
      printf("B");
      fflush(stdout);
      sem_post(&A);
      sleep(random() % 2);
   }
   pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
   pthread_t th1, th2;
   srandom(time(NULL));
   sem_init(&A, 0, 0);
   sem_init(&B, 0, 1);
   pthread_create(&th1, NULL, escribirA, NULL);
   pthread_create(&th2, NULL, escribirB, NULL);
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   sem_destroy(&A);
   sem_destroy(&B);
   return 0;
}
