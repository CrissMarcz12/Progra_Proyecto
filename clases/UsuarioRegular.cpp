#include "UsuarioRegular.h"

#include "Constantes.h"

using namespace std;

UsuarioRegular::UsuarioRegular()
    : Usuario()
{
}

UsuarioRegular::UsuarioRegular(const string& codigo, const string& nombre, const string& dni,
                               const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, REGULAR, codigoTarjeta)
{
}

int UsuarioRegular::obtenerDescuento() const
{
    return DESCUENTOS[REGULAR];
}
