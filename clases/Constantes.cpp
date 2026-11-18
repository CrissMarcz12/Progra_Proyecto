/*
 * ==============================================================
 *  Archivo:  clases/Constantes.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - Los valores de todas las constantes declaradas en Constantes.h.
 *    - La red de transporte completa: 8 estaciones, 3 medios y sus rutas.
 *    - Tarifas base y descuentos por tipo de usuario.
 *    - Los montos estan en centimos (S/ 1.50 = 150).
 * ==============================================================
 */

#include "Constantes.h"

// ------------------------------------------------------------
// Tamanos fijos. CAPACIDAD_INICIAL es el tamano con el que nacen los
// arreglos dinamicos; RECARGA_MAXIMA es el maximo por recarga (S/ 500.00).
// ------------------------------------------------------------
const int CANT_ESTACIONES = 8;
const int CANT_MEDIOS = 3;
const int CANT_TIPOS = 3;
const int LONG_RUTA = 5;
const int CAPACIDAD_INICIAL = 4;
const int RECARGA_MAXIMA = 50000;

// ------------------------------------------------------------
// Medios de transporte. El numero es la fila/posicion en los arreglos.
// ------------------------------------------------------------
const int BUS = 0;
const int METRO = 1;
const int TRANVIA = 2;

// ------------------------------------------------------------
// Tipos de usuario. Tambien sirven como posicion en DESCUENTOS[].
// ------------------------------------------------------------
const int REGULAR = 0;
const int ESTUDIANTE = 1;
const int ADULTO_MAYOR = 2;

// ------------------------------------------------------------
// Codigos de resultado. Las operaciones del sistema devuelven uno de estos
// y Consola.cpp (mensajeError) lo convierte en un mensaje para el usuario.
// ------------------------------------------------------------
const int OK = 0;
const int ERR_USUARIO = 1;
const int ERR_TARJETA_INACTIVA = 2;
const int ERR_ESTACION = 3;
const int ERR_MISMA_ESTACION = 4;
const int ERR_MEDIO = 5;
const int ERR_RUTA = 6;
const int ERR_FECHA_HORA = 7;
const int ERR_CRONOLOGIA = 8;
const int ERR_SALDO = 9;
const int ERR_MONTO = 10;
const int ERR_DNI = 11;
const int ERR_DNI_REPETIDO = 12;

// ------------------------------------------------------------
// Estaciones: la posicion es el numero de estacion (0 = Norte ... 7 = Parque).
// ------------------------------------------------------------
const char* CODIGOS_ESTACION[] = {
        "E01", "E02", "E03", "E04", "E05", "E06", "E07", "E08"
};
const char* NOMBRES_ESTACION[] = {
        "Norte", "Central", "Mercado", "Hospital", "Terminal", "Sur", "Universidad", "Parque"
};

// ------------------------------------------------------------
// Medios, tarifas base en centimos (Bus 1.50, Metro 2.00, Tranvia 1.80),
// tipos de usuario y su descuento en % (0, 30 y 50).
// ------------------------------------------------------------
const char* NOMBRES_MEDIO[] = {"Bus", "Metro", "Tranvia"};
const int TARIFAS_BASE[] = {150, 200, 180};
const char* NOMBRES_TIPO[] = {"Regular", "Estudiante", "Adulto mayor"};
const int DESCUENTOS[] = {0, 30, 50};

// ------------------------------------------------------------
// RUTAS[medio][i]: estaciones por las que pasa cada medio, en orden.
// Fila 0 = Bus, 1 = Metro, 2 = Tranvia. El -1 es relleno porque el Metro
// y el Tranvia tienen 4 estaciones y la matriz tiene 5 columnas.
// ------------------------------------------------------------
const int RUTAS[3][5] = {
        {0, 1, 2, 3, 4},
        {5, 6, 1, 0, -1},
        {7, 6, 2, 4, -1}
};
