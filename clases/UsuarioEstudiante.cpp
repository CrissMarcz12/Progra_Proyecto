#include "UsuarioEstudiante.h"

#include "Constantes.h"

using namespace std;

UsuarioEstudiante::UsuarioEstudiante()
    : Usuario()
{
}

UsuarioEstudiante::UsuarioEstudiante(const string& codigo, const string& nombre, const string& dni,
                                     const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, ESTUDIANTE, codigoTarjeta)
{
}

int UsuarioEstudiante::obtenerDescuento() const
{
    return DESCUENTOS[ESTUDIANTE];
}
