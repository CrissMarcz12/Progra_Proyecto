/*
 * ==============================================================
 *  Archivo:  clases/Tarjeta.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de la clase Tarjeta.
 *    - Recarga con validacion, descuento sin saldo negativo,
 *      cambio de estado y la sobrecarga de los operadores += y <<.
 *    - Todos los montos estan en centimos.
 * ==============================================================
 */

#include "Tarjeta.h"

#include "Constantes.h"
#include "Utilidades.h"

using namespace std;

// ------------------------------------------------------------
// Tarjeta()  -- constructor por defecto
// Que hace: crea una tarjeta sin codigo, con saldo 0 y activa.
//           Se usa cuando el Usuario se crea antes de asignarle su tarjeta.
// ------------------------------------------------------------
Tarjeta::Tarjeta()
{
    // Una tarjeta nueva comienza sin saldo y queda activa.
    codigo = "";
    saldoCentimos = 0;
    activa = true;
}

// ------------------------------------------------------------
// Tarjeta(nuevoCodigo)  -- constructor con codigo
// Que hace: crea la tarjeta con su codigo (ej. T001), saldo 0 y activa.
// ------------------------------------------------------------
Tarjeta::Tarjeta(const string& nuevoCodigo)
{
    codigo = nuevoCodigo;
    saldoCentimos = 0;
    activa = true;
}

// Devuelve el codigo de la tarjeta (por referencia constante, sin copiarlo).
const string& Tarjeta::obtenerCodigo() const
{
    return codigo;
}

// Devuelve el saldo actual en centimos.
int Tarjeta::consultarSaldo() const
{
    return saldoCentimos;
}

// Devuelve true si la tarjeta esta activa.
bool Tarjeta::estaActiva() const
{
    return activa;
}

// Cambia el estado: true la activa, false la desactiva.
void Tarjeta::cambiarEstado(bool nuevoEstado)
{
    activa = nuevoEstado;
}

// ------------------------------------------------------------
// recargar(monto)
// Que hace: valida el monto y, si es correcto, lo suma con el operador +=.
// Regla:    0 < monto <= RECARGA_MAXIMA (50000 centimos = S/ 500.00).
//           El limite es por cada recarga, no para el saldo total.
// Devuelve: true si recargo, false si el monto no es valido.
// ------------------------------------------------------------
bool Tarjeta::recargar(int monto)
{
    if (monto <= 0 || monto > RECARGA_MAXIMA) {
        return false;
    }

    *this += monto;

    return true;
}

// ------------------------------------------------------------
// operator+=(monto)  -- sobrecarga de operador
// Que hace: suma el monto al saldo.
// Devuelve: la misma tarjeta (*this) para poder encadenar operaciones.
// ------------------------------------------------------------
Tarjeta& Tarjeta::operator+=(int monto)
{
    saldoCentimos += monto;

    return *this;
}

// ------------------------------------------------------------
// operator<<(salida, tarjeta)  -- sobrecarga de operador (friend)
// Que hace: escribe la tarjeta en pantalla: "T001 | S/ 15.20 | Activa".
// Devuelve: el mismo flujo, para encadenar: cout << a << b;
// ------------------------------------------------------------
ostream& operator<<(ostream& salida, const Tarjeta& tarjeta)
{
    salida << tarjeta.codigo << " | " << montoTexto(tarjeta.saldoCentimos) << " | ";

    if (tarjeta.activa) {
        salida << "Activa";
    } else {
        salida << "Inactiva";
    }

    return salida;
}

// ------------------------------------------------------------
// descontar(monto)
// Que hace: resta la tarifa del saldo.
// Devuelve: false si el monto es negativo o si el saldo no alcanza;
//           en ese caso el saldo no cambia (nunca queda negativo).
// ------------------------------------------------------------
bool Tarjeta::descontar(int monto)
{
    if (monto < 0 || saldoCentimos < monto) {
        return false;
    }

    saldoCentimos -= monto;

    return true;
}
