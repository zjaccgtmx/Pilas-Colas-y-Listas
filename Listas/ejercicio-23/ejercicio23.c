#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANT_ALUMNOS 100
#define INPUT_BIN "entrada.bin"
#define OUTPUT_BIN "salida.bin"
/**
 * Char: 1 byte
 * Puntero: 4 bytes
 * Entero: 4 bytes
 * Coma flotante: 8 bytes
 * Bool (enum): 4 bytes
 * Bool: 1 byte
 *** Si usamos "short" la cantidad de bytes es la mitad.
 *** Si usamos "long" la cantidad de bytes es el doble.
 */

/**
 * Dado un archivo de registros de alumnos ARCHA sin ningún orden, donde cada registro contiene:
 * a) Apellido y Nombre del alumno (34 caracteres) 
 * b) Número de legajo (6 dígitos) c) División asignada (1 a 100).
 * Se debe desarrollar el algoritmo y codificación del programa que genere un archivo ARCHL igual al anterior pero ordenado por número de legajo.
 * Nota: Memoria estática 64 KB; dinámica suficiente si ningún​ ​nodo​ ​ocupa​ ​más​ ​de​ ​12​ ​bytes. 
 */
// ftell se divide por la posición del registro, porque ftell() devuelve un long int

/**
 *  Estructura para leer el archivo ARCHA. Memoria estática
 *  41 bytes
 */
typedef struct 
{
    int legajo; // 4 bytes, puede ir de 0 a 999.999
    char nombre[34+1]; // 35 bytes
    short int divisionAsignada; // 2 bytes
} ST_BIN;

typedef struct nodo
{
    int legajo;
    struct nodo *ste;
} ST_NODO;

void error(const char *text)
{
    printf("%s\n", text);
    exit(EXIT_FAILURE);
}

FILE *open(const char *nombre, const char *modo)
{
    FILE *nuevoArchivo = NULL;
    if( (nuevoArchivo = fopen(nombre, modo)) == NULL )
        error("Imposible abrir el archivo.");

    return nuevoArchivo; 
}

ST_NODO *crearNodo(ST_BIN dato)
{
    ST_NODO *nuevoNodo = (ST_NODO*) malloc(sizeof(ST_NODO));
    nuevoNodo->legajo = dato.legajo;
    nuevoNodo->ste = NULL;
    return nuevoNodo;
}

ST_NODO *insertarOrdenado(ST_NODO **cabecera, ST_BIN dato)
{
    ST_NODO *nuevoNodo = crearNodo(dato);
    ST_NODO *aux = *cabecera;
    ST_NODO *anterior = NULL;
    while( aux && aux->legajo < dato.legajo )
    {
        anterior = aux;
        aux = aux->ste;
    }
    if( anterior != NULL ) // Si hay anterior, quiere decir que había un legajo menor en el espacio anterior
        anterior->ste = nuevoNodo; // Así que ese anterior tiene que apuntar a siguiente, que tiene un valor mayor
    else 
        *cabecera = nuevoNodo;

    nuevoNodo->ste = aux; // enlazo el nodo nuevo con el resto de la lista (debería tener valores mayores a nuevoNodo->legajo)
    return nuevoNodo;
}

void crearPup()
{
    printf("crearPup()");
}

void crearBinarioDePrueba()
{
    FILE *entrada = open(INPUT_BIN, "a+b");
    ST_BIN dummie;
    for(int i = 0;i < CANT_ALUMNOS;i++)
    {
        dummie.legajo = rand() % 1000; // El lote de prueba lo hago con 3 dígitos en vez de 6 porque soy re heavy re jodido. Debería funcionar igual con 6 digitos por legajo :)
        strncpy(dummie.nombre, "Personita", 34+1);
        dummie.divisionAsignada = rand() % 100+1;
        fwrite(&dummie, sizeof(ST_BIN), 1, entrada);
    }
    fclose(entrada);
}

int main()
{
    // Leo secuencialmente el archivo
    // Hago un algoritmo que acomode la lista según van entrando los legajos nuevos
    ST_BIN lectura;
    ST_NODO *cabecera = NULL;
    FILE *entrada = open(INPUT_BIN, "rb");
    crearBinarioDePrueba();
    /*fread(&lectura, sizeof(ST_BIN), 1, entrada);
    while( !feof(entrada) )
    {
        insertarOrdenado(&cabecera, lectura); // Insertará en la cabecera el legajo de forma ordenada
        crearPup(lectura); // Ubicará en el archivo el registro del alumno completo
    }
    fclose(entrada);*/
}