#ifndef NODO_H
#define NODO_H

struct nodo {
	int estado[12];
    struct zona *izq;
	struct zona *der;
	struct zona *rotar;
};

struct elemListaNodo {
	struct nodo *nodo;
	struct elemListaNodo *sig;
	struct elemListaNodo *ant;
};

struct headListaNodo {
	struct elemListaNodo *primero;
};

/**
 * @brief 					inicializa un nodo con su estado
 * 
 * @param state 			estado del nodo
 * @return struct nodo* 	el nodo inicializado
 */
struct nodo *crearNodo(int state[12]);

/**
 * @brief 							Crea un elemento para una lista doblemente enlazada y circular de tipo nodo
 * 
 * @param nodo 						El nodo correspondiente a este elemento de la lista
 * @return struct elemListaNodo* 	El elemento de lista creado
 */
struct elemListaNodo *crearElemListaNodo(struct nodo *nodo);

/**
 * @brief 							Crea una lista enlazada de elementos de nodo.
 * 
 * @return struct headListaNodo* 	La cabeza de la lista creada
 */
struct headListaNodo *crearLista();

/**
 * @brief 			Agrega un elemento a la lista de nodos.
 * 
 * @param head 		Cabeza de la lista
 * @param nuevo 	Elemento a agregar en la lista
 */
void agregarNodo(struct headListaNodo *head, struct elemListaNodo *nuevo);

/**
 * @brief 			Limpia la lista y sus elementos
 * 
 * @param head 		La cabeza de la lista a limpiar
 */
void limpiarListaNodo(struct headListaNodo *head);

#endif