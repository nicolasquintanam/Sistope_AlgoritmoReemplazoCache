#include "funciones.h"

/* ------------------------------------------------------------------------------------ */
/* --------------------------------- FUNCIONES ---------------------------------------- */
/* ------------------------------------------------------------------------------------ */

//Entradas: No tiene parámetros de entrada.
//Funcionamiento: Función que imprime un mensaje de bienvenida que se mues-
//                tra al comienzo del programa.
//Salidas: Se retorna nada, debido a que es void.
void imprimirBienvenida(){
    /* -- Cuerpo de la función -- */
    printf("\n################################################");
	printf("\n############### Laboratorio 3 ##################");
	printf("\n############ Sistemas Operativos ###############");
	printf("\n################################################");
	printf("\n################################################");
	printf("\n################################################");
	printf("\n################################################");
	printf("\n### Integrantes:       #########################");
	printf("\n### - Rodrigo Castillo #########################");
	printf("\n### - Nicolás Quintana #########################");
	printf("\n################################################\n\n");
}

//Entradas: No tiene parámetros de entrada.
//Funcionamiento: Función que imprime un separador. Que como dice su nombre
//                separa dos mensajes para mostrar por consola el funciona-
//                miento más amigable.
//Salidas: Se retorna nada, debido a que es void.
void imprimirSeparador(){
    /* -- Cuerpo de la función -- */
    printf("\n-------------------------------------------------\n\n");
}

//Entradas: Función recibe por parámetro un puntero a char, que se utiliza 
//          como un string. Este puntero a char hace referencia al nombre de
//          archivo de entrada, es decir, el archivo que contiene la lista 
//          de páginas a referenciar.
//Funcionamiento: Función permite contar la cantidad de páginas a referen-
//                ciar.
//Salidas: Se retorna un número entero que indica la cantidad de páginas a
//         referenciar.
int contarPaginas(char* nombreArchivoEntrada){
    /* -- Definición de variables -- */
    char *separador, *lecturaArchivo;
    int cantidadPaginas;
    FILE *archivoEntrada;

    /* -- Inicialización de variables y reserva de memoria -- */
    lecturaArchivo = (char*)malloc(sizeof(char)*1024);
    archivoEntrada = fopen(nombreArchivoEntrada, "r");
    cantidadPaginas = 0;
    
    /* -- Apertura de archivo -- */
    fread(lecturaArchivo, sizeof(char(*)), 1024, archivoEntrada);    

    /* -- Cuerpo de la función -- */
    separador = strtok(lecturaArchivo, ", ");
    while( separador != NULL ) {
        cantidadPaginas++;
        separador = strtok(NULL, ", ");
    }

    /* -- Cierre de archivo y liberación de memoria -- */
    fclose(archivoEntrada); 
    free(separador);
    free(lecturaArchivo);

    return cantidadPaginas;
}

//Entradas: Función recibe por parámetro un puntero a char y un número entero.
//          El puntero a char se utiliza como un string y hace referencia a el
//          nombre del archivo de entrada, el que contiene las páginas a refe-
//          renciar. Por otro lado, el número entero hace referencia a la can-
//          tidad de páginas que se van a referenciar.
//Funcionamiento: Función permite obtener las páginas que se van a referenciar,
//                y llevarlas a un puntero a entero (int) que se utilizará como
//                una lista de números enteros. 
//Salidas: Se retorna un puntero a entero (int) que hace referencia a la lista 
//         de páginas a referenciar.
int* obtenerPaginas(char* nombreArchivoEntrada, int cantidadPaginas){
    /* -- Definición de variables -- */
    char *separador, *lecturaArchivo;
    int *paginas, i;
    FILE* archivoEntrada;

    /* -- Inicialización de variables y reserva de memoria -- */
    lecturaArchivo = (char*)malloc(sizeof(char)*1024);
    archivoEntrada = fopen(nombreArchivoEntrada, "r");
    paginas = (int*) malloc(sizeof(int)*cantidadPaginas);	

    /* -- Apertura de archivo -- */
    fread(lecturaArchivo, sizeof(char(*)), 1024, archivoEntrada);   

    /* -- Cuerpo de la función -- */
	separador = strtok(lecturaArchivo, ", ");
	for (i = 0; i < cantidadPaginas; i++){
		paginas[i] = atoi(separador);
		separador = strtok(NULL, ", ");
	}

    /* Cierre de archivo y liberación de memoria -- */
    fclose(archivoEntrada);
    free(separador);
    free(lecturaArchivo);

    return paginas;
}

