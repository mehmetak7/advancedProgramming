#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char *argumanlar[], char **envp)
{

    struct tm *fulltime;
    time_t currentTime;
    time(&currentTime);
    fulltime = localtime(&currentTime); //sistemin detaylı time bilgisini fulltime adli yapıda tutuyorum.
    
    FILE *file;
    if (strcmp(argumanlar[0], "-f") == 0)//-f argumani dogru girilmis mi kontrol edilir.
    {
        if (argc != 3)
        {
            if (access(argumanlar[1], F_OK) != 0) // dosya acces kontrol yapar yoksa acar ve yazar.
            {
                file = fopen(argumanlar[1], "w");
            }
            else
            {
                file = fopen(argumanlar[1], "a"); // dosya varsa append modda acar.
            }
            fprintf(file, "pid:%d, ppid:%d, time: %s", getpid(), getppid(), asctime(fulltime)); //dosyaya istenen bilgiler yazilir.
            fclose(file); //dosy islemi bitince kapatir dosyayi
            printf("Dosya basarili bir sekilde olusturuldu ve kaydedildi.\n");
        }
    }
    else
        {
            printf("'%s' Dogru bir komut degildir.Ornek komut: writef -f DosyaAdı \n", argumanlar[0]); //yanlis girdiler icin ornek format gosterir.
        }

    return 0;
}
