#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){

    pid_t pid = fork();

    if (pid == 0){
        
        /*codice figlio*/
        char * parametri[3];
        parametri[0] = "ps";
        parametri[1] = "aux";
        parametri[2] = NULL;

        execvp("ps", parametri);

        perror("exec fallita!");
        exit(1);

    }
    else if (pid == -1){

        perror("fork fallita");
        exit(1);
    }

    /*codice padre*/

    wait(NULL);
    printf("Sono il padre con PID: [%d]\n", getpid());
    printf("La exec ha terminato correttamente");

    return 0;
}