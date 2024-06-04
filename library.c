#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define CARS 500

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sema;
pthread_t pts[CARS];
pthread_t out;
int currentCars = 0;
int allCarsDone = 1;

//AusgabeThread
void * ausgabe() {

    //Beendet wenn jeder Autothread beendet
    while(allCarsDone) {

        sem_wait(&sema);
        printf("Belegte Plätze: %d \n Freie Plätze: %d \n", currentCars, 100 - currentCars);
        sem_post(&sema);
        sleep(1);
    }
    pthread_exit(NULL);
}

//AutoThread
void * car() {

    //Parkplatz Nummer finden
    int i = 0;
    while (pthread_self() != pts[i]) {
        i++;
    }

    //warten falls voll
    sem_wait(&sema);
    while(currentCars >= 100) {
        sem_post(&sema);
        sleep(1);
    }

    sem_wait(&sema);
    currentCars++;
    sem_post(&sema);

    sleep((rand() % 4) + 1);

    sem_wait(&sema);
    currentCars--;
    sem_post(&sema);

    pthread_exit(NULL);
}

int main() {

    sem_init(&sema, 0, 1);
    //AusgabeThread erzeugen
    pthread_create(&out, NULL, ausgabe, NULL);

    //AutoThreads erzeugen
    for (int i = 0; i < CARS; i++) {

        pthread_create(&pts[i], NULL, car, NULL);
    }
    //Auf AutoThreads warten
    for (int i = 0; i < CARS; i++) {

        pthread_join(pts[i], NULL);
    }
    allCarsDone = 0;
    pthread_join(out, NULL);
}
