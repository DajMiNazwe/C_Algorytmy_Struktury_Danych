#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*Pomocnicza deklaracja wskaznikow(skraca zapis)*/
typedef struct wezel *WskNaWezel;
typedef struct lista *WskNaListe;
int a[100];
int pozycja=0;




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
WskNaWezel nowyWezel(char klucz,int ile){
WskNaWezel nowy=(WskNaWezel)malloc(sizeof(TWEZEL));
nowy->left=NULL;
nowy->right=NULL;
nowy->parent=NULL;
nowy->ile_razy=ile;
nowy->znak=klucz;
return nowy;
}




/*INICJALIZACJA LISTY*/
void listaInit(){
ELEMENTS=(WskNaListe)malloc(sizeof(TLISTA));
ELEMENTS->prev=NULL;
ELEMENTS->next=NULL;
ELEMENTS->korzen=NULL;
//return ELEMENTS;
}





/*FUNKCJA "ODPORWADZAJACA" WSKAZNIK NA POCZATEK LISTY*/
void znajdzPoczatek(){

while(ELEMENTS->prev!=NULL){
    ELEMENTS=ELEMENTS->prev;
}
//printf("%i %i\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
//return ELEMENTS;
}



/*FUNKCJA "ODPORWADZAJACA" WSKAZNIK NA KONIEC LISTY*/
void znajdzKoniec(){
printf("SZUKAM\n");

while(ELEMENTS->next!=NULL){
    ELEMENTS=ELEMENTS->next;
}
printf("%i %i\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
//return ELEMENTS;
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
        fclose(plik);
    }

}




/*FUNKCJA POMOCNICZA WSTAWIAJACA WEZEL(jako klucz i ilosc) DO LISTY*/
WskNaListe wstawDoListy(char klucz, int ile){
WskNaListe tmp=(WskNaListe)malloc(sizeof(TLISTA));

/*sprawdzanie czy lista jest pusta czy nie*/
if(ELEMENTS==NULL){
ELEMENTS->korzen=nowyWezel(klucz,ile);
}else{
tmp->korzen=nowyWezel(klucz,ile);
tmp->prev=ELEMENTS;
ELEMENTS->next=tmp;
ELEMENTS=tmp;
ELEMENTS->next=NULL;
}
return ELEMENTS;
}




/*FUNKCJA POMOCNICZA WSTAWIAJACA WEZEL(jako argument) DO LISTY*/
WskNaListe wstawWezelDoListy(WskNaWezel wezel){
WskNaListe tmp=(WskNaListe)malloc(sizeof(TLISTA));

/*sprawdzanie czy lista jest pusta czy nie*/
if(ELEMENTS==NULL){
ELEMENTS->korzen=wezel;
}else{
tmp->korzen=wezel;
tmp->prev=NULL;
tmp->next=ELEMENTS;
ELEMENTS->prev=tmp;
ELEMENTS=tmp;
}
return ELEMENTS;
}





/*FUNKCJA UZUPELNIAJACA LISTE WEZLAMI*/
WskNaListe uzupelnijListe(){

WskNaListe temp=(WskNaListe)malloc(sizeof(TLISTA));
int licznik=0;
int zakres;
char znak;

/*biale znaki*/
wstawDoListy('\t',0);
licznik++;
ELEMENTS->prev=NULL;
wstawDoListy('\n',0);
licznik++;
wstawDoListy(' ',0);
licznik++;
/*cyfry*/
for(zakres='0';zakres<='9';zakres++){
    znak=zakres;
    wstawDoListy(znak,0);
    licznik++;
}
/*wielkie litery*/
for(zakres='A';zakres<='Z';zakres++){
    znak=zakres;
    wstawDoListy(znak,0);
    licznik++;
}
/*male litery*/
for(zakres='a';zakres<='z';zakres++){
    znak=zakres;
    wstawDoListy(znak,0);
    licznik++;
}
printf("LISTA MA TYLE: %i ELEMENTOW\n\n",licznik);
ELEMENTS->next=NULL;
return ELEMENTS;
}




