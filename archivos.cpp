#include <iostream>
#include <cstdio>
#include "memoria.h"
#include "archivos.h"

using namespace std;

void CrearArchivo(const char nombreArc[])
{
    FILE* f1 = fopen(nombreArc, "wb");
    if (f1 == NULL)
    {
        cout << "ERROR: No se pudo crear el archivo." << endl;
        return;
    }

    char queres = 's';
    while (queres == 's' || queres == 'S')
    {
        OrdenArchivo orden;

        cout << "\n--- Ingresar Datos de la Orden ---" << endl;
        cout << "Coordenada X: "; cin >> orden.x;
        cout << "Coordenada Y: "; cin >> orden.y;
        cout << "Espera: "; cin >> orden.espera;
        cout << "Soltar granada 1? (0=no, 1=si): "; cin >> orden.soltarGranada1;
        cout << "Soltar granada 2? (0=no, 1=si): "; cin >> orden.soltarGranada2;
        cout << "Ataque Kamikaze? (0=no, 1=si): "; cin >> orden.ataqueKamikaze;
        cout << "Aterrizaje? (0=no, 1=si): "; cin >> orden.aterrizaje;
        cout << "Despegue? (0=no, 1=si): "; cin >> orden.despegue;
        cout << "Siguiente coordenada X (-1 si es fin): "; cin >> orden.siguientex;
        cout << "Siguiente coordenada Y (-1 si es fin): "; cin >> orden.siguientey;

        fwrite(&orden, sizeof(OrdenArchivo), 1, f1);

        cout << "\nDeseas agregar otra orden? (s/n): ";
        cin >> queres;
    }

    fclose(f1);
    cout << "\nArchivo creado y guardado con exito.\n" << endl;
}

void EditarArchivo(const char nombreArc[])
{
    FILE* f2 = fopen(nombreArc, "r+b");
    if (f2 == NULL)
    {
        cout << "ERROR: No se pudo abrir el archivo para edicion." << endl;
        return;
    }

    int cordx, cordy;
    cout << "Elija las coordenadas a editar en el archivo:" << endl;
    cout << "Coordenada X: "; cin >> cordx;
    cout << "Coordenada Y: "; cin >> cordy;

    OrdenArchivo orden;
    int posicion = 0;
    bool encontrado = false;

    // Buscar el registro directamente en el archivo binario
    while (fread(&orden, sizeof(OrdenArchivo), 1, f2) == 1)
    {
        if (orden.x == cordx && orden.y == cordy)
        {
            encontrado = true;
            break;
        }
        posicion++;
    }

    if (!encontrado)
    {
        cout << "ERROR: No se encontro ningun registro con esas coordenadas en el archivo." << endl;
        fclose(f2);
        return;
    }

    cout << "\n========== REGISTRO ENCONTRADO ==========" << endl;
    cout << "X: " << orden.x << " | Y: " << orden.y << endl;
    cout << "Espera: " << orden.espera << endl;
    cout << "Granada 1: " << orden.soltarGranada1 << " | Granada 2: " << orden.soltarGranada2 << endl;
    cout << "Kamikaze: " << orden.ataqueKamikaze << " | Aterrizaje: " << orden.aterrizaje << " | Despegue: " << orden.despegue << endl;
    cout << "Siguiente X: " << orden.siguientex << " | Siguiente Y: " << orden.siguientey << endl;
    cout << "=========================================" << endl;

    char confirmar;
    cout << "Desea modificar este registro? (s/n): ";
    cin >> confirmar;

    if (confirmar != 's' && confirmar != 'S')
    {
        cout << "Modificacion cancelada." << endl;
        fclose(f2);
        return;
    }

    cout << "\nIngrese los nuevos valores:" << endl;
    cout << "Nueva Espera: "; cin >> orden.espera;
    cout << "Soltar Granada 1? (0/1): "; cin >> orden.soltarGranada1;
    cout << "Soltar Granada 2? (0/1): "; cin >> orden.soltarGranada2;
    cout << "Ataque Kamikaze? (0/1): "; cin >> orden.ataqueKamikaze;
    cout << "Aterrizaje? (0/1): "; cin >> orden.aterrizaje;
    cout << "Despegue? (0/1): "; cin >> orden.despegue;
    cout << "Siguiente X: "; cin >> orden.siguientex;
    cout << "Siguiente Y: "; cin >> orden.siguientey;

    // Volver a la posicion exacta del registro
    fseek(f2, posicion * sizeof(OrdenArchivo), SEEK_SET);
    fwrite(&orden, sizeof(OrdenArchivo), 1, f2);

    cout << "\nRegistro en archivo modificado correctamente." << endl;
    fclose(f2);
}

void GuardarMemoriaEnArchivo(const char nombreArc[], Orden memoria[FILAS][COLUMNAS])
{
    FILE* f3 = fopen(nombreArc, "wb");
    if (f3 == NULL)
    {
        cout << "ERROR: No se pudo crear el archivo de destino." << endl;
        return;
    }

    int registrosGuardados = 0;

    for (int x = 0; x < FILAS; x++)
    {
        for (int y = 0; y < COLUMNAS; y++)
        {
            if (memoria[x][y].celdaOcupada)
            {
                OrdenArchivo reg;
                reg.x = x;
                reg.y = y;
                reg.espera = memoria[x][y].espera;
                reg.soltarGranada1 = memoria[x][y].soltarGranada1;
                reg.soltarGranada2 = memoria[x][y].soltarGranada2;
                reg.ataqueKamikaze = memoria[x][y].ataqueKamikaze;
                reg.aterrizaje = memoria[x][y].aterrizaje;
                reg.despegue = memoria[x][y].despegue;
                reg.siguientex = memoria[x][y].siguientex;
                reg.siguientey = memoria[x][y].siguientey;

                fwrite(&reg, sizeof(OrdenArchivo), 1, f3);
                registrosGuardados++;
            }
        }
    }

    fclose(f3);
    cout << "\nArchivo '" << nombreArc << "' creado con exito." << endl;
    cout << "Se guardaron " << registrosGuardados << " registros en total." << endl;
}