//Entradas: Función recibe por parámetro un puntero a entero (int), un puntero
//          a char y dos números enteros. El puntero a entero corresponde a las
//          páginas a referenciar; el puntero a char, se utiliza como un string
//          y corresponde al nombre del archivo de salida; el primer número en-
//          tero corresponde a la cantidad de marcos; el segundo corresponde a 
//          la cantidad de páginas a referenciar.
//Funcionamiento: Función permite aplicar el algoritmo óptimo a una lista de pá-
//                ginas en una determinada cantidad de marcos. Además se escribe
//                la traza, resultado, tasa de hit y tasa de miss en un archivo.
//Salidas: Se retorna un número de tipo double que indica la tasa de hit del al-
//         goritmo.
double algoritmoOptimo(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida){
    FILE* archivoSalida;
    int *marco, *marcoAux, *marcoAuxLru;
    int i, hitOptimo, contador, iteracionInt, count, indiceMayorValor, seEncuentraEnLaLista, seRepiteNumeroMayor;
    double tasaHit, iteracion;

    indiceMayorValor = 0; seRepiteNumeroMayor = 0;
    hitOptimo = 0; contador = 0; iteracion = 1.0; iteracionInt = 1;
    count = 0;
    archivoSalida = fopen(nombreArchivoSalida, "w");
    marco = (int*) malloc(sizeof(int)*cantidadMarcos);
    marcoAux = (int*) malloc(sizeof(int)*cantidadMarcos);
    marcoAuxLru = (int*) malloc(sizeof(int)*cantidadMarcos);

    for(i = 0; i < cantidadMarcos; i++){
        marco[i] = -1;
        marcoAux[i] = 0;
        marcoAuxLru[i] = -1;
    }
    fprintf(archivoSalida, "-- Algoritmo OPTIMO --\n\n");
    fprintf(archivoSalida, " ");
    int cantidad, indiceEspacioVacio;
    cantidad = (6 * cantidadMarcos) - 1;
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "_");
    }
    fprintf(archivoSalida, " \n");
    for(i = 0; i < cantidadPaginas; i++){
        seEncuentraEnLaLista = seEncuentraEnLista(marco, cantidadMarcos, paginas[i]);
        if(seEncuentraEnLaLista != -1){
            hitOptimo++;
            marcoAuxLru = modificarAux(marcoAuxLru, cantidadMarcos, seEncuentraEnLaLista);
        }
        else{
            indiceEspacioVacio = getIndicePrimerVacio(marco, cantidadMarcos);
            if(indiceEspacioVacio != -1){
                marco[indiceEspacioVacio] = paginas[i];
                marcoAuxLru = modificarAux(marcoAuxLru, cantidadMarcos, indiceEspacioVacio);
            }
            else{
                marcoAux = obtenerMarcoAux(marco, cantidadMarcos, paginas, cantidadPaginas, i);
                indiceMayorValor = getIndiceMayorValor(marcoAux, cantidadMarcos);
                seRepiteNumeroMayor = seRepiteNumero(marcoAux[indiceMayorValor], marcoAux, cantidadMarcos);
                if(seRepiteNumeroMayor == 1){ 
                    indiceMayorValor = getLru(marcoAuxLru, marcoAux, cantidadMarcos, marcoAux[indiceMayorValor]);
                }
                    marco[indiceMayorValor] = paginas[i];
                    marcoAuxLru = modificarAux(marcoAuxLru, cantidadMarcos, indiceMayorValor);
            }
        }
        escribirMarcoEnArchivo(marco, cantidadMarcos, archivoSalida);
    }
    fprintf(archivoSalida, " ");
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "-");
    }
    tasaHit = (double) hitOptimo/cantidadPaginas;

    fprintf(archivoSalida, " \n\n");
    fprintf(archivoSalida, "tasa miss: %.2f %%\n", 100.0*(1-tasaHit));
    fprintf(archivoSalida, "tasa hit: %.2f %%\n\n", 100.0*tasaHit);

    fclose(archivoSalida);
    free(marco);
    free(marcoAux);
    free(marcoAuxLru);

    return tasaHit;
}

