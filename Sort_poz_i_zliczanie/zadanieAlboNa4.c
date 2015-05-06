#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//SORTOWANIE PRZEZ ZLICZANIE
void COUNTINGSORT(char **A, char **B, int ILOSC_NAPIS, int POZYCJA){
int ZAKRE_WART = 127; //Zakres wybrany na podstawie ASCII
int C[1000]; //Tablica przechowywujaca ilosc wystapien danego zanku. Wartosc podana jako zwykle widzi-mi-sie.
            //rownie dobrze mozna dac tablice C[128] dla ASCII
int i=0;

//Wyzerowanie tablicy C zeby uniknπÊ bledow
for(i=0;i<=ZAKRE_WART;i++){
    C[i] = 0;
}

int j=0;
for(j=1;j<=ILOSC_NAPIS;j++){
    C[A[j][POZYCJA]] = C[A[j][POZYCJA]] + 1; //Zwiekszenie ilosci wystapien znaku o 1
}
for(i=1;i<=ZAKRE_WART;i++){
    C[i] = C[i] + C[i-1]; //Sumuje ilosc wystapien danego znaku i ilosc wystapien znaku mniejszego (INTERPRETACJA ASCII)
}

//Sortowanie
for(j=ILOSC_NAPIS;j>=1;j--){
    B[C[A[j][POZYCJA]]] = A[j]; //przypisanie odpowiednich znakow do odpowiednich komorek w tablicy WYJSCIOWEJ B
    C[A[j][POZYCJA]] = C[A[j][POZYCJA]]-1; //maksymalny indeks mozliwego wystapienia znaku zostaje zmniejszony o 1
}
}


//DRUKOWANIE NAPIS”W
void DRUK_TABLICE(char **A, int ILOSC_NAPIS){

int i=0;

for(i=1;i<=ILOSC_NAPIS;i++){
    printf("%s\n", A[i]);
}
}

//CZYTANIE WPROWADZANYCH NAPISOW DO TABLICY
void WPROWADZ_NAPIS(char **A, int ILOSC_NAPIS){
int MAX_DLUGOSC = 8;
char napis[MAX_DLUGOSC];
int i=0;

for(i=1;i<=ILOSC_NAPIS;i++){
    printf("PODAJ NAPIS: \n");
    scanf("%s", &napis); //Za≥adowanie napisu do zmiennej 'napis'
    A[i] = (char*) malloc(sizeof(char)*MAX_DLUGOSC); //Zarezerwowanie pamieci w tablicy dla napisu
    strcpy(A[i],napis); //Zaladowanie napisu'string' do tablicy
}
}

//SORTOWANIE POZYCYJNE
void RADIX_SORT(char **A, char **B,char **D, int ILOSC_NAPISOW){

int i=0;

//Wykonanie sortowania przez zliczanie dla kazdej pozycji od konca
for(i=7;i>=0;i--){
COUNTINGSORT(A,B,ILOSC_NAPISOW,i);
printf("Wedlug pozycji: %i\n", i+1);
DRUK_TABLICE(B,ILOSC_NAPISOW);
printf("\n\n");
D=A; //Tablica posortowana pozycyjnie dla danego indeksu staje siÍ tablicπ wejúciowπ do kolejnego COUNTINGSORTA
A=B;
B=D;
}
}

int main(){

int ILOSC_NAPIS;

printf("Sortowanie przez zliczanie\n");
printf("Marcin Hallman: 224705");
printf("\n\n");
printf("Ile napisow chcesz posortowac?:");
scanf("%i", &ILOSC_NAPIS);

//DEKLAROWANIE TABLIC WSKAèNIK”W DO WSKAèNIK”W
char **A=(char**) malloc(ILOSC_NAPIS*sizeof(char*)); //tablica wejsciowa przechowywujaca napisy REZERWACJA PAMIECI
char **B=(char**) malloc(ILOSC_NAPIS*sizeof(char*)); //tablica wyjsciowa przechowywujaca posortowane napisy REZERWACJA PAMIECI
char **D=(char**) malloc(ILOSC_NAPIS*sizeof(char*)); //tablica pomocnicza przy Sortowaniu pozycyjnym REZERWACJA PAMIECI

WPROWADZ_NAPIS(A,ILOSC_NAPIS);
printf("\n\n");
printf("Wprowadzone napisy:\n");
DRUK_TABLICE(A,ILOSC_NAPIS);

printf("\nSORTOWANIE\n\n");
printf("Posortowana tablica:\n");
//COUNTINGSORT(A,B,ILOSC_NAPIS);
RADIX_SORT(A,B,D,ILOSC_NAPIS);
//Tym razem wywolanie funkcji drukujacej tablice A!! Poniewaz, RADIX-SORT na koncu przypisuje tablice wejsciowa do A( dlatego tutaj znajduja sie napisy posortowane poprawnie)
DRUK_TABLICE(A,ILOSC_NAPIS);


//Zwolnienie pamiÍci
free(A);
free(B);
free(D);
return 0;


}
