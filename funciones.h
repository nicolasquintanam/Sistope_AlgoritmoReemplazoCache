/* ------------------------------------------------------------------------------------ */
/* ----------------------------- LIBRERÍAS UTILIZADAS --------------------------------- */
/* ------------------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* ------------------------------------------------------------------------------------ */
/* --------------------------- CABECERA DE LAS FUNCIONES ------------------------------ */
/* ------------------------------------------------------------------------------------ */

void imprimirBienvenida();
int seEncuentraEnLista(int* marco, int cantidadMarcos, int pagina);
int getIndicePrimerVacio(int* marco, int cantidadMarcos);
void escribirMarcoEnArchivo(int* marco, int cantidadMarcos, FILE* archivo);
double algoritmoFifo(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo);
double algoritmoOptimo(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida);
double algoritmoLru(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo);
double algoritmoReloj(int cantidadMarcos, int* paginas, int cantidadPaginas, char* nombreArchivoSalida, double tasaMissOptimo);
int contarPaginas(char* nombreArchivoEntrada);
int* obtenerPaginas(char* nombreArchivoEntrada, int cantidadPaginas);
void imprimirResultados(double tasaHitOptimo, double tasaHitFifo, double tasaHitLru, double tasaHitReloj);
void imprimirSeparador();
int cuantoFaltaParaRepetirse(int* paginas, int cantidadPaginas, int indiceActual, int valor);
int* obtenerMarcoAux(int* marco, int cantidadMarcos, int* paginas, int cantidadPaginas, int indiceActual);
int getIndiceMayorValor(int* marco, int cantidadMarcos);
int* modificarAux(int* marcoAux, int cantidadMarcos, int indiceReferenciado);
int getLru(int* marcoAuxLru, int* marcoAux, int cantidadMarco, int mayor);
int seRepiteNumero(int numero, int* lista, int largoLista);