//Entradas: Función recibe por parámetro un puntero a entero (int), un puntero
//          a char, dos números enteros y un número de tipo double. El puntero
//          a entero corresponde a las páginas a referenciar; el puntero a char
//          se utiliza como un string y corresponde al nombre del archivo de 
//          salida; el pimer número entero corresponde a la cantidad de marcos;
//          el segundo corresponde a la cantidad de páginas a referenciar; el 
//          número de tipo double corresponde a la tasa de miss correspondiente
//          al algoritmo del óptimo.
//Funcionamiento: Función permite aplicar el algoritmo FIFO a una lista de pá- 
//                ginas en una determinada cantidad de marcos. Además se escri-
//                be la traza, resultado, tasa de hit, tasa de miss y porcentaje
//                de peor en comparación con el algoritmo del óptimo.
//Salidas: Se retorna un número de tipo double que indica la tasa de hit del al-
//         goritmo.
double algoritmoFifo(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo){
    int *marco;
    int hitFifo, contador, i;
    double tasaHit;
    FILE* archivoSalida;

    marco = (int*) malloc(sizeof(int)*cantidadMarcos);
    archivoSalida = fopen(nombreArchivoSalida, "a");
    hitFifo = 0; contador = 0;
    
	for(i = 0; i < cantidadMarcos; i++){
		marco[i] = -1;
	}
    fprintf(archivoSalida, "-- Algoritmo FIFO --\n\n");
    fprintf(archivoSalida, " ");
    int cantidad;
    cantidad = (6*cantidadMarcos)-1;
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "_");
    }
    fprintf(archivoSalida, " \n");
	for(i = 0; i < cantidadPaginas; i++){
		if(seEncuentraEnLista(marco, cantidadMarcos, paginas[i]) != -1){
			hitFifo++;
		}
		else{
			if(contador < cantidadMarcos){
				marco[contador] = paginas[i];
				contador++;
			}
			else{
				contador = 0;
				marco[contador] = paginas[i];
				contador++;
			}
		}
		escribirMarcoEnArchivo(marco, cantidadMarcos, archivoSalida);
	}
    fprintf(archivoSalida, " ");
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "-");
    }
    tasaHit = (double) hitFifo/cantidadPaginas;
    fprintf(archivoSalida, " \n\n");
    fprintf(archivoSalida, "tasa miss: %.2f %%\n", 100.0*(1.0-tasaHit));
    fprintf(archivoSalida, "tasa hit: %.2f %%\n", 100.0*tasaHit);
    fprintf(archivoSalida, "%.2f %% peor que algoritmo optimo\n\n", 100.0 * ((1.0-tasaHit)-tasaMissOptimo));

    fclose(archivoSalida);
    free(marco);
	
    return tasaHit;
}

