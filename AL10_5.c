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


WskNaWezel nowyWezel(char klucz){
WskNaWezel nowy=(WskNaWezel)malloc(sizeof(TWEZEL));
nowy->left=NULL;
nowy->right=NULL;
nowy->parent=NULL;
nowy->ile_razy=0;
nowy->znak=klucz;
return nowy;
}



void listaInit(){
ELEMENTS=(WskNaListe)malloc(sizeof(TLISTA));
ELEMENTS->prev=NULL;
ELEMENTS->next=NULL;
ELEMENTS->korzen=NULL;
return ELEMENTS;
}


void wczytajPlik(){
char klucz;
FILE *plik;
plik=fopen("tekst.txt","r");
if(plik==NULL){
    printf("NIE UDALO SIE WCZYTAC PLIKU!!\n");
}else{


}


}



WskNaListe uzupelnijListe(){

WskNaListe temp=(WskNaListe)malloc(sizeof(TLISTA));


ELEMENTS->korzen=nowyWezel('\t');
temp=ELEMENTS;
temp->korzen=nowyWezel('\n');
ELEMENTS->




return ELEMENTS;
}

int main(){


listaInit();




return 0;
}
