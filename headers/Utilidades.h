/*
 * ==============================================================
 *  Archivo:  headers/Utilidades.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - Funciones de apoyo que no pertenecen a ninguna clase:
 *      codigos con ceros, formato de montos, validacion de fecha y hora,
 *      conversion a minutos y lectura de montos escritos con punto decimal.
 *    - La implementacion esta en clases/Utilidades.cpp.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_UTILIDADES_H
#define PROYECTIO_BUZZIO_UTILIDADES_H

#include <string>

using namespace std;

// Arma codigos como U001 o T012
string codigoConCeros(const string& prefijo, int numero);

// Convierte centimos a texto: 150 -> "S/ 1.50"
string montoTexto(int centimos);

// Validaciones de fechas (formato AAAAMMDD) y horas (formato HHMM)
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
bool fechaValida(int fecha);
bool horaValida(int hora);

// Convierte fecha y hora a minutos para comparar viajes
int minutosAbsolutos(int fecha, int hora);

// Muestra fecha y hora como "05/10/2026 07:30"
string fechaHoraTexto(int fecha, int hora);

// Lee un monto escrito como "10.50" y lo pasa a centimos
bool convertirMontoACentimos(const string& texto, int& centimos);

#endif
