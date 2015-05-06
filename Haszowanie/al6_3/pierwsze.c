#include <stdio.h>
#include <string.h>


int haszowanie(char slowo[]){

int i;
int litera;
int dlugosc;
long long int hasz;
int pierwsza;
int druga;
int kolejna;

pierwsza=slowo[0];
druga=slowo[1];

hasz=5*pierwsza+druga;

dlugosc=strlen(slowo);
for(i=2;i<dlugosc;i++){
    kolejna=slowo[i];
    hasz=hasz*5+kolejna;
}
return hasz;
}

void zeruj(int tab[],int rozmiar){
int i=0;

for(i=0;i<rozmiar;i++){
    tab[i]=0;
}
}



void test(int tab[], int rozmiar){

int i=0;
int zero=0;
long long int max=0;
double srednia=0;
int niezero=0;

for(i=0;i<rozmiar;i++){
    if(tab[i]==0){
        zero++;
    }else{
        srednia+=tab[i];
        niezero++;
    }
    if(tab[i]>max){
        max=tab[i];
    }
}

srednia=srednia/niezero;
printf("Zerowe eleemnty tablicy: %i\n", zero);
printf("Maksymalna wartosc tablicy: %i\n", max);
printf("Srednia wartosci niezerowych: %lf\n", srednia);

}


void koduj(int tab[],int rozmiar, int ilosc){
int i;
char slowo[20];
long long int indeks;

FILE *plik;
plik=fopen("3700.txt","r");
if(plik == NULL){//sprawdzanie mozliwosci otworzenia pliku
              printf("BLAD ODCZYTU!!\n");
              }else{
              printf("WCZYTANO\n\n");
              }
for(i=0;i<ilosc||feof(plik);i++){
    fscanf(plik,"%s",&slowo);
    indeks=haszowanie(slowo);
    tab[indeks*3%rozmiar]++;

}
test(tab,rozmiar);

}


int main(){

int rozmiar;
int ilosc;

printf("KONTROLNE SPRAWDZANIE DZIALANIA PROGRAMU Z DANYMI WYBIERANYMI OSOBISCIE!\n\n");
printf("Podaj rozmiar tablicy: ");
scanf("%i",&rozmiar);

int tablica[rozmiar];
zeruj(tablica,rozmiar);

printf("Podaj ilosc slow do wczytania: ");
scanf("%i", &ilosc);

koduj(tablica,rozmiar,ilosc);

printf("PRZEPROWADZANIE TESTOW!!!\n");
printf("KORZYSTNE WARTOSCI!:\n\n");
printf(" \n\n");
printf("ROZMIAR: 2221 ILOSC DANYCH: 3600\n");
int tablica2[2221];
zeruj(tablica2,2221);
koduj(tablica2,2221,3600);
printf(" \n\n");
printf("ROZMIAR: 1222 ILOSC DANYCH: 2460\n");
int tablica3[1222];
zeruj(tablica3,1222);
koduj(tablica3,1222,2460);
printf(" \n\n");
printf("ROZMIAR: 1697 ILOSC DANYCH: 3600\n");
int tablica7[1697];
zeruj(tablica7,1697);
koduj(tablica7,1697,3600);
printf(" \n\n");
printf("NIEKORZYSTNE WARTOSCI!:\n\n");
printf("ROZMIAR: 1500 ILOSC DANYCH: 2000\n");
int tablica4[1500];
zeruj(tablica4,1500);
koduj(tablica4,1500,2000);
printf(" \n\n");
printf("ROZMIAR: 1250 ILOSC DANYCH: 2500\n");
int tablica5[1250];
zeruj(tablica5,1250);
koduj(tablica5,1250,2500);
printf(" \n\n");
printf("ROZMIAR: 2007 ILOSC DANYCH: 3600\n");
int tablica6[2007];
zeruj(tablica6,2007);
koduj(tablica6,2007,3600);
return 0;
}
