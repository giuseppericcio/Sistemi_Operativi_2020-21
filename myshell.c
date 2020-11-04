#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
 
int main(int argc, char *argv[]){
    
    char programma[20];
    char * parametri[20];
    int i = 1;
    char * comando = NULL;
	size_t len = 20;
    const char delimiters[] = " \n";
    
    printf("HELLO USER \n");
    printf("Welcome into My Shell \n");
       
    while(1){
	
		int pid, status;
		pid = fork();
			
		if (pid == -1) 
		{
			
			perror("Generazione del processo fallita");
			exit(1);

		}   
			
		if(pid == 0)
		{
			
			printf("Inserisci comando (i parametri devono essere separati da punto e virgola): ");
    		getline(&comando,&len,stdin);
    		char * tmp = strtok(comando, delimiters);
    		parametri[0] = tmp;
			strcpy(programma,tmp);

    		while (tmp != NULL)
    		{
        		tmp = strtok(NULL, delimiters);
				parametri[i] = tmp;
				i++;
			}
			
			execvp(programma,parametri);
			printf("exec fallita!\n");
			exit(1);

		}
			
		else if(pid > 0) 
		{
			
			wait(&status);

			printf("\nIl figlio %d ha terminato l'esecuzione ", pid);
			if ( WIFEXITED(status) )
			{
				printf("con stato: %d\n\n", WEXITSTATUS(status));
			} 
			else 
			{
					printf("involontariamente!\n\n");
			}

		}

		return 0;
    
    }
    
}