#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

#include "memoria.h"
#include "operaciones.h"
#include "archivos.h"

using namespace std;

void CrearArchivo(char nombreArc[],OrdenArchivo memoria[FILAS][COLUMNAS])
{

    FILE*f1;

    if(f1=fopen(nombreArc, "wb")){

     char queres = 's';

    //SE MODIFICAN LOS REGISTROS, SI QUIERES EDITAR OTRO SE REINICIA EL CICLO
        while (queres == 's' || queres == 'S')
        {
            OrdenArchivo orden;

        cout<<"Seleccione los registros que quiere modificar"<<endl<<endl;

                        cout<<"espera: ";
            cin>>orden.espera;
                        cout<<"coordenada x: ";
            cin>>orden.x;
                        cout<<"coordenada y: ";
            cin>>orden.y;
                        cout<<"soltar granada 1?: ";
            cin>>orden.soltarGranada1;
                        cout<<"soltar granada 2?: ";
            cin>>orden.soltarGranada2;
                        cout<<"Ataque Kamikaze?: ";
            cin>>orden.ataqueKamikaze;
                        cout<<"Aterrizar?: ";
            cin>>orden.aterrizaje;
                        cout<<"Despegar?: ";
            cin>>orden.despegue;
                        cout<<"Siguiente coordenada x: ";
            cin>>orden.siguientex;
                        cout<<"Siguiente coordenada y: ";
            cin>>orden.siguientey;
            cout<<endl<<endl;

                memoria[orden.x][orden.y] = orden;
    //SE ALMACENA EL STRUCT EN LA POSICION DE LA GRILLA

    fwrite(&orden, sizeof(OrdenArchivo), 1, f1);

            cout << endl;
            cout << "Deseas agregar otra orden? (s/n): ";
            cin >> queres;
            cout << endl;
            cout<<"*******************************************"<<endl;
        }

        fclose(f1);
            cout<<"FINALIZO EL GUARDADO"<<endl<<endl;
        }

    else{
        cout<<"ERROR";
    }
    return;
}

void EditarArchivo(char nombreArc[], OrdenArchivo memoria[FILAS][COLUMNAS]){

    FILE* f2;
    int cordx, cordy;
    char era = 'n';
    int posicion = 0;

    OrdenArchivo coordenada;
    OrdenArchivo orden;

    if(f2 = fopen(nombreArc, "r+b")){

        while(era != 's' && era != 'S'){

        cout<<"Elija las coordenadas a editar:"<<endl;
        cout<<"Coordenada X: ";
        cin>>cordx;
        cout<<"Coordenada Y: ";
        cin>>cordy;

            coordenada = memoria[cordx][cordy]; //DEVUELVE LOS DATOS DE LA POSICION AL STRUCT EDITABLE

        cout<<endl;

            cout << "========== REGISTRO ==========" << endl;
            cout << "X: " << coordenada.x << endl;
            cout << "Y: " << coordenada.y << endl;
            cout << "Espera: " << coordenada.espera << endl;
            cout << "Soltar Granada 1: " << coordenada.soltarGranada1 << endl;
            cout << "Soltar Granada 2: " << coordenada.soltarGranada2 << endl;
            cout << "Ataque Kamikaze: " << coordenada.ataqueKamikaze << endl;
            cout << "Aterrizaje: " << coordenada.aterrizaje << endl;
            cout << "Despegue: " << coordenada.despegue << endl;
            cout << "Siguiente X: " << coordenada.siguientex << endl;
            cout << "Siguiente Y: " << coordenada.siguientey << endl;
            cout << "===============================" << endl;

            cout<<"Esa es la coordenada correcta?(s/n): ";
            cin>>era;
            cout<<endl<<endl;
        }

    //BUSCA LA POSICION DEL ARCHIVO EN MEMORIA
        posicion =0;

        while(fread(&orden, sizeof(OrdenArchivo), 1, f2) == 1){

            if(orden.x == cordx && orden.y == cordy){
                break;
            }
            posicion++;
        }
                    cout << "========== REGISTRO EDITABLE ==========" << endl;
            cout << "X: ";
                cin>>coordenada.x;
            cout << "Y: ";
                cin>>coordenada.y;
            cout << "Espera: ";
                cin>>coordenada.espera;
            cout << "Soltar Granada 1: ";
                cin>>coordenada.soltarGranada1;
            cout << "Soltar Granada 2: ";
                cin>>coordenada.soltarGranada2;
            cout << "Ataque Kamikaze: ";
                cin>>coordenada.ataqueKamikaze;
            cout << "Aterrizaje: ";
                cin>>coordenada.aterrizaje;
            cout << "Despegue: ";
                cin>>coordenada.despegue;
            cout << "Siguiente X: ";
                cin>>coordenada.siguientex;
            cout << "Siguiente Y: ";
                cin>>coordenada.siguientey;
            cout << "===============================" << endl;

                memoria[coordenada.x][coordenada.y] = coordenada;

        // Volver al comienzo del registro encontrado
        fseek(f2, posicion * sizeof(OrdenArchivo), SEEK_SET);

        // Reemplazar el registro
        fwrite(&coordenada, sizeof(OrdenArchivo), 1, f2);

        cout << endl << "Registro modificado correctamente." << endl;

        fclose(f2);
    }

    else{
        cout<<"ERROR 2";
    }
}
