#ifndef PDB_H
#define PDB_H

/**
 * @brief                   Arreglo con la cantidad de movimientos desde un determinado estado
 * 
 */
extern unsigned char visitados[1320];

/**
 * @brief                   Inicializa el arreglo con puros 255 ()
 * 
 */
void inicializar_PDB();

/**
 * @brief                   Calcula el indice unico para las posiciones de las piezas de la particion
 * 
 * @param p1                Posicion del primer numero
 * @param p2                Posicion del segundo numero
 * @param p3                Posicion del tercer numero
 * @return int              Indice perfecto calculado
 */
int indicePerfecto(int p1, int p2, int p3);

/**
 * @brief                   Busca la posicion de una pieza en un estado
 * 
 * @param val               El valor de la pieza a buscar
 * @param state             El estado en el que hay que buscar la pieza
 * @return int              El indice de la pieza en el estado
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