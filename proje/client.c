#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sFileList
{
    char fileName[20];
} s_fl;

s_fl FileLists[10];

int DeleteFile(char *filename)
{

    for (int i = 0; i < 10; i++)
    {
        if (FileLists[i].fileName[0] != NULL)
        {
            int sayac = 0;
            for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
            {
                if (FileLists[i].fileName[j] == filename[j])
                {
                    sayac++;
                }
            }
            if (sayac == sizeof(filename) / sizeof(filename[0]))
            {
                int sonuc = remove(strcat(filename, ".txt"));

                for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
                {
                    FileLists[i].fileName[j] = NULL;
                }
                return 0; // basarili sildi
            }
        }
    }

    return 1; // silinmek istenen dosya adı listede yok
}




int WriteFile(char *filename, char *gelenText)
{
    strcat(filename, ".txt");
    for (int i = 0; i < 10; i++)
    {
        if (FileLists[i].fileName[0] != NULL)
        {
            int sayac = 0;
            for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
            {
                if (FileLists[i].fileName[j] == filename[j])
                {
                    sayac++;
                }
            }

            if (sayac == sizeof(filename) / sizeof(filename[0]))
            {
                FILE *fptr;
                fptr = fopen(FileLists[i].fileName, "a+");
                if (fptr == NULL)
                {
                    printf("Error!");
                    exit(1);
                }
                fprintf(fptr, "%s \n", gelenText);
                fclose(fptr);

                return 0; // basarili sekilde dosyaya yazildi
            }
        }
    }

    return 1; // yazilmasi istenen dosya listede YOK.
}

int CreateFile(char *filename)
{
    printf("gelen file name %s  \n", filename);

    for (int i = 0; i < 10; i++)
    {
        if (FileLists[i].fileName[0] != NULL)
        {
            int sayac = 0;
            for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
            {
                if (FileLists[i].fileName[j] == filename[j])
                {
                    sayac++;
                }
            }
            if (sayac == sizeof(filename) / sizeof(filename[0]))
            {
                return 0;
            }
        }
    }

    for (int i = 0; i < sizeof(filename) / sizeof(filename[0]); i++)
    {
        if (FileLists[i].fileName[0] == NULL)
        {
            for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
            {
                FileLists[i].fileName[j] = filename[j];
            }
            FILE *fp;
            fp = fopen(strcat(FileLists[i].fileName, ".txt"), "w");
            fclose(fp);
            return 1;
        }
    }

    return 1;
}

int ReadFile(char *filename, int line)
{
    strcat(filename, ".txt");
    for (int i = 0; i < 10; i++)
    {
        if (FileLists[i].fileName[0] != NULL)
        {
            int sayac = 0;
            for (int j = 0; j < sizeof(filename) / sizeof(filename[0]); j++)
            {
                if (FileLists[i].fileName[j] == filename[j])
                {
                    sayac++;
                }
            }
            if (sayac == sizeof(filename) / sizeof(filename[0]))
            {
                FILE *ptr;
                char ch;
                ptr = fopen(filename, "r");
                if (NULL == ptr)
                {
                    printf("file can't be opened \n");
                }
                printf("-----Dosyadan Okunan Yazi-----\n");
                do
                {
                    ch = fgetc(ptr);
                    printf("%c", ch);

                } while (ch != EOF);
                fclose(ptr);
                return 0; // basarili sekilde dosyaya yazildi
            }
        }
    }

    return 1;
}

int main()
{
    char str[100];
    char fileName[20];
    char gelenText[50];
    int okunacakLine;

    printf("** ISLEMLER **\n\n");
    printf("CREATE\n");
    printf("DELETE\n");
    printf("READ\n");
    printf("WRITE\n");
    printf("EXIT\n\n");
    printf("********\n\n\n");

    while (1 == 1)
    {
        printf("\n");
        printf("ISLEM GIRINIZ : ");
        scanf("%[^\n]", str);
        getchar();

        if (strcmp("EXIT", (str)) == 0)
        {
            printf("Cikis yapiliyor...\n");
            exit(0);
        }
        else if (strcmp("CREATE", (str)) == 0)
        {
            printf("Lutfen olusturulacak fileName giriniz : ");
            gets(fileName);

            int kontrol = CreateFile(fileName);

            if (kontrol == 1) // olustulacak dosya yoksa olusturur
            {
                printf("%s dosyasi yoktu ve basarili sekilde olusturuldu. \n", fileName);
            }
            if (kontrol == 0) // olusturulacak dosya varsa
            {
                printf("olusturmak istediginiz dosya adinda bir dosya listede zaten mevcuttur...\n");
            }
        }
        else if (strcmp("DELETE", (str)) == 0)
        {
            printf("Lutfen olusturulacak fileName giriniz : ");
            gets(fileName);
            int kontrol = DeleteFile(fileName);
            if (kontrol == 0)
            {
                printf("dosya basariyla silindi...");
            }
            if (kontrol == 1)
            {
                printf("aranan dosya yok\n");
            }
        }
        else if (strcmp("READ", (str)) == 0)
        {

            printf("Lutfen okunacak fileName giriniz : ");
            gets(fileName);
            printf("Hangi line okunacak lutfen giriniz : ");
            scanf("%d", &okunacakLine);
            getchar();


            int kontrol = ReadFile(fileName, okunacakLine);

            if (kontrol == 0) // okunacak dosya varsa
            {
                printf("%s dosyasi okundu ve basarili sekilde ekrana yazildi.. \n", fileName);
            }
            if (kontrol == 1) // olusturulacak dosya yoksa
            {
                printf("olusturmak istediginiz dosya adinda bir dosya listede zaten mevcuttur...\n");
            }
        }
        else if (strcmp("WRITE", (str)) == 0)
        {
            printf("Lutfen ustune yazilacak fileName giriniz : ");
            gets(fileName);
            printf("Lutfen dosyaya yazilacak metini yaziniz.. : ");
            gets(gelenText);
            int kontrol = WriteFile(fileName, gelenText);
            if (kontrol == 0)
            {
                printf("Metin dosyaya yazildi\n");
            }
            if (kontrol == 1)
            {
                printf("Yazilmak istenen dosya mevcut değil\n");
            }
        }
        else
        {
            printf("Hatali giris yapildi. Tekrar giris yapiniz.\n");
        }
    }

    return 0;
}