WskNaWezel szukajNajmniejszy(){

WskNaWezel pierwszy/*=(WskNaWezel)malloc(sizeof(TWEZEL))*/;


WskNaListe tmp/*=(WskNaListe)malloc(sizeof(TLISTA))*/;
WskNaListe pierwszyLista/*=(WskNaListe)malloc(sizeof(TLISTA))*/;


znajdzPoczatek();
tmp=ELEMENTS;
pierwszyLista=tmp;

tmp=tmp->next;
while(tmp!=NULL){
    if(tmp->korzen->ile_razy < pierwszyLista->korzen->ile_razy){
        pierwszyLista=tmp;
      //  printf("Pierwszy najmniejszy: %i | %i\n\n",pierwszyLista->korzen->znak,pierwszyLista->korzen->ile_razy);
    }
    tmp=tmp->next;
}
    if(pierwszyLista->prev==NULL){
        printf("KOLIZJA\n");
        /*printf("Pierwszy najmniejszy: %i | %i\n\n",pierwszyLista->korzen->znak,pierwszyLista->korzen->ile_razy);
        printf("Pierwszy najmniejszy-next: %i | %i\n\n",pierwszyLista->next->korzen->znak,pierwszyLista->next->korzen->ile_razy);
        printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);*/
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->next;
       /* printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);
        printf("tmp-next: %i | %i\n\n",tmp->next->korzen->znak,tmp->next->korzen->ile_razy);*/
        tmp->prev=NULL;
    }else if(pierwszyLista->next==NULL){
        printf("KOLIZJA2\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->prev;
        tmp->next=NULL;
    }else{
        printf("KOLIZJA3\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        /*printf("tmp: %i | %i\n\n",tmp->korzen->znak,tmp->korzen->ile_razy);
        printf("tmp-prev: %i | %i\n\n",tmp->prev->korzen->znak,tmp->prev->korzen->ile_razy);
        printf("tmp-next: %i | %i\n\n",tmp->next->korzen->znak,tmp->next->korzen->ile_razy);*/
        tmp->prev->next=tmp->next;
        tmp->next->prev=tmp->prev;
    }

    ELEMENTS=tmp;
    znajdzPoczatek();
   /* printf("Poczatek: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
    printf("Pierwszy: %i | %i\n\n",pierwszy->znak,pierwszy->ile_razy);*/
return pierwszy;
}





void drukujTablice(int tablica[], int pozycja){
    int i;
    for (i=0;i<pozycja;++i){
		printf("%i", tablica[i]);
		printf("\n");
		}
		}


void drukujKod(WskNaListe poczatek, int tablica[], int pozycja)
{
    if (poczatek->korzen->left)
    {
        tablica[pozycja] = 0;
        drukujKod(poczatek->korzen->left, tablica, pozycja + 1);
    }

    if (poczatek->korzen->right)
    {
        tablica[pozycja] = 1;
        drukujKod(poczatek->korzen->right, tablica, pozycja + 1);
    }

    if (poczatek->korzen->left=NULL && poczatek->korzen->right==NULL)
    {
        printf("%c: ", poczatek->korzen->znak);
        drukujTablice(tablica, pozycja);
    }
}







void Huffman(){
int i=0;

WskNaWezel X=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel Y=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel XY=(WskNaWezel)malloc(sizeof(TWEZEL));
int ile;

/*LACZENIE W PETLI WEZLOW LISCI*/
for(i=0;i<63;i++){
int laczna_ilosc=0;
WskNaWezel najwiekszyX=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel najwiekszyY=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel laczony=(WskNaWezel)malloc(sizeof(TWEZEL));
najwiekszyX=szukajNajmniejszy();
printf("najwiekszyX: %i | %i\n",najwiekszyX->znak,najwiekszyX->ile_razy);


najwiekszyY = szukajNajmniejszy();
laczna_ilosc=najwiekszyX->ile_razy + najwiekszyY->ile_razy;
laczony=nowyWezel('?',laczna_ilosc);
laczony->left= najwiekszyX;
laczony->right= najwiekszyY;
printf("laczony: %i | %i\n\n",laczony->znak,laczony->ile_razy);
printf("left: %i | %i\n\n",laczony->left->znak,laczony->left->ile_razy);
printf("right: %i | %i\n\n",laczony->right->znak,laczony->right->ile_razy);

znajdzPoczatek();
wstawWezelDoListy(laczony);
printf("ELEMENTS: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
}

/*LACZENIE 2 OSTATNICH ELEMENTOW*/
znajdzPoczatek();
X=ELEMENTS->korzen;
Y=ELEMENTS->next->korzen;
ile=X->ile_razy + Y->ile_razy;
XY=nowyWezel('?',ile);
wstawWezelDoListy(XY);
znajdzPoczatek();
ELEMENTS->next=NULL;

/*DRUK KONTROLNY SPRAWDZAJACY CZY NA LISCIE JEST OSTATNI ELEMENT*/
printf("ELEMENTS: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
if(ELEMENTS->prev==NULL){
    printf("prev==NULL\n");
}
if(ELEMENTS->next==NULL){
    printf("next==NULL\n");
}
drukujKod(ELEMENTS,a,pozycja);
}


int main(){


listaInit();
uzupelnijListe();
wczytajPlik();
znajdzKoniec();
Huffman();


return 0;
}
