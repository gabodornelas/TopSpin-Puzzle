#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"

struct nodo *crearNodo(int state[12], int dist) {
	struct nodo *newnodo = (struct nodo *)malloc(sizeof(struct nodo));
    for (int i = 0; i < 12; i++) {
        newnodo->estado[i] = state[i]; 
    }
    newnodo->distanciaPadre = dist;
	newnodo->sig = NULL;
	return newnodo;
}

struct head *crearLista() {
    struct head *x = (struct head *)malloc(sizeof(struct head));
    if(x != NULL){
        x->primero = NULL;
        x->ultimo = NULL;
    }
    return x;
}

void agregarNodo(struct head *head, struct nodo *nuevo) {
    if((head == NULL) || (nuevo == NULL)){
        printf("❌ Error: Estas intentando crear una lista con un elemento NULO");
        return;
    }
    if(head->primero == NULL){
        head->primero = nuevo;
        head->ultimo = nuevo;
    }else{
        head->ultimo->sig = nuevo;
        head->ultimo = nuevo;
    }
}

void limpiarListaNodo(struct head *head){
	if (head != NULL){
		if (head->primero == NULL)
			free(head);
		else{
			struct nodo *actual = head->primero;
			struct nodo *elemAlimpiar;
			while(actual != NULL){
				elemAlimpiar = actual;
				actual = actual->sig;
				free(elemAlimpiar);
			}
			free(head);
		}
	}
}