#include <iostream>
#include <conio.h>
#include <stdlib.h>

#include "memoria.h"
#include "operaciones.h"

using namespace std;

int main()
{
    inicializarMemoria();

    int opcion;
    char ruta[260];

                                                                //MENU DE OPCIONES
    cout << "1. Cargar archivo de ataque en memoria" << endl;
    cout << "2. Mostrar ataque cargado" << endl;
    cout << "3. Crear un archivo de ataque nuevo" << endl;
    cout << "4. Corregir un registro del archivo" << endl;
    cout << "5. Corregir un registro en memoria" << endl;
    cout << "6. Guardar memoria en un archivo nuevo" << endl;
    cout << "7. Visualizar un archivo de ataque en html" << endl<<endl;
        cin>>opcion;

        switch(opcion){         //SELECCION DE OPCIONES
            case 1:
                    cout<<"---CARGAR ARCHIVO DE ATAQUE---"<<endl;
                    cout << "Ingrese la ruta y nombre del archivo binario"<<endl;
                    cin>>ruta;

                    if (cargarArchivoEnMemoria(ruta))
                        cout << "El archivo fue validado y cargado con éxito"<<endl; 
                break;

            case 2:
                    cout<<"Opcion aun no programada";
                break;

            case 3:
                    cout<<"Opcion aun no programada";
                break;

            case 4:
                    cout<<"Opcion aun no programada";
                break;

            case 5:
                    cout<<"Opcion aun no programada";
                break;

            case 6:
                    cout<<"Opcion aun no programada";
                break;

            case 7:
                    cout<<"Opcion aun no programada";
                break;
        }

    getch();
    return 0;
}
