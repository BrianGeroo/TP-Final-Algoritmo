#include "memoria.h"

// Definición y reserva física de la memoria del dron (40.000 celdas)
Orden memoria[FILAS][COLUMNAS];

// Función para reiniciar o limpiar la memoria del dron
void inicializarMemoria()
{
    for (int i = 0; i < FILAS; ++i)
    {
        for (int j = 0; j < COLUMNAS; ++j)
        {
            memoria[i][j].espera = 0;
            memoria[i][j].soltarGranada1 = false;
            memoria[i][j].soltarGranada2 = false;
            memoria[i][j].ataqueKamikaze = false;
            memoria[i][j].aterrizaje = false;
            memoria[i][j].despegue = false;
            memoria[i][j].siguientex = POS_NULA;
            memoria[i][j].siguientey = POS_NULA;
            memoria[i][j].celdaOcupada = false;
        }
    }
}

// Función auxiliar de seguridad para validar coordenadas dentro de la grilla
bool estaEnRango(int x, int y)
{
    return (x >= 0 && x < FILAS && y >= 0 && y < COLUMNAS);
}