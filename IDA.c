#include <stdio.h>
#include <stdlib.h>

#include "nodo.h"
#include "PDB.h"
#include "IDA.h"

#define INF 50 // valor infinito en este contexto

struct solYlim *crearSolYlim(struct nodo *nodo, int limite){
	struct solYlim *newsolYlim = (struct solYlim *)malloc(sizeof(struct solYlim));
    newsolYlim->nodo = nodo;
    newsolYlim->limite = limite;
    newsolYlim->edoEvaluados = 0;
    newsolYlim->edoExplorados = 0;
	return newsolYlim;
}

int min(int v1, int v2){
    if(v1 < v2)
        return v1;
    else
        return v2;
}

int esMeta(int *state){
    for(int i = 0; i < 12; i++)
        if(state[i] != i+1)
            return 0;
    return 1;
}

void crearVecinos(struct head *vecinos, int *vecino, struct nodo *nodoActual){
    // izq
    vecino[11] = nodoActual->estado[0];
    for (int i = 1; i < 12; i++)
        vecino[i-1] = nodoActual->estado[i];
    agregarNodo(vecinos, crearNodo(vecino,nodoActual->distanciaPadre+1));
    // der
    vecino[0] = nodoActual->estado[11];
    for (int i = 0; i < 11; i++)
        vecino[i+1] = nodoActual->estado[i];
    agregarNodo(vecinos, crearNodo(vecino,nodoActual->distanciaPadre+1));
    // girar
    for (int i = 0; i < 12; i++) {
        if(i < 4)
            vecino[3-i] = nodoActual->estado[i]; 
        else
            vecino[i] = nodoActual->estado[i];
    }
    agregarNodo(vecinos, crearNodo(vecino,nodoActual->distanciaPadre+1));
}

void DFS(struct nodo *nodoActual, int limite, struct solYlim *resultadoDFS, unsigned char *visitados1, int *info1, unsigned char *visitados2, int *info2){
    resultadoDFS->edoExplorados++;
    int minCostoSig = nodoActual->distanciaPadre +
                    heuristica( visitados1[indicePerfecto(info1[0],info1[1],info1[2],info1[3],info1[4],info1[5],info1[6],info1[7],nodoActual->estado)],
                                visitados2[indicePerfecto(info2[0],info2[1],info2[2],info2[3],info2[4],info2[5],info2[6],info2[7],nodoActual->estado)]  );
    if(minCostoSig > limite){
        resultadoDFS->nodo = NULL;
        resultadoDFS->limite = minCostoSig;
        return;
    }
    if(esMeta(nodoActual->estado)){
        resultadoDFS->nodo = nodoActual;
        resultadoDFS->limite = limite;
        return;
    }
    int limCostoSig = INF;
    // Vecinos
    int vecino[12];
    struct head *vecinos = crearLista();
    struct nodo *amistosoVecino;
    crearVecinos(vecinos, vecino, nodoActual);
    amistosoVecino = vecinos->primero;
    // Bucle de vecinos
    while(amistosoVecino != NULL){
        amistosoVecino->ant = nodoActual;
        resultadoDFS->edoEvaluados++;
        DFS(amistosoVecino, limite, resultadoDFS, visitados1, info1, visitados2, info2);
        if(resultadoDFS->nodo != NULL)
            return;
        limCostoSig = min(limCostoSig, resultadoDFS->limite);
        amistosoVecino = amistosoVecino->sig;
    }
    limpiarListaNodo(vecinos);
    resultadoDFS->nodo = NULL;
    resultadoDFS->limite = limCostoSig;
}

int heuristica(int visita1, int visita2){
    if(visita1 >= visita2)
        return visita1;
    else
        return visita2;
    return 0;// esto nunca deberia pasar
}

// Función principal de IDA*
struct solYlim *IDA(int *estadoInicial, unsigned char *visitados1, int *info1, unsigned char *visitados2, int *info2){
    struct nodo *nodoInicial = crearNodo(estadoInicial,0);
    int limite = heuristica(    visitados1[indicePerfecto(info1[0],info1[1],info1[2],info1[3],info1[4],info1[5],info1[6],info1[7],estadoInicial)],
                                visitados2[indicePerfecto(info2[0],info2[1],info2[2],info2[3],info2[4],info2[5],info2[6],info2[7],estadoInicial)]   );
    struct solYlim *resultadoDFS = crearSolYlim(nodoInicial, limite);
    while(limite < INF){
        DFS(nodoInicial, limite, resultadoDFS, visitados1, info1, visitados2, info2);
        limite = resultadoDFS->limite;
        if(resultadoDFS->nodo != NULL)
            return resultadoDFS;
    }
    return NULL;
}