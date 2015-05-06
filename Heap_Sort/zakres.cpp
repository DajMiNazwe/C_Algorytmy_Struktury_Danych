#include <stdio.h>
#include <stdlib.h>

/*MARCIN HALLMAN 224705*/

/*OTWORZENIE PLIKU*/
void otworzPlik(){
    char c;
    FILE * plik;

     plik=fopen("liczby.txt","r");
      if(plik==NULL){
        fclose(plik);
        printf("->Brak bazy liczb do posortowania\n");
      }
      else{
        printf("->Wykryto baze liczb, nastapilo jej wczytanie\n");
        fclose(plik);
    }
      }

/*ZLICZENIE ILOSCI WIERSZY*/
int liczWiersze(){
        char znak;
        int a=0;
        FILE * plik;
        plik=fopen("liczby.txt","r");
         if(plik == NULL){
                printf("BLAD!\n");
         }
         else{
          while( (znak=getc(plik))!= EOF){
                if(znak == '\n'){
                        ++a;
                }
          }
          fclose(plik);
}
    a=a+1;
        printf("->Plik posiada %i wierszy", a);
        return a;
}



/*FUNKCJA REZERWUJACA PAMIEC DLA TABLICY I ZWRACAJACA JA, Z WCZYTANYMI Z PLIKU LICZBAMI*/
int* wpisywanie( int rozmiar ){
     int i;
     int* tab = ((int*) malloc(sizeof(*tab) * rozmiar));

     FILE *plik;
     plik=fopen("liczby.txt", "r");
     if(plik == NULL){
              printf("nie moge otworzyc pliku\n");
              }
     for(i=0;i<rozmiar && !feof(plik);i++){

                      fscanf(plik, "%i", &tab[i]);

                      }
     fclose(plik);
     return tab ;
}


/*FUNKCJA ZAMIENIAJACA MIEJSCAMI DWIE KOMORKI*/
void SWAP(int tab[], int a, int b){
        int c;
        c=tab[a];
        tab[a]=tab[b];
        tab[b]=c;
}

/*FUNKCJA NAPRAWIAJACA*/
void napraw (int tab[], int n , int k){
        int max = k;
        int lewy = k * 2+1;
        int prawy = k * 2+2;

        if(lewy<n){
                if(tab[max]<tab[lewy]){
                        max = lewy;
                }
        }
        if(prawy<n && tab[prawy]>tab[max]){
                max = prawy;
        }
        if(max != k){
                SWAP(tab,k,max);
                napraw(tab,n,max);
        }
}

/*FUNKCJA SORTUJACA*/
void sortujKopiec(int tab[],int n){
    int i;
    for(i=n-1;i>=0;i--){
        SWAP(tab,0,i);
        napraw(tab,i,0);
    }
}

/*FUNKCJA BUDUJACA KOPIEC*/
void budujKopiec(int tab[], int n){
    int i;
        for(i=(n/2);i>=0;i--)
        napraw(tab,n,i);
}

/*FUNKCJA WPISUJACA ELEMENTY DO PLIKU WYJSCIOWEGO*/
void wypisz(int tab[], int ograniczenie){
        FILE * plik;
        plik=fopen("liczbyposortowane.txt","w");
    int i=0;
    for(i=0;i<ograniczenie;i++){
        fprintf(plik,"%i\n",tab[i]);
    }
        fclose(plik);
}

int main (){

           /*OTWORZENIE PLIKU*/
        otworzPlik();

                /*DEKLARACJA ZMIENNEJ DLA ILOSCI WIERSZY*/
        int iloscWierszy=liczWiersze();
        int odkad, dokad;
        int nowyrozmiar=0;

       /*UTWORZENIE TABLICY I PRZYPISANIE DO NIEJ TABLICY Z LICZBAMI POBIERANYMI PRZEZ FUNKCJE*/
        int* tab1=wpisywanie(iloscWierszy);
        printf("\n");

        /*WYPISANIE WPROWADZONYCH LICZB*/
        int p=0;
        printf("->Wprowadzone liczby:\n");
        for(p=0;p<iloscWierszy;p++){
        printf(" %i,", tab1[p]);
        }

        /*USTALENIE ZAKRESU SORTOWANIA*/
        printf("\n");
        printf("->Od ktorej pozycji zaczac sortowac 'wlacznie'?: ");
        scanf("%i",&odkad);
        if(odkad>iloscWierszy){
            printf("BLAD, POZYCJA STARTOWA WYKRACZA POZA TABLICE\n\n");
            exit(0);
        }
        printf("\n");
        printf("->Do ktorej pozycji sortowac 'wlacznie'?: ");
        scanf("%i", &dokad);
        if(dokad>iloscWierszy){
            printf("BLAD, POZYCJA KONCOWA WYKRACZA POZA TABLICE\n\n");
            exit(0);
        }
        printf("\n");

        /*PRZYPISANIE ODPOWIEDNICH KOMOREK TABLICY PIERWSZEJ DO NOWEJ OGRANICZONEJ ZAKRESEM*/
        int q=0;
        nowyrozmiar=(dokad-odkad)+1;
        printf("Rozmiar: %i\n", nowyrozmiar);
        int tab2[nowyrozmiar],y=0;
        for(q=(odkad-1);q<dokad;q++){
            tab2[y]=tab1[q];
          //  printf("tab2[%i]=%i \n",y,tab2[y]);
            y++;
        }

        printf("\n");

        /*BUDOWA KOPCA*/
        budujKopiec(tab2,nowyrozmiar);
        /*SORTOWANIE ELEMENTOW*/
        sortujKopiec(tab2,nowyrozmiar);


        /*WPISYWANIE LICZB DO PLIKU WYJSCIOWEGO*/
        wypisz(tab2,nowyrozmiar);

        /*WYPISYWANIE LICZB POSORTOWANYCH*/
        int i=0;
        printf("->Liczby posortowane:\n");
        for(i=0;i<nowyrozmiar;i++){
                printf(" %i,",tab2[i]);
        }

        /*ZWOLNIENIE PAMIECI TABLICY*/
        free(tab1);
return 0;
}
