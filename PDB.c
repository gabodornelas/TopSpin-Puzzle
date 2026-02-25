#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodo.h"
#include "PDB.h"

// {1,2,3,4,5,6,7,8}, {5,6,7,8,9,10,11,12}
// 19.958.400
void inicializarPDB(unsigned char *visitados) {
    memset(visitados, 255, 19958400);
}

int indicePerfecto(int a, int b, int c, int d, int e, int f, int g, int h, int *state){
    int valores[8] = {a,b,c,d,e,f,g,h}; // Agrupamos las 8 piezas en un arreglo para poder iterarlas
    // Multiplicadores precalculados para 8 piezas en 12 espacios, calculados como permutaciones de los espacios restantes.
    int multiplicadores[8] = {1663200, 151200, 15120, 1680, 210, 30, 5, 1};
    int pAjustada = 0;
    int p[8] = {0}; 
    int id = 0;
    for(int i = 0; i < 8; i++)         // Encontramos las posiciones de las 8 piezas en los 12 puestos
        for (int j = 0; j < 12; j++)
            if (state[j] == valores[i]) {
                p[i] = j;
                break;                  // Lo encontramos, pasamos a la siguiente pieza
            }
    for(int i = 0; i < 8; i++) {       // Calculo de la pAjustada
        pAjustada = p[i];
        for(int j = 0; j < i; j++)      // Restamos 1 por cada pieza anterior que ya ocupa un índice menor
            if(p[j] < p[i])
                pAjustada--;
        id += pAjustada*multiplicadores[i]; // Sumamos al ID usando el multiplicador correspondiente
    }
    return id;
}

void caminosBFS(struct nodo *nodoInicial, int *info, unsigned char *visitados) {
	if (nodoInicial == NULL) return;
    visitados[indicePerfecto(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], nodoInicial->estado)] = nodoInicial->distanciaPadre;
    int vecino[12];
    int idVecino = 0;
    //arregla este gentio
    struct head *cola = crearLista();
    agregarNodo(cola, nodoInicial);
    struct nodo *primeroCola = cola->primero;;
    while(primeroCola != NULL){ 
        for(int i = 1; i <= 3; i++){
            switch(i){
                case 1: // rotar izq
                    vecino[11] = primeroCola->estado[0];
                    for (int i = 1; i < 12; i++)
                        vecino[i-1] = primeroCola->estado[i];
                    break;
                case 2: // rotar der
                    vecino[0] = primeroCola->estado[11];
                    for (int i = 0; i < 11; i++)
                        vecino[i+1] = primeroCola->estado[i]; 
                    break;
                case 3: // girar
                    for (int i = 0; i < 12; i++) {
                        if(i < 4)
                            vecino[3-i] = primeroCola->estado[i]; 
                        else
                            vecino[i] = primeroCola->estado[i];
                    }
                    break;
            }
            idVecino = indicePerfecto(info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7], vecino);
            if(visitados[idVecino] == 255){ // no ha sido visitado
                visitados[idVecino] = primeroCola->distanciaPadre+1;
                agregarNodo(cola, crearNodo(vecino, primeroCola->distanciaPadre + 1));
            }
        }
        primeroCola = primeroCola->sig;
    }
	limpiarListaNodo(cola);
}


//  Para la creacion de PDBs se restringio que sea de particiones de 8, pero doy libertad a que sea cualquier particion en cualquier posicion
//  depende del caso usarlo para una cosa u otra
void creacionPDB(const char *PDB, unsigned char *visitados, int *info){
    if(access(PDB, F_OK) == -1){		//Si no existe, la creamos
		int uno, dos, tres, cuatro, cinco, seis, siete, ocho, particion;
		printf("Ingresa 16 números, 8 entre 1 y 12 (fichas), y 8 entre 1 y 12 (posiciones para las fichas):\n");
		particion = scanf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &info[0], &info[1], &info[2], &info[3], &info[4], &info[5], &info[6], &info[7], &uno, &dos, &tres, &cuatro, &cinco, &seis, &siete, &ocho);
		if(particion != 16)
			printf("❌ Error: No ingresaste 16 numeros.\n");
		else{
            int state[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            state[uno]   = info[0];   state[dos]  = info[1];   state[tres]  = info[2]; state[cuatro] = info[3];
            state[cinco] = info[4];   state[seis] = info[5];   state[siete] = info[6]; state[ocho]   = info[7];
			FILE *base = fopen(PDB, "w");
			if(base != NULL){
                fprintf(base, "%d %d %d %d %d %d %d %d\n", info[0], info[1], info[2], info[3], info[4], info[5], info[6], info[7]);   // Anoto la particion a seguir
				caminosBFS(crearNodo(state,0),info, visitados);
				for(int i = 0; i < 19958400; i++)
					fprintf(base, "%d %d\n", i, visitados[i]);
				fclose(base);
				printf("✅ Se creo exitosamente la PDB '%s'.\n", PDB);
			}else
				printf("❌ Error: No se pudo crear el archivo.\n");
		}
	}else{                              //Existe, la cargamos
        printf("Cargando '%s'...\n", PDB);
        int indice, valor;
        FILE *base = fopen(PDB, "r");
        fscanf(base, "%d %d %d %d %d %d %d %d", &info[0], &info[1], &info[2], &info[3], &info[4], &info[5], &info[6], &info[7]);
        while(fscanf(base, "%d %d", &indice, &valor) == 2){
            visitados[indice] = valor;
        }
        fclose(base);
        printf("✅ Se cargo exitosamente la PDB '%s'.\n", PDB);
    }
}