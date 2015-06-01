while(wyjscie[indeks].liczba!=0 && indeks<zakres2){
    indeks++;
    kolizja++;
    printf("KONTROLA");
}
    if(indeks==zakres2){
        indeks=0;
        while(wyjscie[indeks].liczba!=0 && indeks<poczatek){
                 printf("KONTROLA2");
            indeks++;
            kolizja++;
        }
    }
        if(indeks==poczatek){
             printf("KONTROLA3");
            printf("\n\nTablica haszujaca jest pelna!!\n\n");
            srednia=kolizja/zakres;
            printf("Srednia prob wstawien: %i\n\n",srednia);
        }
