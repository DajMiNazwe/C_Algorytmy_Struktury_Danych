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
    ELEMENTS=ELEMENTS->prev;
}
printf("%i %i\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
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
        //       printf("znak:%c | ilosc wystapien: %i\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
            }
            ELEMENTS=ELEMENTS->next;
        }
           c=getc(plik);//pobieranie nastepnego znaku
        }
        znajdzPoczatek();
        printf("Poczatek: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
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
ELEMENTS->prev=NULL;
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
ELEMENTS->next=NULL;
return ELEMENTS;
}




WskNaWezel szukajNajmniejszy(){

WskNaWezel pierwszy=(WskNaWezel)malloc(sizeof(TWEZEL));


WskNaListe tmp=(WskNaListe)malloc(sizeof(TLISTA));
WskNaListe pierwszyLista=(WskNaListe)malloc(sizeof(TLISTA));


znajdzPoczatek();
printf("Poczatek: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
tmp=ELEMENTS;
pierwszyLista=tmp;

//printf("Pierwszy najmniejszy: %i | %i\n\n",pierwszyLista->korzen->znak,pierwszyLista->korzen->ile_razy);


tmp=tmp->next;
while(tmp->next!=NULL){
    if(tmp->korzen->ile_razy < pierwszyLista->korzen->ile_razy){
        pierwszyLista=tmp;
      //  printf("Pierwszy najmniejszy: %i | %i\n\n",pierwszyLista->korzen->znak,pierwszyLista->korzen->ile_razy);
    }
    tmp=tmp->next;
}

    if(pierwszyLista->prev==NULL){
        printf("KOLIZJA\n");
        //printf("Pierwszy najmniejszy: %i | %i\n\n",pierwszyLista->korzen->znak,pierwszyLista->korzen->ile_razy);
        //printf("Pierwszy najmniejszy-next: %i | %i\n\n",pierwszyLista->next->korzen->znak,pierwszyLista->next->korzen->ile_razy);
        //printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->next;
       // printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);
        //printf("tmp-next: %i | %i\n\n",tmp->next->korzen->znak,tmp->next->korzen->ile_razy);
        tmp->prev=NULL;
    }
    else if(pierwszyLista->next==NULL){
        printf("KOLIZJA2\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->prev;
        tmp->next=NULL;
    }else{
        printf("KOLIZJA3\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);
        printf("tmp-prev: %i | %i\n\n",tmp->prev->korzen->znak,tmp->prev->korzen->ile_razy);
        printf("tmp-next: %i | %i\n\n",tmp->next->korzen->znak,tmp->next->korzen->ile_razy);
        tmp->prev->next=tmp->next;
    }

    ELEMENTS=tmp;
    znajdzPoczatek();
    printf("Poczatek: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
    printf("Pierwszy: %i | %i\n\n",pierwszy->znak,pierwszy->ile_razy);
return pierwszy;
}




void Huffman(){
//for i = 2 to |C| do
WskNaWezel najwiekszyX=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel najwiekszyY=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel laczony=(WskNaWezel)malloc(sizeof(TWEZEL));
najwiekszyX=szukajNajmniejszy();
printf("najwiekszyX: %i | %i\n",najwiekszyX->znak,najwiekszyX->ile_razy);


najwiekszyY = szukajNajmniejszy();
printf("najwiekszyY: %i | %i\n",najwiekszyY->znak,najwiekszyY->ile_razy);
laczony=nowyWezel('?');
laczony->left= najwiekszyX;
laczony->right= najwiekszyY;
laczony->ile_razy= najwiekszyX->ile_razy + najwiekszyY->ile_razy;
printf("laczony: %i | %i\n",laczony->znak,laczony->ile_razy);
printf("left: %i | %i\n",laczony->left->znak,laczony->left->ile_razy);
printf("right: %i | %i\n",laczony->right->znak,laczony->right->ile_razy);


//Insert(laczony);

}


int main(){


listaInit();
uzupelnijListe();
wczytajPlik();
Huffman();


return 0;
}
