#include <stdio.h>
#include <stdlib.h>
// Headers de nuestros archivos
#include "nodo.h"
#include "PDB.h"

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

	caminosBFS(crearNodo(estadoInicial,0),1,2,3,0,1,2);

    return 0;
}

/*
	int opt;
	int opt_ind = 0;

	// Manejo de flags
	while ((opt = getopt_long(argc, argv, ":d:t:f:psh", long_options, &opt_ind)) != -1) {
		switch (opt) {
			case 'd': 
				free(dir);
				dir = mi_strdup(optarg);
				if (!dir) salirPorErrMem();
				struct stat st = {0};
				if (stat(dir, &st) == -1) {
					if (mkdir(dir, 0700) == -1)
						printf("Error: %s\n", strerror(errno));
				}
				break;
				
			case 't': 
				free(trueTexto);
				trueTexto = mi_strdup(optarg);
				if (!trueTexto) salirPorErrMem();
				break;

			case 'f':
				free(falseTexto);
				falseTexto = mi_strdup(optarg);
				if (!falseTexto) salirPorErrMem();
				break;

			case 'p':
				hayPre = true;
				concatPrefijo = true;
				break;
			
			case 's':
				haySuf = true;
				concatSufijo = true;
				break;

			case 'h':
				mensajeAyuda();
				return 0;

			case ':':
				fprintf(stderr, "❌ No ingresaste los argumentos necesarios para la opción %s\n", argv[optind - 1]);
				return 1;

			case '?':
				if (optopt)
					fprintf(stderr, "❌ Opción inválida: -%c\nUsa la flag --help para más información.\n", optopt);
				else if (argv[optind - 1])
					fprintf(stderr, "❌ Opción inválida: %s\nUsa la flag --help para más información.\n", argv[optind - 1]);
				else
					fprintf(stderr, "❌ Ocurrió un error. Usa la flag --help para más información.\n");
                return 1;
		}
	}

	 Comprobación del nombre de archivo adecuado 
	if (!clave) {
		printf("❌ Necesitas indicar el nombre del archivo .json con la clave dicotómica.\n\n");
		return -1;
	}
	else if (!tieneExtension(clave, ".json")) {
		printf("❌ Necesitas indicar un archivo .json.\n\n");
		return -1;
	}
	else if (!existeArchivo(clave)) {
		printf("❌ La dirección que indicaste es incorrecta, no se encontró el archivo.\n\n");
		return -1;
	}
	
	// Al activar -s se debe desactivar -p, a menos que -p también se active expresamente.
	if (haySuf && !hayPre)
		concatPrefijo = false;

	clock_t inicio = clock();
	
	struct nodo *raiz = leerArchivo(clave);

	if (crearDirectorios(raiz, dir, trueTexto, falseTexto, concatPrefijo, concatSufijo)) {
		printf("✅ Se ha creado el directorio %s para su árbol dicotómico %s con éxito.\n\n", dir, clave);
	}
	else {
		printf("❌ Ocurrió un error. Asegúrate de que el directorio sea correcto.\n");
	}

	liberarMemoriaArbol(raiz);
	
	clock_t final = clock();
	double tiempo_ejecucion = (double)(final - inicio) / CLOCKS_PER_SEC;
	printf("⏱️  Tiempo de ejecución para la creación de directorios: %fs\n", tiempo_ejecucion);
	return 0;
}**/