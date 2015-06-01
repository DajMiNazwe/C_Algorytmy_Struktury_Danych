#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void liczymy(int tablica[], int rozmiar)
     {
     int ilosc=0,max=0,i;
     double srednia=0,ile=0;
            for(i=0;i<rozmiar;i++)
                    {
                    if(tablica[i]==0)
                                 ilosc++;
                    else
                        {
                        srednia+=tablica[i];
                        ile++;
                        }
                    if(tablica[i]>max)
                                  max=tablica[i];
                    }
            srednia=srednia/ile;
            printf("Zerowe eleemnty tablicy: %i\n", ilosc);
            printf("Maksymalna wartosc tablicy: %i\n", max);
            printf("Srednia wartosci niezerowych: %lf\n", srednia);
     }

void haszowanie(int tablica[], int rozmiar)
     {
     int i=0;
     for(i=0; i<rozmiar; i++)
              tablica[i]=0;
     long long wynik=0;
     int n=0;
     char napis[30];
         FILE *plik;
         plik=fopen("3700.txt", "r");
     if(plik == NULL){
              printf("nie moge otworzyc pliku\n");
              }
     else
     {                                        //!!!!!!!!!!!!!!!!
        while(fscanf(plik, "%s", napis) != EOF){
                         int dlugosc = strlen(napis);
                         wynik=5*napis[0]+napis[1];
                         for(i=2; i<dlugosc; i++)
                          wynik=wynik*5+napis[i];
                          tablica[wynik*2%rozmiar]++;
                      }
     fclose(plik);
     }
     liczymy(tablica,rozmiar);
     }
int main(int argc, char *argv[])
{
    int rozmiar=0,ilosc=0;
    char napis[30];
        FILE *plik;
        plik=fopen("3700.txt", "r");
    if(plik == NULL){
              printf("nie moge otworzyc pliku\n");
              }
    else
    {                                        //!!!!!!!!!!!!!!!!
        while(fscanf(plik,"%s", napis) != EOF){
                          ilosc++;
                      }
     fclose(plik);
     }
    ilosc/=2;
        FILE *plik2;
        plik2=fopen("pierwsze.txt", "r");
   if(plik2 == NULL){
              printf("nie moge otworzyc pliku\n");
              }
    else
    {                                        //!!!!!!!!!!!!!!!!
     while(ilosc>rozmiar){
                          ilosc++;
                      fscanf(plik2,"%i", &rozmiar);
                      }
     }
    ilosc=0;
    int tablica[rozmiar];
    printf("Korzystne: \n");
    haszowanie(tablica, rozmiar);
    fscanf(plik2,"%i", &rozmiar);
    tablica[rozmiar];
    haszowanie(tablica, rozmiar);
    fscanf(plik2,"%i", &rozmiar);
    tablica[rozmiar];
    haszowanie(tablica, rozmiar);
    printf("Niekorzystne: \n");
    fclose(plik2);
    tablica[1872];
    haszowanie(tablica, 1872);
    tablica[1874];
    haszowanie(tablica, 1874);
    tablica[1876];
    haszowanie(tablica, 1876);
    return 0;
}
