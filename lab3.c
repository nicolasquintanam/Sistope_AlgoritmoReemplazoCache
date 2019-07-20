#include "funciones.h"

/* ------------------------------------------------------------------------------------ */
/* ----------------------------------- MAIN ------------------------------------------- */
/* ------------------------------------------------------------------------------------ */

//Entradas: Función recibe por parámetro un número entero y un array de punteros
//			a carácteres. El número entero corresponde a la cantidad de argumen-
//			tos que se han introducido y el array de punteros contiene los argu-
//			mentos.
//Funcionamiento: Función que permite ejecutar toda la lógica del programa, ya 
//				  que corresponde al main. Primero se comienza con una bienveni-
//				  da, luego se leen los parámetros ingresados mediante GETOPT(),
//			      luego se ejecutan los algoritmos de reemplazo y escribiéndose
//				  en un archivo de salida.
//Salidas: Se retorna un número entero que indica si el main fue ejecutado correc-
//		   tamente.
int main(int argc, char *argv[]){
	/* -- Definición de variables -- */
	char *nombreArchivoEntrada, *nombreArchivoSalida;
    int cantidadMarcos, bandera, opcionGetOpt, cantidadPaginas, *paginas;
	double tasaHitFifo, tasaHitOptimo, tasaHitLru, tasaHitReloj;	
	FILE* archivoEntrada;

	/* -- Inicialización de variables y reserva de memoria -- */
	nombreArchivoEntrada = (char*)malloc(sizeof(char)*30);
    nombreArchivoSalida = (char*)malloc(sizeof(char)*30);
    cantidadMarcos = 0; bandera = 0; opcionGetOpt = 0; cantidadPaginas = 0;

	/* -- Impresión bienvenida y recepción de parámetros por consola -- */
	imprimirBienvenida();
	while((opcionGetOpt = getopt(argc, argv, "m:i:o:b")) != -1){
        	switch (opcionGetOpt){
			case 'm':
				cantidadMarcos = atoi(optarg);
				printf("La cantidad de marcos es: %i\n", cantidadMarcos);
				break;
            case 'i':
				strcpy(nombreArchivoEntrada, optarg);
				printf("El nombre del archivo de entrada es: %s\n", nombreArchivoEntrada);
				break;
			case 'o':
				strcpy(nombreArchivoSalida, optarg);
				printf("El nombre del archivo de salida es: %s\n", nombreArchivoSalida);
				break;
			case 'b':
				bandera = 1;
				printf("Bandera seleccionada\n");
				break;
			default:
				imprimirSeparador();
				printf("Se ha ingresado un parámetro incorrecto. Por favor, intente nuevamente.\n\n");
				return -1;
		}
	}
	imprimirSeparador();

	if(cantidadMarcos > 0){
		archivoEntrada = fopen(nombreArchivoEntrada, "r");
		if(archivoEntrada != NULL){
			/* -- Obtención de páginas -- */
			cantidadPaginas = contarPaginas(nombreArchivoEntrada);
			paginas = (int*) malloc(sizeof(int)*cantidadPaginas);	
			paginas = obtenerPaginas(nombreArchivoEntrada, cantidadPaginas);

			/* -- Obtención tasas de hit de algoritmos -- */
			tasaHitOptimo = algoritmoOptimo(cantidadMarcos, paginas, cantidadPaginas, nombreArchivoSalida);
			tasaHitFifo = algoritmoFifo(cantidadMarcos, paginas, cantidadPaginas, nombreArchivoSalida, 1 - tasaHitOptimo);
			tasaHitLru = algoritmoLru(cantidadMarcos, paginas, cantidadPaginas, nombreArchivoSalida, 1 - tasaHitOptimo);
			tasaHitReloj = algoritmoReloj(cantidadMarcos, paginas, cantidadPaginas, nombreArchivoSalida, 1 - tasaHitOptimo);
			/* -- Liberación de memoria -- */
			free(nombreArchivoSalida);
			free(nombreArchivoEntrada);
			free(paginas);

			/* -- Impresión de resultados -- */
			if(bandera == 1){
				imprimirResultados(tasaHitOptimo, tasaHitFifo, tasaHitLru, tasaHitReloj);
			}
			return 0;
		}
		else{
			printf("El archivo archivo que se está intentando abrir no existe...\n");
			printf("Por favor, intente con otro.\n\n");
			return -1;
		}
	}
	else{
		printf("El programa no admite una cantidad de marco menor o igual a 1...\n");
		printf("Por favor, intente con otra cantidad.\n\n");
		return -1;
	}	
}
