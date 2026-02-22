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

int indicePerfecto(int p1, int p2, int p3) {
    int id = 0;
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

int findCandidato(int val, int *state){
    int i = 0;
    while(i < 12){
        if( state[i] == val)
            return i;
        i++;
    }
    return 0;
}

void caminosBFS(struct nodo *nodoInicial, int a, int b, int c, int ini, int med, int ult, unsigned char *visitados) {
	if (nodoInicial == NULL) return;
	int p1 = findCandidato(a, nodoInicial->estado);
    int p2 = findCandidato(b, nodoInicial->estado);
    int p3 = findCandidato(c, nodoInicial->estado);
    visitados[indicePerfecto(p1, p2, p3)] = nodoInicial->distanciaPadre;
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
            p1 = findCandidato(a, vecino);
            p2 = findCandidato(b, vecino);
            p3 = findCandidato(c, vecino);
            idVecino = indicePerfecto(p1, p2, p3);
            if(visitados[idVecino] == 255){ // no ha sido visitado
                visitados[idVecino] = primeroCola->distanciaPadre+1;
                agregarNodo(cola, crearNodo(vecino, primeroCola->distanciaPadre + 1));
            }
        }
        primeroCola = primeroCola->sig;
    }
	limpiarListaNodo(cola);
}

void creacionPDB(const char *PDB, unsigned char *visitados){
    if(access(PDB, F_OK) == -1){		//Si no existe, la creamos
		int a, b, c, ini, med, ult, particion;
		printf("Ingresa 6 números: ");
		particion = scanf("%d %d %d %d %d %d", &a, &b, &c, &ini, &med, &ult);
		if(particion != 6)
			printf("❌ Error: No ingresaste 6 numeros.\n");
		else{
            int state[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
            state[ini] = a;
            state[med] = b;
            state[ult] = c;
			FILE *base = fopen(PDB, "w");
			if(base != NULL){
				caminosBFS(crearNodo(state,0),a,b,c,ini,med,ult, visitados);
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
        while(fscanf(base, "%d %d", &indice, &valor) == 2){
            visitados[indice] = valor;
        }
        fclose(base);
        printf("✅ Se cargo exitosamente la PDB '%s'.\n", PDB);
    }
}