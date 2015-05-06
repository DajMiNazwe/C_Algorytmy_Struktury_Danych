#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//MARCIN HALLMAN 224705

int main(){
//BUDOWA STRUKTURY I WSZYSTKIE WYMAGANE FUNKCJE
//struktura zawierajaca wspolrzedne punktu w ukladzie wspolrzednych

typedef struct punkt{
struct punkt *prev;
double wspX;
double wspY;
struct punkt *next;
} ppunkt; //Punkt pozwala nam na stosowanie skroconej nazwy zamiast struct punkt, staje sie aliasem pelnej nazwy

//Deklarowanie pustego ukladu, ktory bedzie zawierac punkty
ppunkt *uklad=NULL;
//Rezerwowanie pamieci dla nowego punktu
ppunkt *nowy=malloc(sizeof(ppunkt));

//FUNKCJA WSTAWIAJACA NOWY PUNKT
ppunkt WSTAW(ppunkt *uklad,double x,double y){
//Rezerwowanie pamieci dla tymczasowej zmiennej
ppunkt *tmp=malloc(sizeof(ppunkt));
//Rezerwowanie pamieci dla nowego punktu, ktory ma byc dodany
ppunkt *kolejny=malloc(sizeof(ppunkt));
//Przypisanie do zmiennej wspX nowego unktu, wartosci podanej w wywolaniu funkcji
kolejny->wspX=x;
//Przypisanie do zmiennej wspY nowego unktu, wartosci podanej w wywolaniu funkcji
kolejny->wspY=y;
//Wskaznik na poprzedniu punkt KOLEJNEGO PUNKTU ustawiony na NULL
kolejny->prev=NULL;
//Jesli uklad jest pusty to kolejny sie staje nowym ukladem
if(uklad==NULL){
kolejny->next=NULL;
}else{  //jesli nie to przenosimy uklad do zmiennej tymczasowej
tmp=uklad;
kolejny->next=tmp;//Wskaznik na nastepny punkt KOLEJNEGO PUNKTU zawiera teraz uklad
}
uklad=kolejny;//Przypisanie do ukladu, nowego ukladu z dodanym punktem
return *uklad;//Zwrocenie ukladu
}




//FUNKCJA SZUKAJACA PUNKTÓW POSIADAJACYCH PODANA WSPOLRZEDNA
void SZUKAJ_JEDNA(ppunkt *uklad, double wsp){
//deklaracje zmiennych i rezerwacja pamieci
ppunkt *szukany=malloc(sizeof(ppunkt));
ppunkt *ptr=uklad;
printf("POCZATEK LISTY, PRZESZUKIWANIE ROZPOCZETE!\n");
while(ptr!=NULL){ //dopoki element listy nie rowna sie NULL
    if(ptr->wspX==wsp || ptr->wspY==wsp){//sprawdza czy wspolrzedna X lub Y pkt jest rowna podanej wspolrzednej
        szukany=ptr;
        printf("wspX: %lf | wspY: %lf\n", szukany->wspX,szukany->wspY);
    }
    ptr=ptr->next;//pobiera nastepny element listy
}
 printf("KONIEC LISTY, PRZESZUKIWANIE ZAKONCZONE!\n\n");
}

//FUNKCJA SZUKAJACA PUNKTOW POSIADAJACYCH DWIE TAKIE SAME WSPOLRZEDNE JAK TE PODANE W WYWOLANIU
//dziala na bardzo podobnej zasadzie jak poprzednia dlatego brak opisu
void SZUKAJ_DWIE(ppunkt *uklad, double wspxx, double wspyy){
ppunkt *ptr=uklad;
printf("POCZATEK LISTY, PRZESZUKIWANIE ROZPOCZETE!\n");
while (ptr!=NULL){
    if( ptr->wspX==wspxx && ptr->wspY==wspyy ){
        printf("PUNKT O PODANYCH WSPOLRZEDNYCH: wspX %lf | wspY %lf ISTNIEJE\n", ptr->wspX,ptr->wspY);
    }
    ptr=ptr->next;
}
 printf("KONIEC LISTY, PRZESZUKIWANIE ZAKONCZONE!\n\n");
}




//FUNKCJA WYPISUJACA WSZYSTKIE PUNKTY
//funkcja wzorowana na skonstruowanej i omowionej na laboratoriach
void WYPISZ(ppunkt *uklad){
	if(uklad == NULL){
		printf("BLAD, LISTA JEST PUSTA\n");
		exit(-1);
	}else{
		printf("LISTA ZAWIERA ELEMENTY!\n");
}

ppunkt *ptr = uklad;
do{
	printf("wspX: %lf wspY: %lf\n",ptr->wspX,ptr->wspY);
	ptr=ptr->next;
}while(ptr!=NULL);

}

//FUNKCJA KASUJACA UKLAD (jej dzialanie okresle slowami 'jako-tako' poniewaz nie do konca jestem z niej zadowolony no ale chyba ujdzie)
void KKASUJ(ppunkt *uklad){
ppunkt *tmp=malloc(sizeof(ppunkt));
//nie zadziala tutaj zwykle free(uklad), poniewaz musimy usuwac KAZDY element z listy osobno
while(uklad!=NULL){
    tmp=uklad->next;
    free(uklad);//zwalnianie pamieci
    uklad=tmp;

}
WYPISZ(uklad);
}



//FUNKCJA USUWAJACA DANY PUNKT
ppunkt USUN(ppunkt *uklad, double wspxx,double wspyy){
ppunkt *usunac=malloc(sizeof(ppunkt));

usunac->wspX=wspxx;
usunac->wspY=wspyy;


ppunkt *ptr=uklad;
while(ptr!=NULL){//dopoki element listy nie rowna sie NULL
        //teraz nastepuje sprawdzanie warunkow bo usuwajac musimy uwazac zeby nie zepsuc listy
        //nr1 jesli wspolrzedne wywolania sa takie same jak wspolrzedne punktu z listy to->
        if(ptr->wspX==usunac->wspX && ptr->wspY==usunac->wspY ){
        //sprawdz czy element jest pierwszym elementem z listy
        if(ptr->prev!=NULL){//jesli nie to element poprzedni wskakuje na miejsce usuwanego
            ptr->prev->next=ptr->prev;
        }

        else{
            //jesli element jest elementem ostatnim to element drugi staje sie pierwszym na liscie
            ptr->prev=NULL;
            ptr->wspX=ptr->next->wspX;
            ptr->wspY=ptr->next->wspY;
            ptr->next=ptr->next->next;
        }
        //teraz sprawdzamy podobnie jak poprzednio lecz czy element jest elementem ostatnim
        if(ptr->next!=NULL){
            ptr->next->prev=ptr->prev;
        }else{
          ptr->next=NULL;
          ptr->wspX=ptr->prev->wspX;
          ptr->wspY=ptr->prev->wspY;
          ptr->prev=ptr->prev->prev;
        }
    }
ptr=ptr->next;
}
return *uklad;
}



//FUNKCJA SCALAJACA
ppunkt SCALAJ(ppunkt *wejsciowa1, ppunkt *wejsciowa2){

ppunkt *ptr1=wejsciowa1;
ppunkt *ptr2=wejsciowa2;
ppunkt *ptrwyjsc;
ppunkt *tmp=malloc(sizeof(ppunkt));
ppunkt *tmp2=malloc(sizeof(ppunkt));
if(ptr1==NULL){
    ptrwyjsc=ptr2;
}
if(ptr2==NULL){
    ptrwyjsc=ptr1;
}
if(ptr1!=NULL && ptr2!=NULL){
        while(ptr1!=NULL){
        tmp=ptr1->next;
        tmp2=ptrwyjsc;
        ptrwyjsc->prev=NULL;
        ptrwyjsc->wspX=ptr1->wspX;
        ptrwyjsc->wspY=ptr1->wspY;
        ptrwyjsc->next=tmp2;
        ptr1=tmp;
}
}
return *ptrwyjsc;
}

//DODAWANIE PUNKTU ZWYKLA METODA A NIE PRZEZ FUNKCJE (tak for fun)
nowy->wspX=5.4;
nowy->wspY=4.2;
nowy->prev=NULL;
nowy->next=NULL;
uklad=nowy;

//DODAWANIE KILKU PUNKTÓW DO PIERWSZEJ LISTY uklad
ppunkt *tmp=malloc(sizeof(ppunkt));
*tmp=WSTAW(uklad,1.2,6.9);
uklad=tmp;

ppunkt *tmp2=malloc(sizeof(ppunkt));
*tmp2=WSTAW(uklad,7.7,3.1);
uklad=tmp2;

ppunkt *tmp3=malloc(sizeof(ppunkt));
*tmp3=WSTAW(uklad,3.4,5.7);
uklad=tmp3;

ppunkt *tmp4=malloc(sizeof(ppunkt));
*tmp4=WSTAW(uklad,4.9,1.1);
uklad=tmp4;


//WYPISANIE CALEGO UKLADU
WYPISZ(uklad);


//DODAWANIE PUNKTOW DO DRUGIEJ LISTY
ppunkt *uklad2=NULL;

ppunkt *tmp11=malloc(sizeof(ppunkt));
*tmp11=WSTAW(uklad2,3.3,4.4);
uklad2=tmp11;

ppunkt *tmp22=malloc(sizeof(ppunkt));
*tmp22=WSTAW(uklad2,1.2,6.7);
uklad2=tmp22;

ppunkt *tmp33=malloc(sizeof(ppunkt));
*tmp33=WSTAW(uklad2,4.8,5.1);
uklad2=tmp33;

//printf("x:%lf y:%lf\n",uklad->next->wspX,uklad->next->wspY);
//printf("x:%lf y:%lf\n",uklad->wspX,uklad->wspY);
printf("\n\n");
printf("******PREZENTACJA FUNKCJI SZUKAJ_JEDNA******\n\n");
printf("SZUKANIE PUNKTU ZAWIERAJACEGO WSPOLRZEDNA 6.0\n\n");
SZUKAJ_JEDNA(uklad,6.0);
printf("SZUKANIE PUNKTU ZAWIERAJACEGO WSPOLRZEDNA 3.4\n\n");
SZUKAJ_JEDNA(uklad,3.4);

printf("\n\n");

printf("******PREZENTACJA FUNKCJI SZUKAJ_DWIE******\n\n");
printf("SZUKANIE PUNKTU ZAWIERAJACEGO WSPOLRZEDNE 3.4 oraz 5.7\n\n");
SZUKAJ_DWIE(uklad,3.4,5.7);
printf("SZUKANIE PUNKTU ZAWIERAJACEGO WSPOLRZEDNE 1.4 oraz 4.2\n\n");
SZUKAJ_DWIE(uklad,1.4,4.2);

//Usuwanie punktu 4.9,1.1
printf("\n\n");
printf("******PREZENTACJA FUNKCJI USUN******\n\n");
printf("USUWANIE PUNKTU O WSPOLRZEDNYCH: 4.9, 1.1\n\n");

ppunkt *tmp5=malloc(sizeof(ppunkt));
*tmp5=USUN(uklad,4.9,1.1);
uklad=tmp5;

WYPISZ(uklad);

printf("\n\n");
printf("WYPISANIE DRUGIEJ LISTY!!\n\n");
WYPISZ(uklad2);
printf("\n\n");

ppunkt *uklad3=NULL;
ppunkt *uklad4=NULL;
ppunkt *pomoc=malloc(sizeof(ppunkt));

/**pomoc=SCALAJ(uklad,uklad2);
uklad4=pomoc;*/

//
printf("*******PREZENTACJA FUNKCJI KASUJ!!!*******\n\n");
KKASUJ(uklad);



return 0;
}
