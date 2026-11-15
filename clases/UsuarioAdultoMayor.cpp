#include "UsuarioAdultoMayor.h"

#include "Constantes.h"

using namespace std;

UsuarioAdultoMayor::UsuarioAdultoMayor()
    : Usuario()
{
}

UsuarioAdultoMayor::UsuarioAdultoMayor(const string& codigo, const string& nombre, const string& dni,
                                       const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, ADULTO_MAYOR, codigoTarjeta)
{
}

int UsuarioAdultoMayor::obtenerDescuento() const
{
    return DESCUENTOS[ADULTO_MAYOR];
}
