#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int controlProcess(char** words, int wordCnt, char** envp){
	//gelen count sayisina gore dizi olusturuldu.
    	char* YeniArgv[wordCnt];
    	
    	//words parametresine gore ilgili if blogu calistirilir.
    	//Shell de hazir olan genel komutlar system ile calistirilir.
    	if(strcmp("exit",*(words)) == 0){
            printf("Cikis yapiliyor...");
            exit(0);
        }else if(strcmp("cat",*(words)) == 0){
            int i;
            printf("cat: ");
            for(i=1;i<wordCnt;i++){
                printf("%s ", words[i]);
            }
            printf("\n");
        }else if(strcmp("execx",*(words)) == 0){
            int i, pid;

            pid = fork();
            if (pid == 0) {
            //-t 5 program
            int i;
            for(i=1;i<wordCnt;i++){
		YeniArgv[i-1]=*(words+i);
	    }
                YeniArgv[wordCnt-1]=NULL;
		
                i=execve("execx", YeniArgv, envp);
                perror("error\n");
                exit(1);
            }
        }else if(strcmp("clear",*(words)) == 0){
            system("clear");
            printf("\n Ekran temizlendi...\n");
        }else if(strcmp("ls",*(words)) == 0){
          printf("\n Dosya Listesi...\n");
            system("ls");
        }else if(strcmp("bash",*(words)) == 0){
            //int i;
            int pid, h, status;

            pid = fork();

            if (pid > 0) {
                wait(&status);
            } else {
                YeniArgv[0]="bash>>";
                YeniArgv[1]=NULL;
                status=execve("/bin/bash", YeniArgv, envp);
                printf("bash>>");
                perror("error\n");
                exit(1);
            }
        }else if(strcmp("writef",*(words)) == 0){
            //int i;
            int pid, status;

            pid = fork();

            if (pid > 0) {
                wait(&status);
            } else {
                YeniArgv[0]=*(words+1);
                YeniArgv[1]=*(words+2);
                YeniArgv[2]=NULL;
                status=execve("writef", YeniArgv, envp);
                perror("error\n");
                exit(1);
            }
        }else{
            printf("Yanlis bir komut girdiniz..Lutfen tekrar giriniz.\n");
        }
        return 0;

}

//boşluk karakterine göre split eder.Kac adet word oldugunu hesaplar.
int charCount(char* str,char c){
    int i,paramCount,strLength;
    paramCount = 0;
    strLength = strlen(str);
    for(i=0;i<strLength;i++){
        if(*(str+i) == c){
            paramCount +=1;
        }
    }
    return paramCount;
}

char** splitStr(char* str,char* c,int wordCnt){
    char **words = (char**) malloc(wordCnt* sizeof(char *));
    char *token = strtok(str, c);

    int counter =0;
    while (token != NULL){   
        *(words+counter++)=token;
        token = strtok(NULL, c);
    }
    return words;
}


int main(int argc, char *argv[], char** envp){
    int exitControlVal;
    char str[58];
    printf("myshell>> ");
    while(scanf("%[^\n]",str)==1){    
        int wordCnt=charCount(str, ' ')+1;
        char **words=splitStr(str, " ",wordCnt);
        
        exitControlVal=controlProcess(words, wordCnt, envp);// exit komutu girilene kadar program calismaya devam eder.
       
        if(exitControlVal){
           break;        
        }
        printf("myshell>> ");
        scanf("%[^\n]",str);
        getchar();
    }
    
    return 0;

}
