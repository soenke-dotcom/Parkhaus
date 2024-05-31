#include "library.h"

#include <stdio.h>
#define CARS 500

pthread_t pts[CARS];
pthread_t out;
int slots [500];
int currentCars = 0;

//AusgabeThread
void * ausgabe() {
    //Beendet wenn jedes Autothread beednet
    while(1) {
        printf("Belegte Plätze: &d\n Freie Plätze: &d\n", currentCars, CARS - currentCars);
        sleep(1);
    }

}

//AutoThread
void * car() {
    int i = 0;
    while ()
    while (currentCars < CARS) {

    }
}

int main() {

    //AusgabeThread erzeugen
    pthread_create(out, NULL, ausgabe, NULL);

    //AutoThread erzeugen
    for (int i = 0; i < CARS; i++) {

        pthread_create(&pts[i], NULL, car, NULL);
    }
    //Variable setzen --> Ausgabe Thread beenden

    //AufAuto Threads warten
    for (int i = 0; i < CARS; i++) {

        pthread_join(&pts[i], NULL);
    }

}
