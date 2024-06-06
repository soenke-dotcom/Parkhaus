#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define CARS 500
#define PARKINGSPOTS 100

pthread_t pts[CARS];
pthread_t info;
int allCarsDone = 1;
int currentCars = 0;

sem_t out;
sem_t in;
sem_t max;

void driveIn() {

    sem_wait(&max);//Falls kein Platz mehr frei wird Prozess hier aufgehalten
    sem_wait(&in);// Oder ein anderes Auto grade ins Parkhaus einfährt

    currentCars++; //Ansonsten fahre ein und erhöhe currentCars

    sem_post(&in);//Gib nun recht wieder frei, dass neues Auto reinfahren kann
    sem_post(&out);//Nun befindet sich mindestens ein Auto im Parkhaus, also kann auch eins rausfahren.
}

void driveOut() {

    sem_wait(&out);
    //sem_wait(&in);//Für Parkhaus mit nur einem Tor
    currentCars--;
    //sem_post(&in);//Für Parkhaus mit nur einem Tor
    sem_post(&max);
}

//AusgabeThread
void * ausgabe() {

    //Beendet wenn jeder Autothread beendet
    while(allCarsDone) {

        printf("Belegte Plätze: %d \n", currentCars);
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

    driveIn();
    sleep((rand() % 4) + 1);
    driveOut();

    pthread_exit(NULL);
}

int main() {

    //Semaphoren intialisieren
    sem_init(&in, 0, 1);
    sem_init(&out, 0, 0);
    sem_init(&max, 0, PARKINGSPOTS);

    //AusgabeThread erzeugen
    pthread_create(&info, NULL, ausgabe, NULL);

    //AutoThreads erzeugen
    for (int i = 0; i < CARS; i++) {

        pthread_create(&pts[i], NULL, car, NULL);
    }

    //Auf AutoThreads warten
    for (int i = 0; i < CARS; i++) {

        pthread_join(pts[i], NULL);
    }
    allCarsDone = 0;
    pthread_join(info, NULL);
}
