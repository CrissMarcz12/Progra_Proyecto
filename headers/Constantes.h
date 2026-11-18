/*
 * ==============================================================
 *  Archivo:  headers/Constantes.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - Las declaraciones (extern) de todas las constantes del sistema.
 *    - Los valores reales estan en clases/Constantes.cpp.
 *    - Cualquier archivo que incluya este .h puede usarlas.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_CONSTANTES_H
#define PROYECTIO_BUZZIO_CONSTANTES_H

// Tamanos fijos de la red y de los arreglos
extern const int CANT_ESTACIONES;
extern const int CANT_MEDIOS;
extern const int CANT_TIPOS;
extern const int LONG_RUTA;
extern const int CAPACIDAD_INICIAL;
extern const int RECARGA_MAXIMA;

// Indices de los medios de transporte (se usan como posicion en los arreglos)
extern const int BUS;
extern const int METRO;
extern const int TRANVIA;

// Indices de los tipos de usuario
extern const int REGULAR;
extern const int ESTUDIANTE;
extern const int ADULTO_MAYOR;

// Codigos que devuelven las operaciones: OK o el error que ocurrio
extern const int OK;
extern const int ERR_USUARIO;
extern const int ERR_TARJETA_INACTIVA;
extern const int ERR_ESTACION;
extern const int ERR_MISMA_ESTACION;
extern const int ERR_MEDIO;
extern const int ERR_RUTA;
extern const int ERR_FECHA_HORA;
extern const int ERR_CRONOLOGIA;
extern const int ERR_SALDO;
extern const int ERR_MONTO;
extern const int ERR_DNI;
extern const int ERR_DNI_REPETIDO;

// Datos fijos de la red: estaciones, medios, tarifas, descuentos y rutas
extern const char* CODIGOS_ESTACION[];
extern const char* NOMBRES_ESTACION[];
extern const char* NOMBRES_MEDIO[];
extern const int TARIFAS_BASE[];
extern const char* NOMBRES_TIPO[];
extern const int DESCUENTOS[];
extern const int RUTAS[3][5];

#endif
