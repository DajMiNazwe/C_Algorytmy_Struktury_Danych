#include <stdio.h>
#include <stdlib.h>






int haszowanie(int klucz){

int hasz;//zmienna przechowywujaca wynik haszowania

hasz=klucz%13;//sam wzor haszujacy

return hasz;//zwracanie klucza po haszowaniu
}

void wypisz(int tablica[], int rozmiar){

int i;

for(i=0;i<rozmiar;i++){
    printf("%i\n", tablica[i]);
}
}



void dodaj(int tablica[]){
int i;

for(i=0;i<5;i++){
    printf("Podaj %i liczbe: \n",i+1);
    scanf("%i", &tablica[i]);
}
}


void haszuj(int wejscie[], int wyjscie[]){

int i;
int pohasz;
int kolizja=0;
for(i=0;i<5;i++){
pohasz=haszowanie(wejscie[i]);
if(wyjscie[pohasz]!=0){
    kolizja++;
}
wyjscie[pohasz]=wejscie[i];
}
printf("%i",kolizja);
}


void zeruj(int tab[], int roz){
int i;
for(i=0;i<roz;i++){
    tab[i]=0;
}
}


int main(){


int A[5];
int B[100];
dodaj(A);
wypisz(A,5);
printf("\n\n");
zeruj(B,100);
haszuj(A,B);
wypisz(B,100);


return 0;
}
