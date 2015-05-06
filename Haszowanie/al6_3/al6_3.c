#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*DEKLARACJA STRUKTURY*/
typedef struct nazwiska{
    int liczba;
    char nazwisko[20];
}NAZWISKA;



/*FUNKCJA ZERUJACA CALA TABLICE*/
void zerujTablice(NAZWISKA doCzyszcz[], int rozmiar){

int i;
for(i=0;i<rozmiar;i++){
   doCzyszcz[i].liczba=0;
   strcpy(doCzyszcz[i].nazwisko,"brak");
}
}


/*FUNKCJA WCZYTUJACA PODANY ZAKRES INFORMACJI DO TABLICY O PODANYM ROZMIARZE*/
NAZWISKA* wczytaj(int zakres, int rozmiar){

/*rezerwacja pamieci odpowiedniej dla pozadanej tablicy*/
NAZWISKA* tablica=malloc(sizeof(NAZWISKA)*rozmiar);
int i;
FILE *plik;
 plik=fopen("nazwiska.txt", "r");
     if(plik == NULL){//sprawdzanie mozliwosci otworzenia pliku
              printf("BLAD ODCZYTU!!\n");
              }else{
              printf("WCZYTANO\n\n");
              }
     for(i=0;i<zakres||feof(plik);i++){//wczytywanie danych do kolejnych komorek tablicy wejsciowej
                      fscanf(plik,"%i %s", &tablica[i].liczba,&tablica[i].nazwisko);

                      }
     fclose(plik);

return tablica;//zwrócenie tablicy z wczytanymi danymi
}

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

/*FUNKCJA HASZUJACA JEDNO NAZWISKO I WSTAWIAJACA DO TABLICY*/
/*opis dzialania znajduje sie w funkcji koduj*/
void kodujJeden(NAZWISKA wyjscie[], int zakres2){

int i,j=0;
int indeks;
int poczatek;
int kolizja=0;

int popularnosc=0;
char nazwisko[20];

printf("\n\nPodaj nazwisko: ");
scanf("%s",&nazwisko);
printf("\n\nPodaj popularnosc: ");
scanf("%i",&popularnosc);

indeks=haszowanie(nazwisko);
poczatek=indeks;
//printf("RAZ\n\n");

while(wyjscie[indeks].liczba!=0&&indeks<zakres2){
   // printf("pocz-czy-wolne\n\n");
    indeks++;
    kolizja++;
}
if(wyjscie[indeks].liczba==0&&indeks<zakres2){
//printf("wolne\n");
wyjscie[indeks].liczba=popularnosc;
strcpy(wyjscie[indeks].nazwisko,nazwisko);
//printf("udane\n");
}
if(indeks==zakres2){
    indeks=0;
    while(wyjscie[indeks].liczba!=0 && indeks<poczatek){
       // printf("pocz-kon\n");
        indeks++;
        kolizja++;
    }
    if(wyjscie[indeks].liczba==0&&indeks<poczatek){
       // printf("pocz-wolne");
        wyjscie[indeks].liczba=popularnosc;
        strcpy(wyjscie[indeks].nazwisko,nazwisko);

       // printf("\npocz-wolne-udane");
    }
    if(indeks==poczatek){
       // printf("KONIEC TABLICY!!!\n\n");
    }
}


printf("\n\nIlosc kolizji dla jednego nazwiska: %i",kolizja);
}
/*FUNKCJA HASZUJACA CALA TABLICE*/
void koduj(NAZWISKA wejscie[], int zakres, NAZWISKA wyjscie[], int zakres2){

int i,j=0;
int indeks;
int poczatek;
int kolizja=0;
int srednia=0;



for(i=0;i<zakres;i++){
indeks=haszowanie(wejscie[i].nazwisko);
poczatek=indeks;
// printf("RAZ\n\n");
/*Dopoki nie ma wolnego miejsca i indeks jest mniejszy od rozmiaru tablicy wyjsciowej to*/
while(wyjscie[indeks].liczba!=0&&indeks<zakres2){
  //  printf("pocz-czy-wolne\n\n");
    indeks++;
    kolizja++;
}
/*Jesli jest wolne miejsce i nie trafilismy na koniec tablicy to*/
if(wyjscie[indeks].liczba==0&&indeks<zakres2){
//printf("wolne\n");
wyjscie[indeks]=wejscie[i];
//printf("udane\n");
}
/*Jesli trafilismy na koniec tablicy to zaczynamy od poczatku*/
if(indeks==zakres2){
    indeks=0;
    /*Przeszukuje tablice od poczatku do indeksu startowego jesli wczesniej nie bylo miejsca*/
    while(wyjscie[indeks].liczba!=0 && indeks<poczatek){
      //  printf("pocz-kon\n");
        indeks++;
        kolizja++;
    }
    /*Jesli jest wolne miejsce i nie trafilismy na indeks startowy*/
    if(wyjscie[indeks].liczba==0&&indeks<poczatek){
      //  printf("pocz-wolne");
        wyjscie[indeks]=wejscie[i];
    }
    /*Jesli tablica jest cala pelna to drukuje stosowny komunikat*/
    if(indeks==poczatek){
     //   printf("KONIEC TABLICY!!!\n\n");
    }
}
}
srednia=kolizja/zakres;
printf("Srednia prob wstawien: %i\n\n",srednia);
}


int main(){

int i;
int rozmiar,rozmiar2;
int zakres;

printf("HASZOWANIE [W+OL], MARCIN_HALLMAN_224705\n\n");
printf("********************************************************\n\n");
printf("1. W celu przeprowadzenia wydruku prosze odkomentowac stosowne petle for w main'ie\n");
printf("2. Aby program dzialal poprawnie nalezy ZAWSZE zostawic JEDNO wolne miejsce w pierwszej tablicy zakres<=rozmiar-1\n\n");
printf("********************************************************\n\n");
printf("Podaj rozmiar tablicy: ");
scanf("%i", &rozmiar);
printf("\n\nPodaj zakres do wypelnienia: ");
scanf("%i", &zakres);
printf("\n\nPodaj rozmiar tablicy haszujacej(wiekszy lub rowny 1000): ");
scanf("%i",&rozmiar2);

/*deklaracja tablicy wyjsciowej przechowywujacej nazwiska po haszowaniu*/
NAZWISKA wyjscie[rozmiar2];
/*deklaracja tablicy wejsciowej z wykorzystaniem funkcji wczytujacek*/
NAZWISKA* spis=wczytaj(zakres,rozmiar);

/*printf("Tablica zawiera:\n\n");
for(i=0;i<rozmiar;i++){
    printf("%i %s\n", spis[i].liczba,spis[i].nazwisko);

}*/

zerujTablice(wyjscie,rozmiar2);//zerowanie tablicy wyjsciowej w celu unikniecia wypisywania smieci
koduj(spis,zakres,wyjscie,rozmiar2);//haszowanie tablicy wejsciowej 'spis'

/*printf("\n\nTablica Haszujaca:\n\n");
for(i=0;i<rozmiar2;i++){//wypisanie tablicy wyjsciowej
    printf("%i %i %s\n",i, wyjscie[i].liczba,wyjscie[i].nazwisko);

}*/

kodujJeden(wyjscie,rozmiar2);//haszowanie pojedynczego nazwiska

/*printf("\n\nTablica Haszujaca:\n\n");
for(i=0;i<rozmiar2;i++){//wypisanie tablicy wyjsciowej
    printf("%i %i %s\n",i, wyjscie[i].liczba,wyjscie[i].nazwisko);

}*/

free(spis);//zwolnienie tablicy wejsciowej


return 0;
}
