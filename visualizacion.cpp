#include <iostream>
#include "memoria.h"
#include "visualizaciones.h"

using namespace std;

void mostrarAtaqueCargado()
{
    const int POR_PAGINA = 15;

    int xs[FILAS * COLUMNAS];
    int ys[FILAS * COLUMNAS];
    int cantidad = 0;

    // Buscar las celdas ocupadas
    for (int x = 0; x < FILAS; x++)
    {
        for (int y = 0; y < COLUMNAS; y++)
        {
            if (memoria[x][y].celdaOcupada)
            {
                xs[cantidad] = x;
                ys[cantidad] = y;
                cantidad++;
            }
        }
    }

    if (cantidad == 0)
    {
        cout << "No hay ningun ataque cargado en memoria." << endl;
        return;
    }

    int pagina = 0;
    int totalPaginas = (cantidad + POR_PAGINA - 1) / POR_PAGINA;
    char opcion;

    do
    {
        int inicio = pagina * POR_PAGINA;
        int fin = inicio + POR_PAGINA;

        if (fin > cantidad)
            fin = cantidad;

        cout << "\n===== ATAQUE CARGADO =====" << endl;
        cout << "Pagina " << pagina + 1
             << " de " << totalPaginas << endl;
        cout << "Registros encontrados: " << cantidad << endl;

        cout << "\nX\tY\tEspera\tGranada1\tGranada2"
             << "\tKamikaze\tAterrizaje\tDespegue"
             << "\tSig.X\tSig.Y" << endl;

        for (int i = inicio; i < fin; i++)
        {
            int x = xs[i];
            int y = ys[i];

            Orden &o = memoria[x][y];

            cout << x << "\t"
                 << y << "\t"
                 << o.espera << "\t"
                 << o.soltarGranada1 << "\t\t"
                 << o.soltarGranada2 << "\t\t"
                 << o.ataqueKamikaze << "\t\t"
                 << o.aterrizaje << "\t\t"
                 << o.despegue << "\t\t"
                 << o.siguientex << "\t"
                 << o.siguientey << endl;
        }

        cout << "\nN: siguiente pagina";
        cout << "\nA: pagina anterior";
        cout << "\nS: salir";
        cout << "\nOpcion: ";
        cin >> opcion;

        if ((opcion == 'N' || opcion == 'n')
            && pagina < totalPaginas - 1)
        {
            pagina++;
        }
        else if ((opcion == 'A' || opcion == 'a')
                 && pagina > 0)
        {
            pagina--;
        }

    } while (opcion != 'S' && opcion != 's');
}

void corregirRegistroMemoria()
{
    int x, y;

    cout << "\n===== CORREGIR REGISTRO EN MEMORIA =====" << endl;
    cout << "Ingrese la coordenada X: ";
    cin >> x;

    cout << "Ingrese la coordenada Y: ";
    cin >> y;

    if (!estaEnRango(x, y))
    {
        cout << "ERROR: Las coordenadas estan fuera de rango." << endl;
        return;
    }

    if (!memoria[x][y].celdaOcupada)
    {
        cout << "ERROR: No existe un registro en esa celda." << endl;
        return;
    }

    Orden &o = memoria[x][y];

    cout << "\n===== REGISTRO ACTUAL =====" << endl;
    cout << "Coordenadas: (" << x << ", " << y << ")" << endl;
    cout << "Espera: " << o.espera << endl;
    cout << "Granada 1: " << o.soltarGranada1 << endl;
    cout << "Granada 2: " << o.soltarGranada2 << endl;
    cout << "Kamikaze: " << o.ataqueKamikaze << endl;
    cout << "Aterrizaje: " << o.aterrizaje << endl;
    cout << "Despegue: " << o.despegue << endl;
    cout << "Siguiente X: " << o.siguientex << endl;
    cout << "Siguiente Y: " << o.siguientey << endl;

    char confirmar;
    cout << "\nDesea modificar este registro? (s/n): ";
    cin >> confirmar;

    if (confirmar != 's' && confirmar != 'S')
    {
        cout << "Modificacion cancelada." << endl;
        return;
    }

    unsigned int espera;
    int g1, g2, kamikaze, aterrizaje, despegue;
    int sx, sy;

    cout << "\nIngrese la nueva espera: ";
    cin >> espera;

    cout << "Soltar granada 1? (0=no, 1=si): ";
    cin >> g1;

    cout << "Soltar granada 2? (0=no, 1=si): ";
    cin >> g2;

    cout << "Ataque kamikaze? (0=no, 1=si): ";
    cin >> kamikaze;

    cout << "Aterrizaje? (0=no, 1=si): ";
    cin >> aterrizaje;

    cout << "Despegue? (0=no, 1=si): ";
    cin >> despegue;

    cout << "Siguiente X (-1 si no hay siguiente): ";
    cin >> sx;

    cout << "Siguiente Y (-1 si no hay siguiente): ";
    cin >> sy;

    if ((g1 != 0 && g1 != 1) ||
        (g2 != 0 && g2 != 1) ||
        (kamikaze != 0 && kamikaze != 1) ||
        (aterrizaje != 0 && aterrizaje != 1) ||
        (despegue != 0 && despegue != 1))
    {
        cout << "ERROR: Las acciones deben ser 0 o 1." << endl;
        return;
    }

    bool sinSiguiente = (sx == POS_NULA && sy == POS_NULA);

    if (!sinSiguiente && !estaEnRango(sx, sy))
    {
        cout << "ERROR: La siguiente posicion no es valida." << endl;
        return;
    }

    if ((sx == POS_NULA) != (sy == POS_NULA))
    {
        cout << "ERROR: Ambas coordenadas siguientes deben ser -1 o ambas deben ser validas." << endl;
        return;
    }

    if (despegue && (g1 || g2 || kamikaze))
    {
        cout << "ERROR: El despegue no puede tener ataques." << endl;
        return;
    }

    if (aterrizaje && kamikaze)
    {
        cout << "ERROR: No puede haber aterrizaje y kamikaze en el mismo registro." << endl;
        return;
    }

    o.espera = espera;
    o.soltarGranada1 = g1;
    o.soltarGranada2 = g2;
    o.ataqueKamikaze = kamikaze;
    o.aterrizaje = aterrizaje;
    o.despegue = despegue;
    o.siguientex = sx;
    o.siguientey = sy;

    cout << "\nRegistro modificado correctamente." << endl;
}