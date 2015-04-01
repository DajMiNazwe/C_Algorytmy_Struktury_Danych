#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//MARCIN HALLMAN
//224705
//KOD HUFFMANA

/*Pomocnicza deklaracja wskaznikow(skraca zapis)*/
typedef struct wezel *WskNaWezel;
typedef struct lista *WskNaListe;
int aa=0;




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
}





/*FUNKCJA "ODPORWADZAJACA" WSKAZNIK NA POCZATEK LISTY*/
void znajdzPoczatek(){

while(ELEMENTS->prev!=NULL){
    ELEMENTS=ELEMENTS->prev;
}
}



/*FUNKCJA "ODPORWADZAJACA" WSKAZNIK NA KONIEC LISTY*/
void znajdzKoniec(){

while(ELEMENTS->next!=NULL){
    ELEMENTS=ELEMENTS->next;
}
}




/*WCZYTYWANIE PLIKU TZN ZNAKOW I ZLICZANIE ICH WYSTAPIEN*/
void wczytajPlik(){
    char c;
    WskNaListe poczatek;
    FILE * plik;

     plik=fopen("tekst.txt","r");
      if(plik==NULL){
        fclose(plik);
        printf("->BRAK PLIKU Z TEKSTEM\n\n");
      }
      else{
        printf("->WYKRYTO PLIK Z TEKSTEM\n\n");
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
        znajdzPoczatek();//wskaznik na poczatek listy
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
printf("LISTA MA : %i ELEMENTOW\n\n",licznik);
ELEMENTS->next=NULL;
return ELEMENTS;
}



/*FUNKCJA SZUKAJACA NAJMNIEJSZYCH ELEMENTOW I LACZACA JE W JEDEN WEZEL(nastepnie dodaje go do listy)*/
WskNaWezel szukajNajmniejszy(){

/*zmienne strukturalne pomocnicze*/
WskNaWezel pierwszy;
WskNaListe tmp;
WskNaListe pierwszyLista;


znajdzPoczatek();//wskaznik na poczatek listy
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
    if(pierwszyLista->prev==NULL){//element jest pierwszy na liscie(od lewej)
        //printf("KOLIZJA\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->next;
        tmp->prev=NULL;
    }else if(pierwszyLista->next==NULL){//element jest pierwszy na liscie(od prawej) | inaczej ujmuj¹c jest elementem ostatnim
        //printf("KOLIZJA2\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp=tmp->prev;
        tmp->next=NULL;
    }else{//element lezy gdzies w srodku listy
        //printf("KOLIZJA3\n");
        pierwszy=pierwszyLista->korzen;
        tmp=pierwszyLista;
        tmp->prev->next=tmp->next;
        tmp->next->prev=tmp->prev;
    }

    ELEMENTS=tmp;
    znajdzPoczatek();//wskaznik na poczatek
return pierwszy;
}



/*FUNKCJA PRZESZUKUJACA DRZEWO 'inorder' I WYPISUJACA KOD DLA POSZCZEGOLNYCH ZNAKOW*/
void Inorder(WskNaWezel wezel, char tablica[], int dlugosc)
{
    int i;
    if(!(wezel->left)){
        if(wezel->znak=='\t'){
            printf("Tabulatory: ");
        }else if(wezel->znak=='\n'){
            printf("Nowe linie: ");
        }else if(wezel->znak==' '){
            printf("Spacje: ");
        }else{
            printf(" %c: ",wezel->znak);
        }
    for(i=0; i<dlugosc; i++){
        printf("%c",tablica[i]);
    }
    printf("\n");
  }
  else
  {
    tablica[dlugosc] = '0'; Inorder(wezel->left,tablica,dlugosc + 1);
    tablica[dlugosc] = '1'; Inorder(wezel->right,tablica,dlugosc + 1);
  }
}





/*SERCE PROGRAMU CZYLI ALGORYTM HUFFMANA*/
void Huffman(){
int i=0;

/*zmienne strukturalne pomocnicze na sam koniec*/
WskNaWezel X=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel Y=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel XY=(WskNaWezel)malloc(sizeof(TWEZEL));
int ile;

/*LACZENIE W PETLI WEZLOW LISCI*/
for(i=0;i<63;i++){
int laczna_ilosc=0;
/*zmienne strukturalne pomocnicze dzialajace w petli*/
WskNaWezel najwiekszyX=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel najwiekszyY=(WskNaWezel)malloc(sizeof(TWEZEL));
WskNaWezel laczony=(WskNaWezel)malloc(sizeof(TWEZEL));
najwiekszyX=szukajNajmniejszy();


najwiekszyY = szukajNajmniejszy();
laczna_ilosc=najwiekszyX->ile_razy + najwiekszyY->ile_razy;
laczony=nowyWezel('?',laczna_ilosc);
laczony->left= najwiekszyX;
laczony->right= najwiekszyY;


/*printf("laczony: %i | %i\n\n",laczony->znak,laczony->ile_razy);
printf("left: %i | %i\n\n",laczony->left->znak,laczony->left->ile_razy);
printf("right: %i | %i\n\n",laczony->right->znak,laczony->right->ile_razy);*/

znajdzPoczatek();
wstawWezelDoListy(laczony);
//printf("ELEMENTS: %i | %i\n\n",ELEMENTS->korzen->znak,ELEMENTS->korzen->ile_razy);
}

/*LACZENIE 2 OSTATNICH ELEMENTOW*/
znajdzPoczatek();
X=ELEMENTS->korzen;
Y=ELEMENTS->next->korzen;
ile=X->ile_razy + Y->ile_razy;
XY=nowyWezel('?',ile);
XY->left=X;
XY->right=Y;
wstawWezelDoListy(XY);
znajdzPoczatek();
ELEMENTS->next=NULL;

/*DRUK KONTROLNY SPRAWDZAJACY CZY NA LISCIE JEST OSTATNI ELEMENT*/
if(ELEMENTS->prev==NULL){
    printf("prev==NULL\n\n");
}
if(ELEMENTS->next==NULL){
    printf("next==NULL\n\n");
}
}

/*MAIN*/
int main(){

char wynikowa[256];
int pozycja=0;

printf("ALGORYTM HUFFMANA\n");
printf("*****************\n\n");
listaInit();//inicjalizacja listy
uzupelnijListe();//uzupelnienie jej wezlami(pustymi)
wczytajPlik();//zliczanie wystapien znakow
znajdzKoniec();//sprawdzanie czy lista jest prawidlowa/szukanie konca
Huffman();
WskNaWezel koniec=ELEMENTS->korzen;
printf("*********************\n");
printf("KODY:\n\n");
Inorder(koniec,wynikowa,pozycja);//wypisanie


return 0;
}
