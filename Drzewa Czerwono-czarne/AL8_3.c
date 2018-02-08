#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED 1
#define BLACK 0


//MARCIN HALLMAN
//numer albumu: 224705

/*DEKLARACJA WSKAZNIKA*/
typedef struct wezel *WskNaWezel; //mozna umiescic zamiast tutaj w strukturze ale ten sposob ladniej wyglada i jest porêczniej

/*DEKLARACJA STRUKTURY WEZLA*/
typedef struct wezel{
    int key;
    WskNaWezel parent;
    WskNaWezel left;
    WskNaWezel right;
    int color;
}TWEZEL;


/*DEKLARACJA WARTOWNIKA, KORZENIA I ZMIENNYCH POMOCNICZYCH*/
WskNaWezel NIL;
WskNaWezel ROOT=0;
int i=0;
int min=0;
int max=0;
int deep_left=0, deep_right=0;

/*INICJALIZER*/
void NilINIt(){

NIL=(WskNaWezel)malloc(sizeof(TWEZEL));
NIL->key=0;
NIL->parent=NULL;
NIL->left=NULL;
NIL->right=NULL;
NIL->color=BLACK;
}

/*FUNKCJA TWORZACA NOWY WEZEL*/
WskNaWezel NowyWezel(int KLUCZ,int KOLOR){

WskNaWezel NEW=(WskNaWezel)malloc(sizeof(TWEZEL));
NEW->key=KLUCZ;
NEW->color=KOLOR;
NEW->left=NIL;
NEW->right=NIL;

return NEW;
}


/*FUNKCJA ROTACJI W LEWO*/
void LEFT_ROTATE(WskNaWezel DoZmiany){

WskNaWezel y;

y=DoZmiany->right;

DoZmiany->right=y->left;

if(y->left!=NIL){
    y->left->parent=DoZmiany;
}

y->parent=DoZmiany->parent;


if(DoZmiany->parent==NIL){
    ROOT=y;

}else if(DoZmiany==DoZmiany->parent->left){
    DoZmiany->parent->left=y;
}else{
    DoZmiany->parent->right=y;
}
y->left=DoZmiany;
DoZmiany->parent=y;

}


/*FUNKCJA ROTACJO W PRAWO*/
void RIGHT_ROTATE(WskNaWezel DoZmiany){

WskNaWezel y;
y=DoZmiany->left;
DoZmiany->left=y->right;

if(y->right!=NIL){
    y->right->parent=DoZmiany;
}
y->parent=DoZmiany->parent;
if(DoZmiany->parent==NIL){
    ROOT=y;
}else if(DoZmiany==DoZmiany->parent->right){
    DoZmiany->parent->right=y;
}else{
    DoZmiany->parent->left=y;
}
y->left=DoZmiany;
DoZmiany->parent=y;

}



/*FUNKCJA NAPRAWIAJACA DRZEWO Z ROZBICIEM NA PRZYPADKI*/
void INSERT_FIX(WskNaWezel nowy){

WskNaWezel y;

while(nowy!=ROOT && nowy->parent->color==RED){
    if(nowy->parent==nowy->parent->parent->left){ //sprawdzanie pierwszego przypadku
        y=nowy->parent->parent->right;
        if(y->color==RED){
            nowy->parent->color=BLACK;
            y->color=BLACK;
            nowy->parent->parent->color=RED;
            nowy=nowy->parent->parent;
        }else{ if(nowy==nowy->parent->right){
            nowy=nowy->parent;
            LEFT_ROTATE(nowy);
        }
        nowy->parent->color=BLACK;
        nowy->parent->parent->color=RED;
        RIGHT_ROTATE(nowy->parent->parent);
        }
    }else{
        y=nowy->parent->parent->left;
        if(y->color==RED){
            nowy->parent->color=BLACK;
            y->color=BLACK;
            nowy->parent->parent->color=RED;
            nowy=nowy->parent->parent;
        }else{ if(nowy==nowy->parent->left){
            nowy=nowy->parent;
           RIGHT_ROTATE(nowy);
        }
        nowy->parent->color=BLACK;
        nowy->parent->parent->color=RED;
       LEFT_ROTATE(nowy->parent->parent);
        }
    }
}

ROOT->color=BLACK;

}

/*FUNKCJA DODAJACA NOWY WEZEL*/
WskNaWezel INSERT(WskNaWezel nowy){

WskNaWezel y;
WskNaWezel x;

y=NIL;
x=ROOT;

while(x!=NIL){
    y=x;
    if(nowy->key < x->key){
        x=x->left;
    }else{
        x=x->right;
    }
}

nowy->parent=y;
if(y==NIL){
    ROOT=nowy;
}else if(nowy->key < y->key){
    y->left=nowy;
}else{
    y->right=nowy;
}
nowy->left=NIL;
nowy->right=NIL;
nowy->color=RED;


INSERT_FIX(nowy);

return ROOT;
}

void DRUKUJ(WskNaWezel root)
{
	if(root != NIL)
	{
		DRUKUJ(root->right);
	printf("%i   -   %i\n", root->key, root->color);
		DRUKUJ(root->left);
	}
}

/*FUNKCJA ZLICZAJ¥CA CZERWONE WÊZ£Y*/
int COUNT_RED(WskNaWezel root)
{
	if(root!=NIL)
	{
	    if(root->color==RED){
			i++;
    		}
		COUNT_RED(root->right);
		COUNT_RED(root->left);
	}
	return i;
}

int max_depth(WskNaWezel root)
{
	if(root!= NULL)
	{
		deep_left = max_depth(root->left);
		deep_right = max_depth(root->right);
		if(deep_left > deep_right)
        {
            max=1+deep_left;
           return max;
        }else{
        max=1+deep_right;
		return max;
        }
	}
}
int min_depth(WskNaWezel root)
{
	if (root != NULL)
	{
		deep_left = min_depth(root->left);
		deep_right = min_depth(root->right);
		if(deep_left < deep_right){
            min=1+deep_left;
			return min;
		}else{
		    min=1+deep_right;
		return min;
	}
	}
}


int main(){

NilINIt();
ROOT=NIL;

WskNaWezel next1=NowyWezel(7,BLACK);
WskNaWezel next2=NowyWezel(9,BLACK);
WskNaWezel next3=NowyWezel(10,BLACK);
WskNaWezel next4=NowyWezel(8,BLACK);
WskNaWezel next5=NowyWezel(5,BLACK);
WskNaWezel next6=NowyWezel(3,BLACK);

INSERT(next1);
INSERT(next2);
INSERT(next3);
INSERT(next4);
INSERT(next5);
INSERT(next6);




printf("                             %i|%i\n",ROOT->key,ROOT->color);
printf("              %i|%i",ROOT->left->key,ROOT->left->color);
printf("                             %i|%i\n",ROOT->right->key,ROOT->right->color);
printf("       %i|%i",ROOT->left->left->key,ROOT->left->left->color);
printf("           %i|%i",ROOT->left->right->key,ROOT->left->right->color);
printf("                                          %i|%i",ROOT->right->left->key,ROOT->right->left->color);
printf("                                             %i|%i\n",ROOT->right->right->key,ROOT->right->right->color);
printf(" %i|%i\n\n",ROOT->left->left->left->key,ROOT->left->left->left->color);


DRUKUJ(ROOT);
printf("----------------------------\n");

	printf("Czerwone wezly: %i \n\n",COUNT_RED(ROOT));

	printf("Maksymalna glebokosc: %i \n\n",max_depth(ROOT));

	printf("Minimalna glebokosc: %i \n\n",min_depth(ROOT));

	printf("\n");
free(ROOT);
return 0;
}
