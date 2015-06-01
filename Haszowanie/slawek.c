#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nazwiska{
    int liczba;
    char nazwisko[20];
}NAZWISKA;

NAZWISKA tabWyjsciowa[100];

NAZWISKA* wczytywanie(int ilosc, int rozmiar){
	NAZWISKA* tablica=malloc(sizeof(NAZWISKA)*rozmiar);
	int i;
	FILE *plik;
	plik=fopen("nazwiska.txt", "r");
    if(plik == NULL){
              printf("nie moge otworzyc pliku\n");
              }
     for(i=0;i<ilosc;i++){
                      fscanf(plik,"%i %s", &tablica[i].liczba,&tablica[i].nazwisko);
                      }
     fclose(plik);

return tablica;
}

int haszowanie(char napis[]){
	int hasz=0;
	int dlugosc = strlen(napis);
	int i;
	int literka;
	int kod;

	for(i=0;i<dlugosc;i++){
		literka = napis[i];
		kod = ((literka*2)%13)%11;
		hasz += kod;
	}

	return hasz;
}

void wyjscie(NAZWISKA tabWejsciowa[], int zakres){
	int i;
	int indeks;
	int tmp=1;

 	for(i=0;i<zakres;i++){
		indeks=haszowanie(tabWejsciowa[i].nazwisko);
		while(tabWyjsciowa[indeks].liczba!=0 && indeks<zakres){
			indeks++;
		}
		tabWyjsciowa[indeks]=tabWejsciowa[i];
	}
}

void szukanie(int ograniczenie){
	char slowo[20];
	int zliczanie=0;
	int szukanieHasz=0;
	printf("Wpisz szukane nazwisko:\n");
	scanf("%s", &slowo);
	szukanieHasz=haszowanie(slowo);
	printf("Nazwisko powinno byc w indeksie: %i\n", szukanieHasz);
	while(strcmp(tabWyjsciowa[szukanieHasz].nazwisko,slowo)!=0){
		szukanieHasz++;
		zliczanie++;
	}
	printf("Musialo przeskoczyc: %i miejsc.\n", zliczanie);
}

int main(){

	int i;
	int rozmiar;
	int zakres;

	printf("Podaj rozmiar tablicy: ");
	scanf("%i", &rozmiar);
	printf("\nPodaj zakres do wypelnienia: ");
	scanf("%i", &zakres);

	NAZWISKA* spis=wczytywanie(zakres,rozmiar);
	wyjscie(spis,zakres);

	for(i=0;i<100;i++){
    	printf("%i %i %s\n",i, tabWyjsciowa[i].liczba,tabWyjsciowa[i].nazwisko);
	}

	printf("\n\nZLICZANIE PO NAZWISKU\n\n");
	szukanie(rozmiar);

return 0;
}
