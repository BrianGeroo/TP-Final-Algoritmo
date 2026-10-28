#include <iostream>
#include <cstdio>
#include "html.h"

using namespace std;

void visualizarEnHTML(const char* nombreArchivo, Orden memoria[FILAS][COLUMNAS])
{
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        cout << "ERROR: No se pudo generar el archivo HTML." << endl;
        return;
    }

    // Cabecera HTML básica
    fprintf(archivo, "<!DOCTYPE html>\n<html>\n<head>\n");
    fprintf(archivo, "<title>Ataque Dron</title>\n");
    fprintf(archivo, "<style>table, th, td { border: 1px solid black; border-collapse: collapse; text-align: center; width: 20px; height: 20px; font-size: 10px; }</style>\n");
    fprintf(archivo, "</head>\n<body>\n");
    fprintf(archivo, "<h2>Mapa de Ataque Cargado en Memoria</h2>\n");
    fprintf(archivo, "<table>\n");

    // Dibujamos la tabla de 200x200
    for (int x = 0; x < FILAS; x++)
    {
        fprintf(archivo, "<tr>\n");
        for (int y = 0; y < COLUMNAS; y++)
        {
            if (memoria[x][y].celdaOcupada)
            {
                // Agregamos unas letras y colores básicos para diferenciar comandos
                if (memoria[x][y].despegue)
                    fprintf(archivo, "<td style='background-color: yellow;'>D</td>");
                else if (memoria[x][y].ataqueKamikaze || memoria[x][y].aterrizaje)
                    fprintf(archivo, "<td style='background-color: red; color: white;'>F</td>");
                else
                    fprintf(archivo, "<td style='background-color: lightgreen;'>X</td>");
            }
            else
            {
                // Celda vacía
                fprintf(archivo, "<td></td>");
            }
        }
        fprintf(archivo, "</tr>\n");
    }

    // Cierre del HTML
    fprintf(archivo, "</table>\n</body>\n</html>\n");
    fclose(archivo);

    cout << "\nEl archivo web '" << nombreArchivo << "' se ha generado correctamente." << endl;
}
