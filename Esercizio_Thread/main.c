#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#include "header.h"

void * produzione (void * m){

    mymonitor * monitor = (mymonitor *) m;

    srand(time(NULL));

    int valori[5];
    int num_valori;

    for (num_valori = 5; num_valori>0; num_valori--){

        for (int i=0; i<num_valori; i++){

            valori[i] = rand() % 10;

        }

        produci_valori(m,valori,num_valori);

    }

    pthread_exit(NULL);

}

void  * consumazione (void * m){

    mymonitor * monitor = (mymonitor *) m;

    for (int i=0; i<5; i++){

        consuma_valori(m);

    }

    pthread_exit(NULL);

}

int main(){

    pthread_t thread[4];
    int rc;

    mymonitor * m = (mymonitor *) malloc(sizeof(mymonitor));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    inizializza_monitor(m);

    rc = pthread_create(&thread[0],&attr,produzione,(void *) m);

    if (rc){
        printf("Errore nella creazione del thread! \n");
        exit(1);
    }

    for(int i=1; i<4; i++){

        rc = pthread_create(&thread[i],&attr,consumazione,(void *) m);

        if (rc){
        printf("Errore nella creazione del thread! \n");
        exit(1);
    }

    }

    for (int i=0; i<4; i++){

        pthread_join(thread[i],NULL);

    }

    rimuovi_monitor(m);

    free(m);

}