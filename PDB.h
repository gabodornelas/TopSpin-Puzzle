#ifndef PDB_H
#define PDB_H

/**
 * @brief                   Inicializa el arreglo con puros 255 (valor basicamente INF en este contexto)
 * 
 * @param visitados         El arreglo 'visitados' a inicializar
 */
void inicializarPDB(unsigned char *visitados);

 /**
  * @brief                  Calcula el indice unico para las posiciones de las piezas de la particion
  * 
  * @param a                El valor de la pieza 'a' a buscar
  * @param b                El valor de la pieza 'b' a buscar
  * @param c                El valor de la pieza 'c' a buscar
  * @param d                El valor de la pieza 'd' a buscar
  * @param e                El valor de la pieza 'e' a buscar
  * @param f                El valor de la pieza 'f' a buscar
  * @param g                El valor de la pieza 'g' a buscar
  * @param h                El valor de la pieza 'h' a buscar
  * @param state            El estado en el que hay que buscar las piezas
  * @return int             Indice perfecto calculado
  */
int indicePerfecto(int a, int b, int c, int d, int e, int f, int g, int h, int *state);

/**
 * @brief                   Busqueda en BFS para la ubicacion de los nodos en el arreglo 'visitados'
 * 
 * @param nodoInicial       El nodo con la particion deseada
 * @param info              Arreglo con la informacion de las piezas de la particion
 * @param visitados         El arreglo 'visitados'
 */
void caminosBFS(struct nodo *nodoInicial, int *info, unsigned char *visitados);

/**
 * @brief                   Creacion y escritura del archivo .txt que contendra la PDB o carga del mismo y llenado del arreglo 'visitados'
 * 
 * @param PDB               Nombre del archivo .txt que contendra la PDB
 * @param visitados         El arreglo 'visitados'
 * @param info              Arreglo con la informacion de las piezas de la particion
 */
void creacionPDB(const char *PDB, unsigned char *visitados, int *info);

#endif