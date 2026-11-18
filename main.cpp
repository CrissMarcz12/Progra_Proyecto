/*
 * ==============================================================
 *  Archivo:  main.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La funcion main(), el punto de entrada del programa.
 *    - Solo crea el sistema y le pasa el control al menu de consola.
 *      Toda la logica vive en SistemaTransporte y en Consola.
 * ==============================================================
 */

#include "headers/Consola.h"
#include "headers/SistemaTransporte.h"

// ------------------------------------------------------------
// main()
// Que hace: crea el objeto SistemaTransporte (que arranca vacio) y
//           ejecuta el menu hasta que el usuario elige 0 (Salir).
// Devuelve: 0 cuando el programa termina bien. Al salir de main se
//           destruye el sistema y se libera toda la memoria dinamica.
// ------------------------------------------------------------
int main()
{
    SistemaTransporte sistema;
    ejecutarAplicacion(sistema);
    return 0;
}
