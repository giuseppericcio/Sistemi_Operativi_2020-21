#include <unistd.h> //per la fork()
#include <stdio.h> //per la printf
#include <sys/wait.h> //per la wait
#include <sys/types.h> //per pid_t
#include <stdlib.h> //per exit()

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