//Entradas: Función recibe por parámetro un puntero a entero (int), un puntero
//          a char, dos números enteros y un número de tipo double. El puntero
//          a entero corresponde a las páginas a referenciar; el puntero a char
//          se utiliza como un string y corresponde al nombre del archivo de 
//          salida; el pimer número entero corresponde a la cantidad de marcos;
//          el segundo corresponde a la cantidad de páginas a referenciar; el 
//          número de tipo double corresponde a la tasa de miss correspondiente
//          al algoritmo del óptimo.
//Funcionamiento: Función permite aplicar el algoritmo LRU a una lista de pá-  
//                ginas en una determinada cantidad de marcos. Además se escri-
//                be la traza, resultado, tasa de hit, tasa de miss y porcentaje
//                de peor en comparación con el algoritmo del óptimo.
//Salidas: Se retorna un número de tipo double que indica la tasa de hit del al-
//         goritmo.
double algoritmoLru(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo){
    FILE* archivoSalida;
    int *marco, *marcoAux;
    int hitLru, i, contador, indiceEspacioVacio, seEncuentraEnLaLista, indiceMayorValor;
    double tasaHit;

    hitLru = 0, contador = 0;
    archivoSalida = fopen(nombreArchivoSalida, "a");
    marco = (int*) malloc(sizeof(int)*cantidadMarcos);
    marcoAux = (int*) malloc(sizeof(int)*cantidadMarcos);

    for(i = 0; i < cantidadMarcos; i++){
        marco[i] = -1;
        marcoAux[i] = -1;
    }

    fprintf(archivoSalida, "-- Algoritmo LRU --\n\n");
    fprintf(archivoSalida, " ");
    int cantidad;
    cantidad = (6 * cantidadMarcos) - 1;
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "_");
    }
    fprintf(archivoSalida, " \n");
    for(i = 0; i < cantidadPaginas; i++){
        seEncuentraEnLaLista = seEncuentraEnLista(marco, cantidadMarcos, paginas[i]);
        if(seEncuentraEnLaLista != -1){
            hitLru++;
            marcoAux = modificarAux(marcoAux, cantidadMarcos, seEncuentraEnLaLista);
        }
        else{
            indiceEspacioVacio = getIndicePrimerVacio(marco, cantidadMarcos);
            if(indiceEspacioVacio != -1){
                marco[indiceEspacioVacio] = paginas[i];
                marcoAux = modificarAux(marcoAux, cantidadMarcos, indiceEspacioVacio);
            }
            else{
                indiceMayorValor = getIndiceMayorValor(marcoAux, cantidadMarcos);
                marco[indiceMayorValor] = paginas[i];
                marcoAux = modificarAux(marcoAux, cantidadMarcos, indiceMayorValor);
                
            }
        }
        
        escribirMarcoEnArchivo(marco, cantidadMarcos, archivoSalida);
    }
    tasaHit = (double) hitLru/cantidadPaginas;
    fprintf(archivoSalida, " ");
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "-");
    }
    fprintf(archivoSalida, " \n\n");
    fprintf(archivoSalida, "tasa miss: %.2f %%\n", 100.0*(1-tasaHit));
    fprintf(archivoSalida, "tasa hit: %.2f %%\n", 100.0*tasaHit);
    fprintf(archivoSalida, "%.2f %% peor que algoritmo optimo\n\n", 100.0 * ((1.0-tasaHit)-tasaMissOptimo));

    fclose(archivoSalida);
    free(marco);
    free(marcoAux);

    return tasaHit;
}

