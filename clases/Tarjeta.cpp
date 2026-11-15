#include "Tarjeta.h"

#include "Constantes.h"
#include "Utilidades.h"

using namespace std;

Tarjeta::Tarjeta()
{
    // Una tarjeta nueva comienza sin saldo y queda activa.
    codigo = "";
    saldoCentimos = 0;
    activa = true;
}

Tarjeta::Tarjeta(const string& nuevoCodigo)
{
    codigo = nuevoCodigo;
    saldoCentimos = 0;
    activa = true;
}

const string& Tarjeta::obtenerCodigo() const
{
    return codigo;
}

int Tarjeta::consultarSaldo() const
{
    return saldoCentimos;
}

bool Tarjeta::estaActiva() const
{
    return activa;
}

void Tarjeta::cambiarEstado(bool nuevoEstado)
{
    activa = nuevoEstado;
}

bool Tarjeta::recargar(int monto)
{
    if (monto <= 0 || monto > RECARGA_MAXIMA) {
        return false;
    }

    *this += monto;

    return true;
}

Tarjeta& Tarjeta::operator+=(int monto)
{
    saldoCentimos += monto;

    return *this;
}

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

bool Tarjeta::descontar(int monto)
{
    if (monto < 0 || saldoCentimos < monto) {
        return false;
    }

    saldoCentimos -= monto;

    return true;
}
