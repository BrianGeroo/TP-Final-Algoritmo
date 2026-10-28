#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include "memoria.h"

// PROTOTIPO DE CREACION DE ARCHIVOS (Operacion 3)
void CrearArchivo(const char nombreArc[]);

// PROTOTIPO DE EDICION DE ARCHIVOS (Operacion 4)
void EditarArchivo(const char nombreArc[]);

// PROTOTIPO PARA GUARDAR LA MEMORIA EN UN NUEVO ARCHIVO (Operacion 6)
void GuardarMemoriaEnArchivo(const char nombreArc[], Orden memoria[FILAS][COLUMNAS]);

#endif // ARCHIVOS_H