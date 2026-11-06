#include "Tarjeta.h"

#include "Constantes.h"

using namespace std;

Tarjeta::Tarjeta()
{
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

bool Tarjeta::recargar(int monto) {
    if (monto <= 0 || monto > RECARGA_MAXIMA) {
        return false;
    }

    saldoCentimos += monto;

    return true;
}

bool Tarjeta::descontar(int monto) {
    if (monto < 0 || saldoCentimos < monto) {
        return false;
    }

    saldoCentimos -= monto;

    return true;
}
