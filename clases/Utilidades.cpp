#include "Utilidades.h"

#include <iomanip>
#include <sstream>

using namespace std;

string codigoConCeros(const string& prefijo, int numero) {
    ostringstream salida;
    salida << prefijo << setw(3) << setfill('0') << numero;
    return salida.str();
}

string montoTexto(int centimos) {
    ostringstream salida;
    salida << "S/ " << centimos / 100 << '.' << setw(2) << setfill('0') << centimos % 100;
    return salida.str();
}

bool esBisiesto(int anio) {
    return (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
}

int diasDelMes(int mes, int anio) {
    const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) return 0;
    if (mes == 2 && esBisiesto(anio)) return 29;
    return dias[mes - 1];
}

bool fechaValida(int fecha) {
    int anio = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;
    if (anio < 2000 || mes < 1 || mes > 12) {
        return false;
    }

    if (dia < 1 || dia > diasDelMes(mes, anio)) {
        return false;
    }

    return true;
}

bool horaValida(int hora) {
    int horas = hora / 100;
    int minutos = hora % 100;
    if (horas < 0 || horas > 23) {
        return false;
    }

    if (minutos < 0 || minutos > 59) {
        return false;
    }

    return true;
}

int minutosAbsolutos(int fecha, int hora) {
    int anio = fecha / 10000;
    int mes = (fecha / 100) % 100;
    int dia = fecha % 100;
    int dias = 0;
    for (int a = 2000; a < anio; ++a) dias += esBisiesto(a) ? 366 : 365;
    for (int m = 1; m < mes; ++m) dias += diasDelMes(m, anio);
    dias += dia - 1;
    return dias * 24 * 60 + (hora / 100) * 60 + hora % 100;
}

string fechaHoraTexto(int fecha, int hora) {
    ostringstream salida;
    salida << setfill('0') << setw(2) << fecha % 100 << '/' << setw(2) << (fecha / 100) % 100
           << '/' << setw(4) << fecha / 10000 << " " << setw(2) << hora / 100 << ':' << setw(2) << hora % 100;
    return salida.str();
}

bool convertirMontoACentimos(const string& texto, int& centimos) {
    if (texto.empty()) return false;
    int punto = -1;
    for (int i = 0; i < (int) texto.length(); ++i) {
        if (texto[i] == '.') {
            if (punto != -1) return false;
            punto = i;
        } else if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    string enteros = punto == -1 ? texto : texto.substr(0, punto);
    string decimales = punto == -1 ? "" : texto.substr(punto + 1);
    if (enteros.empty() || enteros.length() > 4 || decimales.length() > 2) return false;

    int parteEntera = 0;
    for (char c : enteros) parteEntera = parteEntera * 10 + (c - '0');
    int parteDecimal = 0;
    if (decimales.length() == 1) parteDecimal = (decimales[0] - '0') * 10;
    if (decimales.length() == 2) parteDecimal = (decimales[0] - '0') * 10 + (decimales[1] - '0');
    centimos = parteEntera * 100 + parteDecimal;
    return true;
}
