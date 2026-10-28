#include <iostream>
#include <cstdlib>

#include "memoria.h"
#include "operaciones.h"
#include "archivos.h"
#include "visualizaciones.h"
#include "html.h"

using namespace std;

int main()
{
    // 1. Inicializamos la memoria en blanco antes de arrancar
    inicializarMemoria();

    int opcion;
    char ruta[260];

    // 2. Bucle principal del menú
    do
    {
        cout << "\n==================================================\n";
        cout << "          SISTEMA DE GUIA DE APOYO - DRON         \n";
        cout << "==================================================\n";
        cout << "1. Cargar archivo de ataque en memoria\n";
        cout << "2. Mostrar ataque cargado\n";
        cout << "3. Crear un archivo de ataque nuevo\n";
        cout << "4. Corregir un registro del archivo\n";
        cout << "5. Corregir un registro en memoria\n";
        cout << "6. Guardar memoria en un archivo nuevo\n";
        cout << "7. Visualizar un archivo de ataque en html\n";
        cout << "8. Salir del programa\n";
        cout << "==================================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
            case 1:
                cout << "\n--- CARGAR ARCHIVO DE ATAQUE ---\n";
                cout << "Ingrese la ruta y nombre del archivo binario (ej: ataque.dat): ";
                cin >> ruta;
                cargarArchivoEnMemoria(ruta);
                break;

            case 2:
                mostrarAtaqueCargado();
                break;

            case 3:
                cout << "\n--- CREAR ARCHIVO DE ATAQUE NUEVO ---\n";
                cout << "Ingrese la ruta y nombre del archivo a crear: ";
                cin >> ruta;
                CrearArchivo(ruta, memoria);
                break;

            case 4:
                cout << "\n--- CORREGIR REGISTRO DEL ARCHIVO ---\n";
                cout << "Ingrese la ruta y nombre del archivo a editar: ";
                cin >> ruta;
                EditarArchivo(ruta, memoria);
                break;

            case 5:
                corregirRegistroMemoria();
                break;

            case 6:
                cout << "\n--- GUARDAR MEMORIA A DISCO ---\n";
                cout << "Ingrese nombre del nuevo archivo binario (ej: backup.dat): ";
                cin >> ruta;
                GuardarMemoriaEnArchivo(ruta, memoria);
                break;

            case 7:
                cout << "\n--- EXPORTAR A HTML ---\n";
                cout << "Ingrese nombre del archivo web (ej: mapa.html): ";
                cin >> ruta;
                visualizarEnHTML(ruta, memoria);
                break;

            case 8:
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion invalida. Por favor, intente nuevamente.\n";
                break;
        }

    } while (opcion != 8);

    return 0;
}
