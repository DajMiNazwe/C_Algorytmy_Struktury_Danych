#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//SORTOWANIE PRZEZ ZLICZANIE
void COUNTINGSORT(char **A, char **B, int ILOSC_NAPIS){
int ZAKRE_WART = 127; //Zakres wybrany na podstawie ASCII
int C[1000]; //Tablica przechowywujaca ilosc wystapien danego znaku
int i=0;

//Wyzerowanie tablicy C zeby uniknac bledow
for(i=0;i<=ZAKRE_WART;i++){
    C[i] = 0;
}

int j=0;
for(j=1;j<=ILOSC_NAPIS;j++){
    C[A[j][0]] = C[A[j][0]] + 1; //Zwiekszenie ilosci wystapien znaku o 1
}
for(i=1;i<=ZAKRE_WART;i++){
    C[i] = C[i] + C[i-1]; //Sumuje ilosc wystapien danego znaku i ilosc wystapien znaku mniejszego (INTERPRETACJA ASCII)
}

//Faktyczne sortowanie
for(j=ILOSC_NAPIS;j>=1;j--){
    B[C[A[j][0]]] = A[j]; //przypisanie odpowiednich napisow do tablicy WYJSCIOWEJ B
    C[A[j][0]] = C[A[j][0]]-1; //maksymalny indeks mozliwego wystapienia zostaje zmniejszony o 1
}
}






//DRUKOWANIE NAPISÓW
void DRUK_TABLICE(char **A, int ILOSC_NAPIS){

int i=0;

for(i=1;i<=ILOSC_NAPIS;i++){
    printf("%s\n", A[i]);
}
}


void WPROWADZ_NAPIS(char **A, int ILOSC_NAPIS){
int MAX_DLUGOSC = 8;
char napis[MAX_DLUGOSC];
int i=0;

for(i=1;i<=ILOSC_NAPIS;i++){
    printf("PODAJ NAPIS: \n");
    scanf("%s", &napis); //Zaladowanie napisu do zmiennej 'napis'
    A[i] = (char*) malloc(sizeof(char)*MAX_DLUGOSC); //Zarezerwowanie pamieci w tablicy dla napisu
    strcpy(A[i],napis); //Zaladowanie napisu'string' do tablicy
}
}



int main(){

int ILOSC_NAPIS;

printf("Sortowanie przez zliczanie\n");
printf("Marcin Hallman: 224705");
printf("\n\n");
printf("Ile napisow chcesz posortowac?:");
scanf("%i", &ILOSC_NAPIS);

//DEKLAROWANIE TABLIC WSKAZNIKÓW DO WSKAZNIKÓW
char **A=(char**) malloc(ILOSC_NAPIS*sizeof(char*));
char **B=(char**) malloc(ILOSC_NAPIS*sizeof(char*));

WPROWADZ_NAPIS(A,ILOSC_NAPIS);
printf("\n\n");
printf("Wprowadzone napisy:\n");
DRUK_TABLICE(A,ILOSC_NAPIS);

printf("\nSORTOWANIE\n\n");
printf("Posortowana tablica:\n");
COUNTINGSORT(A,B,ILOSC_NAPIS);
DRUK_TABLICE(B,ILOSC_NAPIS);


//zwolnienie pamieci
free(A);
free(B);

return 0;


}
