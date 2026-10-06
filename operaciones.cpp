#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

#include "memoria.h"
#include "operaciones.h"

using namespace std;

//Máxima cantidad de celdas
const int MAX_CELDAS = FILAS * COLUMNAS;

OrdenArchivo registrosTemp [MAX_CELDAS];
bool visitadosTemp [MAX_CELDAS];

int posRegistro [FILAS][COLUMNAS];

bool celdasAled (int x1, int y1, int x2, int y2)
{
    int difX = abs (x1 - x2);
    int difY = abs (y1 - y2);

    return (difX <=1 && difY <= 1) && !(difX == 0 && difY == 0);
}

bool cargarArchivoEnMemoria(const char* rutaArchivo)
{
    FILE* archivo = fopen (rutaArchivo,"rb");
    if (!archivo)
    {
        cout << "ERROR: No se pudo cargar el archivo '"<<rutaArchivo << "'. Verifique que la ruta sea correcta y que el archivo exista." << endl;
        return false;
    }
    int cantidad = 0;
    OrdenArchivo reg;

    //Lectura de registro a registro
    while (fread (&reg, sizeof(OrdenArchivo),1, archivo)==1)
    {
        if (cantidad >= MAX_CELDAS)
        {
            cout << "ERROR: El archivo excede la cantidad máxima de celdas permitidas." << endl;
            fclose(archivo);
            return false;
        }
        registrosTemp [cantidad] = reg;
        cantidad++;
    }
    fclose(archivo);

    if (cantidad < 2)
    {
        cout << "ERROR: El archivo debe contener al menos 2 registros"<<endl;
        return false;
    }

    for (int x = 0; x < FILAS; x++)
        for (int y = 0; y < COLUMNAS; y++)
            posRegistro[x][y] = -1;

    //Validaciones generales.
    int cantDespegue = 0;
    int cantFin = 0;
    int idxDespegue = -1;

    for (int i = 0; i < cantidad; i++)
    {
        int x = registrosTemp[i].x;
        int y = registrosTemp[i].y;

        if (!estaEnRango(x, y))
        {
            cout << "ERROR: Coordenada fuera de rango en celda (" << x << ", " << y << ")." << endl;
            return false;
        }

        if (posRegistro[x][y] != -1)
        {
            cout << "ERROR: Coordenadas duplicadas en (" << x << ", " << y << ")." << endl;
            return false;
        }
        posRegistro[x][y] = i;

        if (registrosTemp[i].despegue)
        {
            cantDespegue++;
            idxDespegue = i;

            if (registrosTemp[i].soltarGranada1 || registrosTemp[i].soltarGranada2 || registrosTemp[i].ataqueKamikaze)
            {
                cout << "ERROR: La instrucción de despegue no puede estar acompañada por ningún ataque."<<endl;
                return false;
            }
        } 
        bool esAterrizaje = registrosTemp[i].aterrizaje;
        bool esKamikaze = registrosTemp[i].ataqueKamikaze;

        if (esAterrizaje && esKamikaze)
        {
            cout << "ERROR: Un registro no puede contener aterrizaje y ataque kamikaze simultáneamente."<<endl;
            return false;
        }

        if (esAterrizaje || esKamikaze)
            cantFin++;
    }

    if (cantDespegue != 1)
    {
        cout << "ERROR: El archivo debe contener un único despegue."<<endl;
        return false;
    }

    if (cantFin != 1)
    {
        cout << "ERROR: Debe existir un único aterrizaje o ataque kamikaze."<<endl;
        return false;
    }
    
    for (int i=0; i < cantidad; i++)
        visitadosTemp [i] = false;

    int idxActual = idxDespegue;
    int pasosRecorridos = 0;

    while (idxActual != -1)
    {
        visitadosTemp [idxActual] = true;
        pasosRecorridos++;

        if (registrosTemp[idxActual].aterrizaje || registrosTemp[idxActual].ataqueKamikaze)
        {
            break;
        }

        int sigX = registrosTemp[idxActual].siguientex;
        int sigY = registrosTemp[idxActual].siguientey;
    
        if (!estaEnRango(sigX, sigY))
        {
            cout << "ERROR: La celda siguiente ("<<sigX<<", "<<sigY<<") está fuera de rango."<<endl;
            return false;
        }

        if (!celdasAled(registrosTemp[idxActual].x, registrosTemp[idxActual].y, sigX, sigY))
        {
            cout << "ERROR: Salto no aledaño desde (" << registrosTemp [idxActual].x << ", " << registrosTemp[idxActual].y << ") hacia (" << sigX << ", " << sigY << ")."<<endl;
            return false;
        }

        int proxIdx = posRegistro[sigX][sigY];
        if (proxIdx == -1)
        {
            cout << "ERROR: Ruta incompleta. Hueco hacia ("<<sigX<<", "<< sigY << "). "<<endl;
            return false;
        }

        if (visitadosTemp[proxIdx])
        {
            cout << "ERROR: Ciclo detectado. La ruta intenta regresar a la celda (" << sigX << ", "<< sigY << ")."<< endl;
            return false;
        }

        idxActual = proxIdx;
    }
    if (pasosRecorridos != cantidad)
    {
        cout << "ERROR: Existen "<< (cantidad - pasosRecorridos) << " celdas aisladas que no forman parte de la ruta." <<endl;
        return false;
    }

    inicializarMemoria ();
    
    for (int i = 0; i < cantidad; i++)
    {
        int x = registrosTemp[i].x;
        int y = registrosTemp [i].y;

        memoria[x][y].espera = registrosTemp[i].espera;
        memoria[x][y].soltarGranada1 = registrosTemp[i].soltarGranada1;
        memoria[x][y].soltarGranada2 = registrosTemp[i].soltarGranada2;
        memoria[x][y].ataqueKamikaze = registrosTemp[i].ataqueKamikaze;
        memoria[x][y].aterrizaje = registrosTemp[i].aterrizaje;
        memoria[x][y].despegue = registrosTemp[i].despegue;
        memoria[x][y].siguientex = registrosTemp[i].siguientex;
        memoria[x][y].siguientey = registrosTemp[i].siguientey;
        memoria[x][y].celdaOcupada = true;
    }
    
    cout << "Archivo cargado con éxito en memoria"<<endl;
    return true;
}
