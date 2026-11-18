/*
 * ==============================================================
 *  Archivo:  headers/UsuarioAdultoMayor.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de UsuarioAdultoMayor, que hereda de Usuario.
 *    - Representa a un usuario adulto mayor: descuento de 50 %.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_USUARIOADULTOMAYOR_H
#define PROYECTIO_BUZZIO_USUARIOADULTOMAYOR_H

#include "Usuario.h"

using namespace std;

// Herencia publica: UsuarioAdultoMayor ES un Usuario.
class UsuarioAdultoMayor : public Usuario {
public:
    // Constructores: pasan los datos al constructor de Usuario
    UsuarioAdultoMayor();
    UsuarioAdultoMayor(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    // Redefine el metodo virtual: devuelve 50
    int obtenerDescuento() const override;
};

#endif
