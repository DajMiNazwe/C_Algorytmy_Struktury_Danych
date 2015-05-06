#include <stdio.h>
#include <string.h>
#include <stdlib.h>







int main(){

 typedef struct Karton{
	 char prezent[20];
	 struct Karton *prev ;
	 struct Karton *next ;
 }	Pudelko;



 Pudelko dodaj(Pudelko *worek, char nazwa[]){
	 Pudelko *pud1 = malloc(sizeof(Pudelko));
	 strcpy(pud1->prezent, "nazwa");
	 pud1->prev = NULL;
	 pud1->next = worek;
	 worek->prev = pud1;
	 worek=pud1;
	 return *worek;

 }



 void dodajmilion(Pudelko *worek){
	 int i=0;
	 for(i=0;i<100;i++){
	 *worek=dodaj(worek,"zegarek");
 }
 }


	void sprawdzListe(Pudelko *worek){
	if(worek == NULL){
		printf("BLAD\n");
	}else{
		printf("Dobrze\n");
}

Pudelko *ptr = worek;
while(ptr!=NULL){
	printf("Element: %s\n", ptr->prezent);
	ptr=ptr->next;
}
}


	Pudelko *worek = NULL;

	Pudelko *pud1 = malloc(sizeof(Pudelko));


	strcpy(pud1->prezent,"rower");
	pud1->next = NULL;
	pud1->prev = NULL;

	worek = pud1;

	*worek=dodaj(worek,"zegarek");
	//dodajmilion(worek);
	sprawdzListe(worek);
	return 0;
}
