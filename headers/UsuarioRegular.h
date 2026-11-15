#ifndef PROYECTIO_BUZZIO_USUARIOREGULAR_H
#define PROYECTIO_BUZZIO_USUARIOREGULAR_H

#include "Usuario.h"

using namespace std;

class UsuarioRegular : public Usuario {
public:
    UsuarioRegular();
    UsuarioRegular(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    int obtenerDescuento() const override;
};

#endif
