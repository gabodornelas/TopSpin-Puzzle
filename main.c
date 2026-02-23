#include <stdio.h>
#include <stdlib.h>

// Headers de nuestros archivos
#include "nodo.h"
#include "PDB.h"
#include "IDA.h"

void impresion(struct nodo *meta){
	if(meta->ant != NULL)
		impresion(meta->ant);
	for (int i = 0; i < 12; i++) 
		printf("%d ", meta->estado[i]);
	printf("\n");
}

int main(int argc, char* argv[]) {
	if (argc != 14) {
        printf("❌ Error: Debes ingresar exactamente 12 numeros y el nombre del archivo de salida.\n");
        printf("Uso correcto: %s n1 n2 n3 n4 n5 n6 n7 n8 n9 n10 n11 n12 salida.txt\n", argv[0]);
        return 1;
    }
	
	int estadoInicial[12];
	char *salida = argv[13];
	for (int i = 0; i < 12; i++) {
        estadoInicial[i] = atoi(argv[i + 1]); 
    }
	// Comprobación para mostrar lo que se guardó
    printf("Arreglo cargado desde parametros:\n( ");
    for (int i = 0; i < 12; i++) {
        printf("%d ", estadoInicial[i]);
    }
    printf(")\n");
	printf("%s\n",salida);

	// PDBs
	const char *PDB1 = "PDB1.txt", *PDB2 = "PDB2.txt", *PDB3 = "PDB3.txt";

	// Arreglos que contienen las claves para los diferentes estados 
	// Se inicializan para llenarlos mas abajo
	unsigned char visitados1[1320], visitados2[1320], visitados3[1320];
    inicializarPDB(visitados1);
    inicializarPDB(visitados2);
    inicializarPDB(visitados3);

	int info1[3], info2[3], info3[3]; // Para guardar informacion inicial de la particion particion

	// Llenado de PDB
	creacionPDB(PDB1, visitados1, info1);
	creacionPDB(PDB2, visitados2, info2);
	creacionPDB(PDB3, visitados3, info3);

	// Ejecutamos IDA*
	struct nodo *resultado = IDA(estadoInicial, visitados1, info1, visitados2, info2, visitados3, info3);
	
	if(resultado == NULL){
		printf("❌ Error: No alcanzo el resultado.\n");
		return 1;
	}else{
		impresion(resultado);
	}
	//Escribimos en salida estandar la longitud del camino y el numero de estados generados

	//Escribimos en el archivo salida el camino de estados desde el inicial hasta la meta

    return 0;
}