#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Pomocnicza deklaracja wskaznikow(skraca zapis)*/
typedef struct wezel *WskNaWezel;
typedef struct lista *WskNaListe;


/*DEKLARACJA STRUKTURY WEZLA*/
typedef struct wezel{
    WskNaWezel lewy; //lewy syn
    WskNaWezel prawy;//prawy syn
    WskNaWezel parent;//rodzic
    char znak;//znak
}TWEZEL;


/*DEKLARACJA STRUKTURY LISTY, W KTOREJ ZNAJDUJA SIE WEZLY*/
typedef struct lista{
    WskNaListe prev; //element poprzedni z listy
    WskNaListe next;//element nastepny z listy
    int ile_razy; //ilosc wystapien znaku
    WskNaWezel korzen;//struktura wezla
}TLISTA;



int main(){


return 0;
}
