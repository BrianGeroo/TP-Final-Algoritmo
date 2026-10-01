#ifndef MEMORIA_H
#define MEMORIA_H

// 1. Constantes del espacio de memoria del dron
const int FILAS = 200;
const int COLUMNAS = 200;

// Constante centinela para indicar celda sin siguiente o vacía
const int POS_NULA = -1;

// 2. Estructura que reside en la memoria RAM del dron (la matriz de 200x200)
// No incluye 'x' ni 'y' porque su posición está determinada por sus índices en la matriz.
struct Orden
{
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = POS_NULA;
    int siguientey = POS_NULA;
    bool celdaOcupada = false; // Flag para saber rápidamente si hay una orden en esta celda
};

// 3. Estructura utilizada para la persistencia en archivos binarios (.dat)
// Incluye 'x' e 'y' de forma explícita para serializar y deserializar registros individuales.
struct OrdenArchivo
{
    int x = 0;
    int y = 0;
    unsigned int espera = 0;
    bool soltarGranada1 = false;
    bool soltarGranada2 = false;
    bool ataqueKamikaze = false;
    bool aterrizaje = false;
    bool despegue = false;
    int siguientex = 0;
    int siguientey = 0;
};

// 4. Declaración de la matriz global de memoria accesible para todo el programa
extern Orden memoria[FILAS][COLUMNAS];

// 5. Prototipos de funciones de gestión de memoria
void inicializarMemoria();
bool estaEnRango(int x, int y);

#endif // MEMORIA_H