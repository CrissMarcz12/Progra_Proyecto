/*
 * ==============================================================
 *  Archivo:  headers/Consola.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de ejecutarAplicacion(), la funcion que maneja el menu.
 *    - Todo lo que se lee o se muestra en pantalla esta en clases/Consola.cpp;
 *      asi la logica (SistemaTransporte) queda separada de la interfaz.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_CONSOLA_H
#define PROYECTIO_BUZZIO_CONSOLA_H

#include "SistemaTransporte.h"

// Muestra el menu y atiende las opciones hasta que el usuario elige 0
void ejecutarAplicacion(SistemaTransporte& sistema);

#endif