//Entradas: Función recibe por parámetro un puntero a entero (int), un puntero
//          a char, dos números enteros y un número de tipo double. El puntero
//          a entero corresponde a las páginas a referenciar; el puntero a char
//          se utiliza como un string y corresponde al nombre del archivo de 
//          salida; el pimer número entero corresponde a la cantidad de marcos;
//          el segundo corresponde a la cantidad de páginas a referenciar; el 
//          número de tipo double corresponde a la tasa de miss correspondiente
//          al algoritmo del óptimo.
//Funcionamiento: Función permite aplicar el algoritmo Reloj a una lista de pá-  
//                ginas en una determinada cantidad de marcos. Además se escri-
//                be la traza, resultado, tasa de hit, tasa de miss y porcentaje
//                de peor en comparación con el algoritmo del óptimo.
//Salidas: Se retorna un número de tipo double que indica la tasa de hit del al-
//         goritmo.
double algoritmoReloj(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo){
    FILE* archivoSalida;
    int *marco, *marcoReloj;
    int i, hitReloj, contador, puntero, ultimoReferenciado;
    double tasaHit; 

    hitReloj = 0, contador = 0; puntero = 0;

    archivoSalida = fopen(nombreArchivoSalida, "a");
    marco = (int*) malloc(sizeof(int)*cantidadMarcos);
    marcoReloj = (int*) malloc(sizeof(int)*cantidadMarcos);

    for(i = 0; i < cantidadMarcos; i++){
        marco[i] = -1;
        marcoReloj[i] = 0;
    }

    fprintf(archivoSalida, "-- Algoritmo del RELOJ --\n\n");
    fprintf(archivoSalida, " ");
    int cantidad;
    cantidad = (6 * cantidadMarcos) - 1;
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "_");
    }
    fprintf(archivoSalida, " \n");
    for(i = 0; i < cantidadPaginas; i++){
        ultimoReferenciado = seEncuentraEnLista(marco, cantidadMarcos, paginas[i]);
        if(ultimoReferenciado != -1){
            marcoReloj[ultimoReferenciado] = 1;
            hitReloj++;
        }
        else{
            while(marcoReloj[puntero] == 1){
                
                marcoReloj[puntero] = 0;
                puntero++;
                if(puntero == cantidadMarcos){
                    puntero = 0;
                }
            }
            marco[puntero] = paginas[i];
            marcoReloj[puntero] = 1;
            puntero++;
            if(puntero == cantidadMarcos){
                puntero = 0;
            }
        }
        escribirMarcoEnArchivo(marco, cantidadMarcos, archivoSalida);
    }
    fprintf(archivoSalida, " ");
    for(i = 0; i < cantidad; i++){
        fprintf(archivoSalida, "-");
    }
    tasaHit = (double) hitReloj/cantidadPaginas;

    fprintf(archivoSalida, " \n\n");
    fprintf(archivoSalida, "tasa miss: %.2f %%\n", 100.0*(1-tasaHit));
    fprintf(archivoSalida, "tasa hit: %.2f %%\n", 100.0*tasaHit);
    fprintf(archivoSalida, "%.2f %% peor que algoritmo optimo\n\n", 100.0 * ((1.0-tasaHit)-tasaMissOptimo));

    fclose(archivoSalida);
    free(marco);
    free(marcoReloj);

    return tasaHit;
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y dos números
//          enteros. El puntero a entero hace referencia al marco; el primer int
//          que se pasa por parámetro es la cantidad de marcos y el segundo hace
//          referencia a la cantidad de páginas a referenciar.
//Funcionamiento: Función permite buscar la página dada por parámetro en el marco
//                para obtener el índice en dónde se encuentra. Si no lo encuen-
//                tra, retornar un -1.
//Salidas: Se retorna el índice de la página buscada en el marco. si no se encuen-
//         tra, se retorna un -1.
int seEncuentraEnLista(int* marco, int cantidadMarcos, int pagina){
    /* -- Definición de variables -- */
    int i;

    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarcos; i++){
        if(marco[i] == pagina){
            return i;
        }
    }

    return -1;
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y un número en-
//          tero. El puntero a entero hace referencia al marco y el número entero
//          es la cantidad de marcos.
//Funcionamiento: Función permite obtener el indice del primer 'elemento' vacío en
//                el marco. Se busca el elemento -1 ya que éste hace referencia a
//                un espacio vacío en el marco. Si el marco se encuentra completo,
//                se retorna un -1.
//Salidas: Se retorna el índice del primer espacio vacío en el marco. Si no se en-
//         cuentra un espacio vacío, se retorna un -1.
int getIndicePrimerVacio(int* marco, int cantidadMarcos){
    /* -- Cuerpo de la función -- */
    return seEncuentraEnLista(marco, cantidadMarcos, -1);
}

//Entradas: Función recibe por parámetro un puntero a entero (int), un número entero
//          y un puntero a FILE. El puntero a entero hace referencia al marco, el nú-
//          mero entero es la cantidad de marcos y por último el puntero a FILE hace
//          referencia al archivo.
//Funcionamiento: Función permite escribir el marco ingresado por parámetro en el ar- 
//                archivo.
//Salidas: Se retorna nada, ya que es void.
void escribirMarcoEnArchivo(int* marco, int cantidadMarcos, FILE* archivo){
    /* -- Definición de variables -- */
    int i;
    char salida[20], aux[12];

    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarcos; i++){
        if(marco[i] == -1){
            if(i == 0){
                strcpy(salida, "|     -");
            }
            else{
                if(i == cantidadMarcos-1){
                    strcpy(salida, "     |");
                }
                else{
                    strcpy(salida, "     -");        
                }
            }
        }
        else{
            if(marco[i] >= 10){
                if(i == 0){
                    strcpy(salida, "|  ");
                    sprintf(aux, "%i", marco[i]);
                    strcat(salida, aux);
                    strcat(salida, " -");
                }
                else{
                    if(i == cantidadMarcos-1){
                        strcpy(salida, "  ");
                        sprintf(aux, "%i", marco[i]);
                        strcat(salida, aux);
                        strcat(salida, " |");
                    }
                    else{
                        strcpy(salida, "  ");
                        sprintf(aux, "%i", marco[i]);
                        strcat(salida, aux);
                        strcat(salida, " -");
                    }
                }
            }
            else{
                if(i == 0){
                    strcpy(salida, "|  ");
                    sprintf(aux, "%i", marco[i]);
                    strcat(salida, aux);
                    strcat(salida, "  -");
                }
                else{
                    if(i == cantidadMarcos - 1){
                        strcpy(salida, "  ");
                        sprintf(aux, "%i", marco[i]);
                        strcat(salida, aux);
                        strcat(salida, "  |");
                    }
                    else{
                        strcpy(salida, "  ");
                        sprintf(aux, "%i", marco[i]);
                        strcat(salida, aux);
                        strcat(salida, "  -");
                    }
                }
            }
        }
        fprintf(archivo, "%s", salida);
    }
    fprintf(archivo, "\n");
}

