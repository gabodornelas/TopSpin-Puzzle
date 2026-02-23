#ifndef IDA_H
#define IDA_H

struct solYlim {
	struct nodo *nodo;
	int limite;
	long long edoEvaluados;
	long long edoExplorados;
};

/**
 * @brief                   Crea la estructura para recibir el nodo y el limite de cada iteracion del DFS
 * 
 * @param nodo              El nodo respuesta de la iteracion
 * @param limite            El limite de profundidad de DFS en esa iteracion
 * @return struct solYlim*  La estructura creada
 */
struct solYlim *crearSolYlim(struct nodo *nodo, int limite);

/**
 * @brief                   Calcula el minimo entre v1 y v2
 * 
 * @param v1                El primer numero
 * @param v2                El segundo numero
 * @return int              El minimo
 */
int min(int v1, int v2);

/**
 * @brief                    Verifica si un estado es el estado meta
 * 
 * @param state              El estado a comparar con [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
 * @return int               1 Si es el estado meta, 0 en caso contrario.
 */
int esMeta(int *state);

/**
 * @brief                    Agrega a una lista los 3 vecinos del nodo actual
 * 
 * @param vecinos            La lista de los vecinos
 * @param vecino             El estado rotado o girado para los vecinos
 * @param nodoActual         El nodo actual
 */
void crearVecinos(struct head *vecinos, int *vecino, struct nodo *nodoActual);

/**
 * @brief                     Busqueda DFS limitada por un cierto numero de profundidad
 * 
 * @param nodoActual          El nodo en el que nos encontramos en la busqueda
 * @param limite              El limite de profundidad
 * @param resultadoDFS        Estructura que contiene el nodo actual (si existe), y el limite
 * @param visitados1          Nuestra primera PDB
 * @param info1               La particion que sigue nuestra primera PDB
 * @param visitados2          Nuestra segunda PDB
 * @param info2               La particion que sigue nuestra segunda PDB
 * @param visitados3          Nuestra tercera PDB
 * @param info3               La particion que sigue nuestra tercera PDB
 */
void DFS(struct nodo *nodoActual, int limite, struct solYlim *resultadoDFS, unsigned char *visitados1, int *info1, unsigned char *visitados2, int *info2, unsigned char *visitados3, int *info3);

/**
 * @brief                       Calculo para decidir cual PDB tiene la cantidad de movimientos mas alta para un estado determinado
 * 
 * @param visita1               Cantidad de movimientos necesarios para llegar al estado meta registrada en la PDB1
 * @param visita2               Cantidad de movimientos necesarios para llegar al estado meta registrada en la PDB2
 * @param visita3               Cantidad de movimientos necesarios para llegar al estado meta registrada en la PDB3
 * @return int                  El valor maximo entre las 3
 */
int heuristica(int visita1, int visita2, int visita3);

/**
 * @brief                       Funcion IDA* que llama a la DFS para cada nuevo limite de profuncidad requerido
 * 
 * @param estadoInicial         El estado inicial 'desordenado' del rompecabezas
 * @param visitados1            Nuestra primera PDB
 * @param info1                 La particion que sigue nuestra primera PDB
 * @param visitados2            Nuestra segunda PDB
 * @param info2                 La particion que sigue nuestra segunda PDB
 * @param visitados3            Nuestra tercera PDB
 * @param info3                 La particion que sigue nuestra tercera PDB
 * @return struct solYlim*      la estructura con l nodo meta con los apuntadores en el camino solucion, la distancia del camino y el numero de estados generados
 */
struct solYlim *IDA(int *estadoInicial, unsigned char *visitados1, int *info1, unsigned char *visitados2, int *info2, unsigned char *visitados3, int *info3);

#endif