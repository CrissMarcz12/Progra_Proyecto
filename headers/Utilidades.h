#ifndef PROYECTIO_BUZZIO_UTILIDADES_H
#define PROYECTIO_BUZZIO_UTILIDADES_H

#include <string>

using namespace std;

string codigoConCeros(const string& prefijo, int numero);
string montoTexto(int centimos);
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
bool fechaValida(int fecha);
bool horaValida(int hora);
int minutosAbsolutos(int fecha, int hora);
string fechaHoraTexto(int fecha, int hora);
bool convertirMontoACentimos(const string& texto, int& centimos);

#endif