//Entradas: Función recibe por parámetro cuatro números double que hacen referencia a
//          la tasa de hit de los diferentes algoritmos de reemplazo. Vale decir, del
//          algoritmo óptimo, fifo, lru y reloj.
//Funcionamiento: Función permite imprimir por pantalla (consola) la tasa de hit de
//                los diferentes algoritmos.
//Salidas: Se retorna nada, ya que es void.
void imprimirResultados(double tasaHitOptimo, double tasaHitFifo, double tasaHitLru, double tasaHitReloj){
    /* -- Cuerpo de la función -- */
    printf("Resultados: \n");
    printf("tasa de hit ÓPTIMO: %.2f %%\n", 100.0 * tasaHitOptimo);
    printf("tasa de hit FIFO: %.2f %%\n", 100.0 * tasaHitFifo);
    printf("tasa de hit LRU: %.2f %%\n", 100.0 * tasaHitLru);
    printf("tasa de hit RELOJ: %.2f %%\n\n", 100.0 * tasaHitReloj);
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y un número entero.
//          El puntero a entero hace referencia al marco y el número entero a la canti-
//          dad de marcos.
//Funcionamiento: Función permite obtener el índice en dónde se encuentra el número de
//                mayor valor dentro del marco. Cabe destacar que para este programa,
//                el -1 es el número más grande.
//Salidas: Se retorna un número entero que hace referencia al índice del número con mayor
//         valor.
int getIndiceMayorValor(int* marco, int cantidadMarcos){
    /* -- Definición de variables -- */
    int i, mayor;

    /* -- Inicialización de variables -- */
    mayor = marco[0];

    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarcos; i++){
        if(marco[i] == -1){
            return i;
        }
        else{
            if(marco[i] > mayor){
                mayor = marco[i];
            }
        }
    }
    for(i = 0; i < cantidadMarcos; i++){
        if(marco[i] == mayor){
            return i;
        }
    }

    return i;
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y tres números enteros.
//          El puntero a entero hace referencia a las páginas; el primer número entero es
//          la cantidad de páginas; el segundo número entero corresponde al índice actual;
//Funcionamiento: Función útil para el algoritmo óptimo. Para el funcionamiento de este al-
//                goritmo, se necesita saber cuánto falta para que se vuelva a referenciar
//                en el futuro. Por lo tanto, este método, cumple con esta función.
//Salidas: Se retorna un número que indica que para un valor faltan n espacios para que se
//         vuelva a referenciar. Si no se vuelve a referenciar, se retorna un -1.
int cuantoFaltaParaRepetirse(int* paginas, int cantidadPaginas, int indiceActual, int valor){
    /* -- Definición de variables -- */
    int i, j;

    /* -- Inicialización de variables -- */
    j = 0;

    /* -- Cuerpo de la función -- */
    for(i = indiceActual; i < cantidadPaginas; i++){
        if(paginas[i] == valor){
            return j + 1;
        }
        j++;
    }
    return -1;
}

//Entradas: Función recibe por parámetro dos punteros a entero (int) y tres números enteros.
//          El primer puntero a entero corresponde al marco; el segundo corresponde a las pá-
//          ginas. El primer número entero corresponde a la cantidad de marcos; el segundo a
//          la cantidad de páginas; el tercero corresponde al índice actual.
//Funcionamiento: Función útil para el algoritmo Óptimo. Permite obtener dependiendo a un marco
//                otro marco que corresponde a cuánto falta para volver a referenciarse (por ca-
//                da uno).
//Salidas: Se retorna un puntero a entero que hace referencia al marco auxiliar.
int* obtenerMarcoAux(int* marco, int cantidadMarcos, int* paginas, int cantidadPaginas, int indiceActual){
    /* -- Definición de variables -- */
    int i, falta, *marcoAux;

    /* -- Reserva de memoria -- */
    marcoAux = (int*)malloc(sizeof(int)*cantidadMarcos);

    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarcos; i++){
        falta = cuantoFaltaParaRepetirse(paginas, cantidadPaginas, indiceActual, marco[i]);
        marcoAux[i] = falta;
    }
    return marcoAux;
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y dos números enteros.
//          El puntero a entero hace referencia al marco auxiliar que contiene cuánto falta
//          por referenciarse en el algoritmo óptimo. El primer número entero corresponde a
//          la cantidad de marcos; el segundo corresponde a un indice recientemente referen-
//          ciado.
//Funcionamiento: Función permite modificar el marco auxiliar y retornar uno nuevo ya modificado.
//                En el algoritmo óptimo, se requiere de un marco auxiliar que contenga cuánto fal-
//                ta por cada elemento por volver a referenciarse. Esta función actualiza el marco.
//                Si se acaba de referenciar, se deja en 0, sino, se aumenta en 1.
//Salidas: Se retorna el nuevo marco auxiliar como un puntero a entero.
int* modificarAux(int* marcoAux, int cantidadMarcos, int indiceReferenciado){
    /* -- Declaración de variables -- */
    int i;
    
    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarcos; i++){
        if(indiceReferenciado == i){
            marcoAux[i] = 0;
        }
        else{
            if(marcoAux[i] != -1){
                marcoAux[i] = marcoAux[i] + 1;
            }
        }
    }

    return marcoAux;
}

