#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "nodo.h"
#include "PDB.h"

// {1,2,3}, {5,6,7}, {9,10,11}

void inicializarPDB(unsigned char *visitados) {
    memset(visitados, 255, 1320);
}

int indicePerfecto(int a, int b, int c, int *state) {
    int i = 0, id = 0, p1 = 0, p2 = 0, p3 = 0;
    while(i < 12){
        if(state[i] == a)
            p1 = i;
        if(state[i] == b)
            p2 = i;
        if(state[i] == c)
            p3 = i;
        i++;
    }
    id += p1 * (11 * 10);       // Hay 11*10 combinaciones por cada posición de p1
    int p2_ajustada = p2;
    if(p2 > p1)                 // Hay que ajustar porque p1 ya ocupa un lugar
        p2_ajustada--;
    id += p2_ajustada * 10;     // Hay 10 combinaciones por cada posición restante de p2
    int p3_ajustada = p3;
    if(p3 > p1)                 // Hay que ajustar porque p1 y p2 ya ocupan un lugar cada uno
        p3_ajustada--;
    if (p3 > p2)
        p3_ajustada--;
    id += p3_ajustada;
    return id;
}

void caminosBFS(struct nodo *nodoInicial, int *info, unsigned char *visitados) {
	if (nodoInicial == NULL) return;
    visitados[indicePerfecto(info[0], info[1], info[2], nodoInicial->estado)] = nodoInicial->distanciaPadre;
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
            idVecino = indicePerfecto(info[0], info[1], info[2], vecino);
            if(visitados[idVecino] == 255){ // no ha sido visitado
                visitados[idVecino] = primeroCola->distanciaPadre+1;
                agregarNodo(cola, crearNodo(vecino, primeroCola->distanciaPadre + 1));
            }
        }
        primeroCola = primeroCola->sig;
    }
	limpiarListaNodo(cola);
}

void creacionPDB(const char *PDB, unsigned char *visitados, int *info){
    if(access(PDB, F_OK) == -1){		//Si no existe, la creamos
		int ini, med, ult, particion;
		printf("Ingresa 6 números, 3 entre 1 y 12 (fichas), y 3 entre 1 y 12 (posiciones para las fichas):\n");
		particion = scanf("%d %d %d %d %d %d", &info[0], &info[1], &info[2], &ini, &med, &ult);
		if(particion != 6)
			printf("❌ Error: No ingresaste 6 numeros.\n");
		else{
            int state[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            state[ini] = info[0];
            state[med] = info[1];
            state[ult] = info[2];
			FILE *base = fopen(PDB, "w");
			if(base != NULL){
                fprintf(base, "%d %d %d\n", info[0], info[1], info[2]);   // Anoto la particion a seguir
				caminosBFS(crearNodo(state,0),info, visitados);
				for(int i = 0; i < 1320; i++)
					fprintf(base, "%d %d\n", i, visitados[i]);
				fclose(base);
				printf("✅ Se creo exitosamente la PDB '%s'.\n", PDB);
			}
			else
				printf("❌ Error: No se pudo crear el archivo.\n");
		}
	}else{
        int indice, valor;
        FILE *base = fopen(PDB, "r");
        fscanf(base, "%d %d %d", &info[0], &info[1], &info[2]);
        while(fscanf(base, "%d %d", &indice, &valor) == 2){
            visitados[indice] = valor;
        }
        fclose(base);
        printf("✅ Se cargo exitosamente la PDB '%s'.\n", PDB);
    }
}