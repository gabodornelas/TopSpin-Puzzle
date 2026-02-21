#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "nodo.h"

struct nodo *crearNodo(int state[12]){
    struct nodo *newnodo = (struct nodo *)malloc(sizeof(struct nodo));
    for (int i = 0; i < 12; i++) {
        newnodo->estado[i] = state[i]; 
    }
    newnodo->izq = NULL;
    newnodo->der = NULL;
    newnodo->rotar = NULL;
    return newnodo;
}

struct elemListaNodo *crearElemListaNodo(struct nodo *nodo) {
	if (nodo == NULL){
        printf("❌ Error: Estas intentando crear un elemento con un nodo NULO");
        return NULL;
    }
	struct elemListaNodo *nuevoElemListaNodo = calloc(1, sizeof(struct elemListaNodo));
	nuevoElemListaNodo->nodo = nodo;
	nuevoElemListaNodo->sig = nuevoElemListaNodo;
    nuevoElemListaNodo->ant = nuevoElemListaNodo;
	return nuevoElemListaNodo;
}

struct headListaNodo *crearLista() {
    struct headListaNodo *x = (struct headListaNodo *)malloc(sizeof(struct headListaNodo));
    if(x != NULL)
        x->primero = NULL;
    return x;
}

void agregarNodo(struct headListaNodo *head, struct elemListaNodo *nuevo) {
    if((head == NULL) || (nuevo == NULL)){
        printf("❌ Error: Estas intentando crear una lista con un elemento NULO");
        return;
    }
    if(head->primero == NULL){
        head->primero = nuevo;
    }else{
        head->primero->ant->sig = nuevo;
        nuevo->ant = head->primero->ant;
        head->primero->ant = nuevo;
        nuevo->sig = head->primero;
    }
}

void limpiarListaNodo(struct headListaNodo *head){
	if (head != NULL){
		if (head->primero == NULL)
			free(head);
		else{
			struct elemListaNodo *actual = head->primero;
			struct elemListaNodo *elemAlimpiar;
			while(actual != NULL){
				elemAlimpiar = actual;
				actual = actual->sig;
				free(elemAlimpiar);
			}
			free(head);
		}
	}
}