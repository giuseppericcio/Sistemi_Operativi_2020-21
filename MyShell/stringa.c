#include <stdio.h>
#include <string.h>

int main(void)
{
    int toknum = 0;
    char * frase = NULL;
    size_t len = 0;
    const char delimiters[] = " \n";

    printf("Inserisci una frase (le parole devono essere separate da punto e virgola): ");
    getline(&frase,&len,stdin);
    char *tmp = strtok(frase, delimiters);
    while (tmp != NULL)
    {
        printf("%d: [%s]\n", ++toknum, tmp);
        tmp = strtok(NULL, delimiters);
    }
    
    return 0;

}
