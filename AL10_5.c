#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*Pomocnicza deklaracja wskaznikow(skraca zapis)*/
typedef struct wezel *WskNaWezel;
typedef struct lista *WskNaListe;


WskNaListe ELEMENTS;

/*DEKLARACJA STRUKTURY WEZLA*/
typedef struct wezel{
    WskNaWezel left; //lewy syn
    WskNaWezel right;//prawy syn
    WskNaWezel parent;//rodzic
    char znak;//znak
    int ile_razy;//ilosc wystapien znaku
}TWEZEL;


/*DEKLARACJA STRUKTURY LISTY, W KTOREJ ZNAJDUJA SIE WEZLY*/
typedef struct lista{
    WskNaListe prev; //element poprzedni z listy
    WskNaListe next;//element nastepny z listy
    WskNaWezel korzen;//struktura wezla
}TLISTA;


/*DODAWANIE NOWEGO WEZLA*/
WskNaWezel nowyWezel(char klucz){
WskNaWezel nowy=(WskNaWezel)malloc(sizeof(TWEZEL));
nowy->left=NULL;
nowy->right=NULL;
nowy->parent=NULL;
nowy->ile_razy=0;
nowy->znak=klucz;
return nowy;
}


/*INICJALIZACJA LISTY*/
void listaInit(){
ELEMENTS=(WskNaListe)malloc(sizeof(TLISTA));
ELEMENTS->prev=NULL;
ELEMENTS->next=NULL;
ELEMENTS->korzen=NULL;
return ELEMENTS;
}


/*FUNKCJA "ODPORWADZAJACA" WSKAZNIK NA POCZATEK LISTY*/
void znajdzPoczatek(){

ELEMENTS;
while(ELEMENTS->prev!=NULL){
    //printf("%i\n\n",ELEMENTS->korzen->znak);
    ELEMENTS=ELEMENTS->prev;
}
ELEMENTS=ELEMENTS->next;
return ELEMENTS;
}

/*WCZYTYWANIE PLIKU TZN ZNAKOW I ZLICZANIE ICH WYSTAPIEN*/
void wczytajPlik(){
    char c;
    WskNaListe poczatek;
    FILE * plik;

     plik=fopen("tekst.txt","r");
      if(plik==NULL){
        fclose(plik);
        printf("->Brak pliku z tekstem\n");
      }
      else{
        printf("->Wykryto plik z tekstem\n");
        c=getc(plik);
        while(c!=EOF){//pobieranie znaku
        znajdzPoczatek();
        while(ELEMENTS->next!=NULL){//przeszukiwanie listy
           if(ELEMENTS->korzen->znak==c){
               ELEMENTS->korzen->ile_razy++;//zliczanie wystapien
               printf("znak:%c | ilosc wystapien: %i\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
            }
            ELEMENTS=ELEMENTS->next;
        }
           c=getc(plik);//pobieranie nastepnego znaku
        }
        znajdzPoczatek();
        fclose(plik);
    }


}

/*FUNKCJA POMOCNICZA WSTAWIAJACA WEZEL DO LISTY*/
WskNaListe wstawDoListy(char klucz){
WskNaListe tmp=(WskNaListe)malloc(sizeof(TLISTA));

/*sprawdzanie czy lista jest pusta czy nie*/
if(ELEMENTS==NULL){
ELEMENTS->korzen=nowyWezel(klucz);
}else{
tmp->korzen=nowyWezel(klucz);
tmp->prev=ELEMENTS;
ELEMENTS->next=tmp;
ELEMENTS=tmp;
}
return ELEMENTS;
}


/*FUNKCJA UZUPELNIAJACA LISTE WEZLAMI*/
WskNaListe uzupelnijListe(){

WskNaListe temp=(WskNaListe)malloc(sizeof(TLISTA));

int zakres;
char znak;

/*biale znaki*/
wstawDoListy('\t');
wstawDoListy('\n');
wstawDoListy(' ');
/*cyfry*/
for(zakres='0';zakres<='9';zakres++){
    znak=zakres;
    wstawDoListy(znak);
}
/*wielkie litery*/
for(zakres='A';zakres<='Z';zakres++){
    znak=zakres;
    wstawDoListy(znak);
}
/*male litery*/
for(zakres='a';zakres<='z';zakres++){
    znak=zakres;
    wstawDoListy(znak);
}
return ELEMENTS;
}

int main(){


listaInit();
uzupelnijListe();
wczytajPlik();




return 0;
}
