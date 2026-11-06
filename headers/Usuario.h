#ifndef PROYECTIO_BUZZIO_USUARIO_H
#define PROYECTIO_BUZZIO_USUARIO_H

#include "Tarjeta.h"

#include <string>

class Usuario {
private:
    std::string codigo;
    std::string nombre;
    std::string dni;
    int tipo;
    Tarjeta tarjeta;

public:
    Usuario();
    Usuario(const std::string& nuevoCodigo, const std::string& nuevoNombre, const std::string& nuevoDni,
            int nuevoTipo, const std::string& codigoTarjeta);

    const std::string& obtenerCodigo() const;
    const std::string& obtenerNombre() const;
    const std::string& obtenerDni() const;
    int obtenerTipo() const;
    int obtenerDescuento() const;
    Tarjeta& obtenerTarjeta();
    const Tarjeta& obtenerTarjeta() const;
};

#endif
