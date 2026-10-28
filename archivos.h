#ifndef ARCHIVOS_H
#define ARCHIVOS_H

//PROTOTIPO DE CREACION DE ARCHIVOS
void CrearArchivo(char nombreArc[],OrdenArchivo memoria[FILAS][COLUMNAS]);

//PROTOTIPO DE EDICION DE ARCHIVOS
void EditarArchivo(char nombreArc[], OrdenArchivo memoria[FILAS][COLUMNAS]);

// PROTOTIPO PARA GUARDAR LA MEMORIA EN UN NUEVO ARCHIVO
void GuardarMemoriaEnArchivo(const char nombreArc[], Orden memoria[FILAS][COLUMNAS]);

#endif //ARCHIVOS_H
