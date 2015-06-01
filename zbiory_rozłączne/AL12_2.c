#include <stdio.h>
#include <stdlib.h>



/*DEKLARACJA WSKAZNIKA*/
typedef struct wezel *WskNaWezel; //mozna umiescic zamiast tutaj w strukturze ale ten sposob ladniej wyglada i jest porêczniej

/*DEKLARACJA STRUKTURY WEZLA*/
typedef struct wezel{
    int key;
    WskNaWezel parent;
    int rank;
}TWEZEL;


/*FUNKCJA TWORZACA NOWY WEZEL*/
WskNaWezel MAKESET(int KLUCZ){
WskNaWezel NEW=(WskNaWezel)malloc(sizeof(TWEZEL));
	NEW->parent=NEW;
    NEW->key=KLUCZ;
	NEW->rank = 0;
	return NEW;
}


/*FUNKCJA SZUKAJACA RODZICA DANEGO WEZLA*/
WskNaWezel FINDSET(WskNaWezel x){
	if(x != x->parent)
		x->parent = FINDSET(x->parent);
	return x->parent;
}


int UNION(WskNaWezel x, WskNaWezel y){
    if(x->rank > y->rank){
        y->parent = x;
    } else {
        x->parent = y;
        if(x->rank == y->rank){
            y->rank++;
        }
    }
    return 0;
}




int main(){


WskNaWezel Z[10];


Z[0] = MAKESET(0);
Z[1] = MAKESET(1);
Z[2] = MAKESET(2);
Z[3] = MAKESET(3);
Z[4] = MAKESET(7);
printf("[0]key: %i ", Z[0]->key);
printf("[0]rank: %i \n", Z[0]->rank);
printf("[1]key: %i ", Z[1]->key);
printf("[1]rank: %i \n", Z[1]->rank);
UNION(FINDSET(Z[0]),FINDSET(Z[1]));
printf("[0]key: %i ", Z[0]->key);
printf("[0]rank: %i \n", Z[0]->rank);
printf("[1]key: %i ", Z[1]->key);
printf("[1]rank: %i \n", Z[1]->rank);
printf("[0]key->parent: %i ", Z[0]->parent->key);
printf("[0]rank->parent: %i \n", Z[0]->parent->rank);





return 0;
}
