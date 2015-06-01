#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tablicaDoNazwisk[10], i, dlugosc=0,hasz=0,x=0, mod;
//char nazwisko[];

//struktura nazwiska
typedef struct nazwiska{
    int liczba;
    char nazwisko[20];
}NAZWISKA;
//zerowanie tablicy
void zerujTablice(NAZWISKA doCzyszcz[], int rozmiar){

int i;
for(i=0;i<rozmiar;i++){
   doCzyszcz[i].liczba=0;
   strcpy(doCzyszcz[i].nazwisko,"brak");
}
}
//HASZOWANIE hehe

int haszowanie(char napis[]){

int hasz=0;
int dlugosc=strlen(napis);
int i;
int litera;
int kod;
for(i=0;i<dlugosc;i++){
        litera=napis[i];
        kod=(litera*111)%7;
        hasz+=kod;
}
return hasz;
}
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

/*void dodaj(){
    for(i=0;i<2;i++) {
          //  nazwisko[]=NULL;
            printf("\nPodaj nazwisko:\n");
            scanf("%s",&nazwisko);
            while(nazwisko[dlugosc]!='\0') {
                    if(nazwisko[dlugosc+1]!='\0'){
                    x=111*nazwisko[dlugosc]+nazwisko[dlugosc+1];
                    hasz=hasz+x;
                    dlugosc++;
                    }
                    else{
                            hasz=hasz*111+nazwisko[dlugosc];
                            dlugosc++;
                    }
                    mod=hasz%2;
                    tablicaDoNazwisk[mod]=hasz;
    }
}
}
*/

//HASZOWANIE CALEJ TABLICY
void koduj(NAZWISKA wejscie[], int zakres, NAZWISKA wyjscie[], int zakres2){

int i,j=0;
int indeks;
int poczatek;
int kolizja=0;
int srednia=0;
int sukces=0;


for(i=0;i<zakres;i++){
indeks=haszowanie(wejscie[i].nazwisko);
poczatek=indeks;
// printf("RAZ\n\n");
while(wyjscie[indeks].liczba!=0&&indeks<zakres2){
    //indeks=indeks*indeks;
    indeks++;
    kolizja++;
}
if(wyjscie[indeks].liczba==0&&indeks<zakres2){

wyjscie[indeks]=wejscie[i];
}
if(indeks==zakres2){
    indeks=0;
    while(wyjscie[indeks].liczba!=0 && indeks<poczatek){

        //indeks=indeks*indeks;
        indeks++;
        kolizja++;
    }
    if(wyjscie[indeks].liczba==0){

        wyjscie[indeks]=wejscie[i];
    }
    if(indeks==poczatek){
        printf("KONIEC TABLICY!!!\n\n");
    }
}
}
srednia=kolizja/zakres;
printf("Srednia prob wstawien: %i\n\n",srednia);
printf("\n******KOLIZACJA WYSTAPILA %i RAZY*****\n", kolizja);
}

void szukaj(char nazwiskoL[20],NAZWISKA zHaszujacej[]) {
    int hasz=0;
    int dlugosc=strlen(nazwiskoL);
    int i;
    int litera;
    int kod;
            for(i=0;i<dlugosc;i++){
            litera=nazwiskoL[i];
            kod=(litera*111)%7;
            hasz+=kod;
}
           while(strcmp(nazwiskoL,zHaszujacej[hasz].nazwisko)==0){
                printf("\n*\nNastapila kolizja, filtruje numer indeksu\n*\n");
                hasz++;
            printf("\nPodane przez Ciebie nazwisko znajduje sie w tablicy pod indeksem %i\n",hasz);
           }
                printf("\nPodane przez Ciebie nazwisko znajduje sie w tablicy pod indeksem %i\n",hasz);

}


int main() {
    printf("\n******************\n");
    printf("**HASZOWANIE 0.97*\n");
    printf("******************\n");
    int i;
    int rozmiar,rozmiar2;
    int zakres;
    char nazwiskoL[20];
    printf("Podaj rozmiar tablicy: ");
    scanf("%i", &rozmiar);
    printf("\n\nPodaj zakres do wypelnienia: ");
    scanf("%i", &zakres);
    printf("\n\nPodaj rozmiar tablicy haszujacej(wiekszy lub rowny 1000): ");
    scanf("%i",&rozmiar2);
    NAZWISKA wyjscie[rozmiar2];
    NAZWISKA* spis=wczytaj(zakres,rozmiar);
    printf("Tablica zawiera:\n\n");
    for(i=0;i<rozmiar;i++){
    printf("%i %s\n", spis[i].liczba,spis[i].nazwisko);
    }
    zerujTablice(wyjscie,rozmiar2);
    koduj(spis,zakres,wyjscie,rozmiar2);
    printf("\n\nTablica Haszujaca:\n\n");
    for(i=0;i<rozmiar2;i++){//wypisanie tablicy wyjsciowej
    printf("%i %i %s\n",i, wyjscie[i].liczba,wyjscie[i].nazwisko);
    }
    printf("\nPodaj nazwisko:\n");
        scanf("%s",&nazwiskoL);
    szukaj(nazwiskoL,wyjscie);


}
   // dodaj();
  //  printf("\n nazwisko=%s\n",nazwisko);
  //  printf("\nLiczba z nazwisko to %i",hasz);
   // printf("\nPierwszy element tablicy to %i, a drugi to %i",tablicaDoNazwisk[0]);
