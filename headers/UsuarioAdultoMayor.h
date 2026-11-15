#ifndef PROYECTIO_BUZZIO_USUARIOADULTOMAYOR_H
#define PROYECTIO_BUZZIO_USUARIOADULTOMAYOR_H

#include "Usuario.h"

using namespace std;

class UsuarioAdultoMayor : public Usuario {
public:
    UsuarioAdultoMayor();
    UsuarioAdultoMayor(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    int obtenerDescuento() const override;
};

#endif
