#include <stdio.h>



int main(){
	//STRUKTURA LISTY
	typedef struct lista{
		int x;
		struct lista *next;
	} Slista;

	void *dodaj(Slista *lista, int element){
	Slista *nowy5=malloc(sizeof(Slista));
	nowy5->x= element;
	nowy5->next= lista;
	return lista;
	}


	void sprawdzListe(Slista *lista){
	if(lista == NULL){
		printf("BLAD\n");
	}else{
		printf("Dobrze\n");
}

Slista *ptr = lista;
while(ptr!=NULL){
	printf("Element: %d\n", ptr->x);
	ptr=ptr->next;
}
}

Slista *lista=NULL;
Slista *nowy=malloc(sizeof(Slista));

nowy->x = 5;
nowy->next = NULL;

lista = nowy;

Slista *nowa2=malloc(sizeof(Slista));
nowa2->x=8;
nowa2->next=lista;

lista = nowa2;

Slista *nowy3=malloc(sizeof(Slista));
nowy3->x=4;
nowy3->next=lista;


lista = nowy3;



sprawdzListe(lista);

lista=dodaj(lista,7);

sprawdzListe(lista);

int y = lista->x;

printf("%i", y);

	return 0;
}
