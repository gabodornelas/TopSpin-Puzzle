#ifndef PDB_H
#define PDB_H

/**
 * @brief           Calcula el indice unico para las posiciones de las piezas de la particion
 * 
 * @param p1        Posicion del primer numero
 * @param p2        Posicion del segundo numero
 * @param p3        Posicion del tercer numero
 * @return int      Indice perfecto calculado
 */
int indicePerfecto(int p1, int p2, int p3);

/**
 * @brief           Distancia manhattan de la posicion de las piezas a su posicion ideal
 * 
 * @param p1        Posicion del primer numero
 * @param pos1      Posicion ideal del primer numero
 * @param p2        Posicion del segundo numero
 * @param pos2      Posicion ideal del segundo numero
 * @param p3        Posicion del tercer numero
 * @param pos3      Posicion ideal del tercer numero
 * @return int      Suma de las distancias
 */
int heuristica(int p1, int pos1, int p2, int pos2, int p3, int pos3);

/**
 * @brief                   Calculo del estado y creacion del nodo rotado a la izquierda
 * 
 * @param state             Estado del nodo base 
 * @param vecino            El nodo base
 * @return struct nodo*     El nodo a la izquierda del base
 */
struct nodo *rotarizq(int *state, struct nodo *vecino);

/**
 * @brief                   Calculo del estado y creacion del nodo rotado a la derecha
 * 
 * @param state             Estado del nodo base 
 * @param vecino            El nodo base
 * @return struct nodo*     El nodo a la derecha del base
 */
struct nodo *rotarder(int *state, struct nodo *vecino);

/**
 * @brief                   Calculo del estado y creacion del nodo girado
 * 
 * @param state             Estado del nodo base 
 * @param vecino            El nodo base
 * @return struct nodo*     El nodo girado con respecto al nodo base
 */
struct nodo *girar(int *state, struct nodo *vecino);

/**
 * @brief               Busca la posicion de una pieza en un estado
 * 
 * @param val           El valor de la pieza a buscar
 * @param state         El estado en el que hay que buscar la pieza
 * @return int          El indice de la pieza en el estado
 */
int findCandidato(int val, int *state);

/**
 * @brief                   Busqueda en BFS para la ubicacion de los nodos en el arreglo 'visitados'
 * 
 * @param nodoInicial       El nodo con la particion deseada
 * @param a                 La pieza 'a'
 * @param b                 La pieza 'b'
 * @param c                 La pieza 'c'
 * @param ini               La posicion ideal de la pieza 'a'
 * @param med               La posicion ideal de la pieza 'b'
 * @param ult               La posicion ideal de la pieza 'c'
 */
void caminosBFS(struct nodo *nodoInicial, int a, int b, int c, int ini, int med, int ult);

#endif