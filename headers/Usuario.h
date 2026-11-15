#ifndef PROYECTIO_BUZZIO_USUARIO_H
#define PROYECTIO_BUZZIO_USUARIO_H

#include "Tarjeta.h"

#include <string>

using namespace std;

class Usuario {
private:
    string codigo;
    string nombre;
    string dni;
    int tipo;
    Tarjeta tarjeta;

public:
    Usuario();
    Usuario(const string& nuevoCodigo, const string& nuevoNombre, const string& nuevoDni,
            int nuevoTipo, const string& codigoTarjeta);

    const string& obtenerCodigo() const;
    const string& obtenerNombre() const;
    const string& obtenerDni() const;
    int obtenerTipo() const;
    virtual int obtenerDescuento() const = 0;
    Tarjeta& obtenerTarjeta();
    const Tarjeta& obtenerTarjeta() const;

    virtual ~Usuario();
};

#endif
