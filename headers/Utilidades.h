#ifndef PROYECTIO_BUZZIO_UTILIDADES_H
#define PROYECTIO_BUZZIO_UTILIDADES_H

#include <string>

std::string codigoConCeros(const std::string& prefijo, int numero);
std::string montoTexto(int centimos);
bool esBisiesto(int anio);
int diasDelMes(int mes, int anio);
bool fechaValida(int fecha);
bool horaValida(int hora);
int minutosAbsolutos(int fecha, int hora);
std::string fechaHoraTexto(int fecha, int hora);
bool convertirMontoACentimos(const std::string& texto, int& centimos);

#endif