//Entradas: Función recibe por parámetro dos punteros a entero (int) y un número entero.
//          El primero puntero a entero corresponde al marco auxiliar de LRU; el segundo
//          corresponde al marco auxiliar del algoritmo óptimo. Y por último el número 
//          corresponde al elemento mayor en el marco auxiliar, es decir, en el marco que
//          contiene cuánto falta por volver a referenciarse.
//Funcionamiento: Función permite obtener el índice del número mayor en el marco auxiliar LRU.
//                Ya que, cuando en el algoritmo óptimo se tiene una igualdad de condición, es
//                decir, dos números se referenciarán en 2 posiciónes, se debe aplicar el algo-
//                ritmo de LRU.
//Salidas: Se retorna el índice del número mayor.
int getLru(int* marcoAuxLru, int* marcoAux, int cantidadMarco, int mayor){
    /* -- Declaración de variables -- */
    int i, indiceNuevoMayor;

    /* -- Inicialización de variables -- */
    i = 0; indiceNuevoMayor = 0;

    /* -- Cuerpo de la función -- */
    for(i = 0; i < cantidadMarco; i++){
        if(marcoAux[i] == mayor){
            if(marcoAuxLru[i] > marcoAuxLru[indiceNuevoMayor]){
                indiceNuevoMayor = i;
            }
        }
    }
    return indiceNuevoMayor;
}

//Entradas: Función recibe por parámetro un puntero a entero (int) y dos números enteros.
//          El puntero a entero corresponde a una lista; el primer número entero corresponde
//          a un número que se verificará si se repite en la lista; y el segundo corresponde
//          al largo de la lista.
//Funcionamiento: Función permite indicar si un número se repite en una lista.
//Salidas: Se retorna un 1 indicando que sí se repite y un 0 cuando no.
int seRepiteNumero(int numero, int* lista, int largoLista){
    /* -- Definición de variables -- */
    int i, contador, resultado;

    /* -- Inicialización de variables -- */
    i = 0; contador = 0; resultado = 0;

    /* -- Cuerpo de la función -- */
    for(i = 0; i < largoLista; i++){
        if(numero == lista[i]){
            contador++;
        }
    }
    if(contador > 2){
        //SÍ
        resultado = 1;
    }
    else{
        //NO
        resultado = 0;
    }

    return resultado;
}