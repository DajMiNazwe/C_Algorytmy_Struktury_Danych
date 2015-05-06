#include <stdio.h>


void COUNTINGSORT(int A[], int B[], int k, int l){
int C[k];
int i=0;

for(i=0;i<=k;i++){
    C[i] = 0;
}
int j=0;
for(j=1;j<=l;j++){
    C[A[j]] = C[A[j]] + 1;
}
for(i=1;i<=k;i++){
    C[i] = C[i] + C[i-1];
}
for(j=l;j>=1;j--){
    B[C[A[j]]] = A[j];
    C[A[j]] = C[A[j]]-1;
}

}

int main(){
int rozmiarWejsc;
int rozmiarPomoc=0;

printf("Sortowanie przez zliczanie\n");
//DEKLAROWANIE ILOSCI ZMIENNYCH
printf("Ile liczb chcesz posortowac?");
scanf("%i", &rozmiarWejsc);

//DEKLARACJE TABLIC
int A[rozmiarWejsc];
int B[rozmiarWejsc];
int i=0;

//WPROWADZENIE ELEMENTOW DO TABLICY A
for(i=1;i<=rozmiarWejsc;i++){
    printf("Podaj element %i: \n", i);
    scanf("%i", &A[i]);
    if(A[i]>=rozmiarPomoc){
        rozmiarPomoc=A[i];
    }
}
//WYPISANIE ELEMENTÓW TABLICY A
for(i=1;i<=rozmiarWejsc;i++){
    printf("%i",A[i]);
}

//ROZMIAR TABLICY
int iloscEle=(sizeof(A) / sizeof(A[0]));
printf("%i", iloscEle);

//SORTOWAENI
COUNTINGSORT(A,B,rozmiarPomoc,iloscEle);
printf("\n\n");

//WYPISANIE POSORTOWANEJ TABLICY
for(i=1;i<=rozmiarWejsc;i++){
    printf("%i",B[i]);
}
}



