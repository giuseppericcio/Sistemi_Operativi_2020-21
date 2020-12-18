#ifndef _HEADER_H
#define _HEADER_H

#include <pthread.h>

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

#define DIM_BUF 5

typedef struct 
{
    int elementi[DIM_BUF];
    int stato[DIM_BUF];   // LIBERO, IN_USO, oppure OCCUPATO
    int elementi_liberi;
    int elementi_occupati;
    // ... aggiungere altre variabili per la sincronizzazione ...
    pthread_mutex_t mutex;
    pthread_cond_t CVprod;
    pthread_cond_t CVcons;

}mymonitor;

void inizializza_monitor(mymonitor * m);
void rimuovi_monitor(mymonitor * m);
void produci_valori (mymonitor * m, int valori[], int num_valori);
int consuma_valori (mymonitor * m);

#endif