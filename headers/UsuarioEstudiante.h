#ifndef PROYECTIO_BUZZIO_USUARIOESTUDIANTE_H
#define PROYECTIO_BUZZIO_USUARIOESTUDIANTE_H

#include "Usuario.h"

using namespace std;

class UsuarioEstudiante : public Usuario {
public:
    UsuarioEstudiante();
    UsuarioEstudiante(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    int obtenerDescuento() const override;
};

#endif
