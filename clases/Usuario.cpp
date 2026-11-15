#include "Usuario.h"

#include "Constantes.h"

using namespace std;

Usuario::Usuario()
{
    // El usuario por defecto permite reservar espacio en el arreglo dinamico.
    codigo = "";
    nombre = "";
    dni = "";
    tipo = REGULAR;
}

Usuario::Usuario(const string& nuevoCodigo, const string& nuevoNombre, const string& nuevoDni, int nuevoTipo,
                 const string& codigoTarjeta)
{
    codigo = nuevoCodigo;
    nombre = nuevoNombre;
    dni = nuevoDni;
    tipo = nuevoTipo;
    tarjeta = Tarjeta(codigoTarjeta);
}

const string& Usuario::obtenerCodigo() const
{
    return codigo;
}

const string& Usuario::obtenerNombre() const
{
    return nombre;
}

const string& Usuario::obtenerDni() const
{
    return dni;
}

int Usuario::obtenerTipo() const
{
    return tipo;
}

Tarjeta& Usuario::obtenerTarjeta()
{
    return tarjeta;
}

const Tarjeta& Usuario::obtenerTarjeta() const
{
    return tarjeta;
}

Usuario::~Usuario()
{
}
