#include <stdio.h>
#include <string.h>


typedef struct nazwiskawej{
char nazwisko[20];

}NAZWISKAWEJ;

typedef struct nazwiskawyj{
int liczba;
struct nazwiskawyj *next;
}NAZWISKAWYJ;

/*FUNKCJA HASZUJACA POJEDYNCZE NAZWISKO*/
int haszowanie(char napis[]){

int hasz=0;//zmienna przechowywujaca wynik haszowania
int dlugosc=strlen(napis);//zmienna przechowywujaca dlugosc nazwiska
int i;
int litera;
int kod;
for(i=0;i<dlugosc;i++){
        //zamiana litery na kod ASCII
        litera=napis[i];
        //obliczanie wartosci litery mod 13
        kod=litera%7;
        //sumowanie wartosci przerobionych liter
        hasz+=kod;
}
return hasz;//zwracanie klucza po haszowaniu
}

void koduj(NAZWISKAWEJ wejsciowa[], int rozmiar,NAZWISKAWYJ wyjsciowa[], int rozmiar2){
int i,j=0;
int indeks;
int poczatek;
int kolizja=0;
int srednia=0;
int sukces=0;

for(i=0;i<rozmiar;i++){
    indeks=haszowanie(wejsciowa[i].nazwisko);
    while(wyjsciowa[indeks].liczba!=0){
        kolizja++;
        wyjsciowa[indeks]=wyjsciowa[indeks]->next;
    }
    wyjsciowa[indeks].liczba=indeks;
}




}
void zerujTablice(NAZWISKAWYJ doCzyszcz[], int rozmiar){

int i;
for(i=0;i<rozmiar;i++){
   doCzyszcz[i].liczba=0;
   doCzyszcz[i].next=NULL;
}
}

NAZWISKAWEJ* wczytaj(int rozmiar){

int i;
NAZWISKAWEJ* tablica=malloc(sizeof(NAZWISKAWEJ)*rozmiar);

FILE *plik;
plik=fopen("3700.txt", "r");
if(plik == NULL){//sprawdzanie mozliwosci otworzenia pliku
              printf("BLAD ODCZYTU!!\n");
              }else{
              printf("WCZYTANO\n\n");
              }
for(i=0;i<rozmiar||feof(plik);i++){
    fscanf(plik,"%s",&tablica[i].nazwisko);
}

fclose(plik);
return tablica;
}






int main(){
int i;
int rozmiar,rozmiar2;


printf("HASZOWANIE AL6_2, MARCIN_HALLMAN_224705\n\n");
printf("Podaj rozmiar tablicy: ");
scanf("%i", &rozmiar);
printf("\n\nPodaj rozmiar tablicy: ");
scanf("%i",&rozmiar2);

//NAZWISKAWYJ* wyjscie=malloc(sizeof(NAZWISKAWYJ)*rozmiar2);
//zerujTablice(wyjscie,rozmiar2);

NAZWISKAWYJ wyjscie[rozmiar2];
zerujTablice(wyjscie,rozmiar2);
/*deklaracja tablicy wejsciowej z wykorzystaniem funkcji wczytujacek*/
NAZWISKAWEJ* spis=wczytaj(rozmiar);

for(i=0;i<rozmiar;i++){
    printf("%s\n",spis[i].nazwisko);
}

for(i=0;i<rozmiar2;i++){
    printf("%i\n",wyjscie[i].liczba);
}

koduj(spis,rozmiar,wyjscie,rozmiar2);

for(i=0;i<rozmiar2;i++){
    printf("%i\n",wyjscie[i].liczba);
}
return 0;
}
