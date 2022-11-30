#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argumanlar[], char **envp)
{
    char* yeniArgv[argc - 2];
    char* command = argumanlar[2];
    int j = 0;

    for(int i = 0; i < argc; i++)
    {
	    printf("komut => %s\n", argumanlar[i]);
    }
    for(int i = 3; i < argc; i++)
    {
	    yeniArgv[j] = argumanlar[i];
	    j++;
    }
    yeniArgv[j] = NULL;
    int count = atoi(argumanlar[1]); // parametre count degerini alir.

    char *forcheck = "-t";
    int resultcheck = strcmp(argumanlar[0], forcheck);
	// -t kontrolu yapilir.Asagida kontrol sonucu kullanilir.
	
    if (resultcheck != 0) //girilen komut formata uygun degilse.
    {
	printf("\nYanlis bir komut girdiniz...\n");
	return 0;
    }


    int status;
    pid_t doFork;

    for(int i = 0; i < count; i++)
    {
        doFork = fork();
        if (doFork == 0){
           status=execve(command, yeniArgv, NULL);

	for(int i = 0; i < 3; i++)
	{
		printf("\n");
	}

	printf("hata\n");
        }
        else{
            wait(&status);
        }
    }
    

    return 0;
}
