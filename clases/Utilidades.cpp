/*
 * ==============================================================
 *  Archivo:  clases/Utilidades.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - Funciones auxiliares para textos, fechas, horas y montos.
 *    - Las usan SistemaTransporte, Viaje, Tarjeta y Consola.
 * ==============================================================
 */

#include "Utilidades.h"

#include <iomanip>
#include <sstream>

using namespace std;

// ------------------------------------------------------------
// codigoConCeros(prefijo, numero)
// Que hace: une el prefijo con el numero rellenado a 3 cifras.
// Ejemplo:  ("U", 7) -> "U007".
// ------------------------------------------------------------
string codigoConCeros(const string& prefijo, int numero) {
    ostringstream salida;
    salida << prefijo << setw(3) << setfill('0') << numero;
    return salida.str();
}

// ------------------------------------------------------------
// montoTexto(centimos)
// Que hace: convierte un monto en centimos a texto con soles.
// Ejemplo:  1307 -> "S/ 13.07". Usa division entera y resto (% 100).
// ------------------------------------------------------------
string montoTexto(int centimos) {
    ostringstream salida;
    salida << "S/ " << centimos / 100 << '.' << setw(2) << setfill('0') << centimos % 100;
    return salida.str();
}

// ------------------------------------------------------------
// esBisiesto(anio)
// Que hace: aplica la regla del calendario: divisible entre 400, o entre 4
//           pero no entre 100. Devuelve true si el anio es bisiesto.
// ------------------------------------------------------------
bool esBisiesto(int anio) {
    return (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
}

// ------------------------------------------------------------
// diasDelMes(mes, anio)
// Que hace: devuelve cuantos dias tiene el mes (29 en febrero bisiesto).
//           Si el mes no existe devuelve 0.
// ------------------------------------------------------------
int diasDelMes(int mes, int anio) {
    const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) return 0;
    if (mes == 2 && esBisiesto(anio)) return 29;
    return dias[mes - 1];
}

// ------------------------------------------------------------
// fechaValida(fecha)
// Que hace: separa AAAAMMDD en anio, mes y dia y revisa que existan.
// Ejemplo:  20260231 -> false (no hay 31 de febrero).
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// horaValida(hora)
// Que hace: separa HHMM en horas y minutos y revisa 0-23 y 0-59.
// Ejemplo:  2400 -> false, 2359 -> true.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// minutosAbsolutos(fecha, hora)
// Que hace: cuenta los minutos desde el 01/01/2000 hasta esa fecha y hora.
// Para que: restar dos viajes da los minutos entre ellos, incluso si
//           cruzan la medianoche. Asi se revisa la regla de 30 minutos.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// fechaHoraTexto(fecha, hora)
// Que hace: arma el texto "DD/MM/AAAA HH:MM" para mostrar en el historial.
// ------------------------------------------------------------
string fechaHoraTexto(int fecha, int hora) {
    ostringstream salida;
    salida << setfill('0') << setw(2) << fecha % 100 << '/' << setw(2) << (fecha / 100) % 100
           << '/' << setw(4) << fecha / 10000 << " " << setw(2) << hora / 100 << ':' << setw(2) << hora % 100;
    return salida.str();
}

// ------------------------------------------------------------
// convertirMontoACentimos(texto, centimos)
// Que hace: lee un monto escrito por el usuario ("10", "10.5" o "10.50")
//           caracter por caracter y lo guarda en centimos (por referencia).
// Devuelve: false si tiene letras, mas de un punto, mas de 2 decimales
//           o mas de 4 cifras enteras. Asi se evita usar double.
// ------------------------------------------------------------
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
