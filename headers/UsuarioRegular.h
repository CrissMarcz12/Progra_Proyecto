/*
 * ==============================================================
 *  Archivo:  headers/UsuarioRegular.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de UsuarioRegular, que hereda de Usuario.
 *    - Representa a un usuario regular (sin descuento): descuento de 0 %.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_USUARIOREGULAR_H
#define PROYECTIO_BUZZIO_USUARIOREGULAR_H

#include "Usuario.h"

using namespace std;

// Herencia publica: UsuarioRegular ES un Usuario.
class UsuarioRegular : public Usuario {
public:
    // Constructores: pasan los datos al constructor de Usuario
    UsuarioRegular();
    UsuarioRegular(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    // Redefine el metodo virtual: devuelve 0
    int obtenerDescuento() const override;
};

#endif
