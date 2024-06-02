#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define CARS 500

pthread_t pts[CARS];
pthread_t out;
int slots [100];
int currentCars = 0;
int allCarsDone = 1;

//AusgabeThread
void * ausgabe() {

    //Beendet wenn jedes Autothread beednet
    while(allCarsDone) {
        printf("Belegte Plätze: %d \n Freie Plätze: %d \n", currentCars, 100 - currentCars);
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
    while(currentCars >= 100) {

    }
    //slots[i / 5] = 1;
    currentCars++;
    sleep((rand() % 4) + 1);
    //slots[i / 5] = 0;
    currentCars--;

    pthread_exit(NULL);
}

int main() {

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
}
