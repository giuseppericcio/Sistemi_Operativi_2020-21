#include "header.h"
#include <stdio.h>
#include <unistd.h>

void inizializza_monitor(mymonitor * m){

    for (int i=0; i<5; i++){
        m->elementi[i] = 0;
        m->stato[i] = LIBERO;        
    }

    m->elementi_occupati = 0;
    m->elementi_liberi = 5;

    pthread_mutex_init(&(m->mutex),NULL);

    pthread_cond_init(&(m->CVprod),NULL);
    pthread_cond_init(&(m->CVcons),NULL);

}

void rimuovi_monitor(mymonitor * m){

    pthread_mutex_destroy(&(m->mutex));
    pthread_cond_destroy(&(m->CVprod));
    pthread_cond_destroy(&(m->CVcons));

}

void produci_valori(mymonitor * m, int valori[], int num_valori){
    
    int indice = 0;
    int k = 0;
    int posizioni[num_valori];

    pthread_mutex_lock(&(m->mutex));

    while (num_valori < m->elementi_liberi){

        pthread_cond_wait(&(m->CVprod),&(m->mutex));
    }

    while (indice < num_valori){

        if (m->stato[indice] == LIBERO){

            posizioni[k] = indice;
            m->stato[indice] = IN_USO;
            k++;

        }

        indice++;
    
    }

    pthread_mutex_unlock(&(m->mutex));

    for (int i=0; i<num_valori; i++){
        m->elementi[posizioni[i]] = valori[i];
        m->stato[posizioni[i]] = OCCUPATO;
        m->elementi_occupati = m->elementi_occupati + 1;
        m->elementi_liberi = m->elementi_liberi - 1;

        printf("Valore prodotto %d in posizione [%d] \n", valori[i], posizioni[i]);
    }

    sleep(1);

    pthread_cond_signal(&(m->CVcons));
    
}

int consuma_valori(mymonitor * m){

    int indice = 0;

    pthread_mutex_lock(&(m->mutex));

    while (m->elementi_occupati == 0){

        pthread_cond_wait(&(m->CVcons),&(m->mutex));

    }

    while (indice < DIM_BUF && m->stato[indice] != LIBERO){
        indice++;
    }

    m->stato[indice] = IN_USO;

    pthread_mutex_unlock(&(m->mutex));

    sleep(1);

    int valore = m->elementi[indice];
    m->elementi_liberi = m->elementi_liberi + 1;
    m->elementi_occupati = m->elementi_occupati - 1;
    m->stato[indice] = LIBERO;

    printf("Valore consumato %d in posizione [%d] \n", valore, indice);

    pthread_cond_signal(&(m->CVprod));
    
}