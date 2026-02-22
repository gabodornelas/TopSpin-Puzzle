#ifndef NODO_H
#define NODO_H

struct nodo {
	int estado[12];
	int distanciaPadre;
	struct nodo *sig;
};

struct head {
	struct nodo *primero;
	struct nodo *ultimo;
};

/**
 * @brief 							Crea un nodo para una lista doblemente enlazada y circular de tipo nodo
 * 
 * @param state 					Estado del nodo
 * @param dist 					Distancia del padre 
 * @return struct elemListaNodo* 	El nodo de lista creado
 */
struct nodo *crearNodo(int state[12], int dist);

/**
 * @brief 					Crea una lista enlazada de elementos de nodo.
 * 
 * @return struct head* 	La cabeza de la lista creada
 */
struct head *crearLista();

/**
 * @brief 			Agrega un elemento a la lista de nodos.
 * 
 * @param head 		Cabeza de la lista
 * @param nuevo 	Elemento a agregar en la lista
 */
void agregarNodo(struct head *head, struct nodo *nuevo);

/**
 * @brief 			Limpia la lista y sus elementos
 * 
 * @param head 		La cabeza de la lista a limpiar
 */
void limpiarListaNodo(struct head *head);

#endif