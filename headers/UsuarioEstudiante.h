/*
 * ==============================================================
 *  Archivo:  headers/UsuarioEstudiante.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de UsuarioEstudiante, que hereda de Usuario.
 *    - Representa a un usuario estudiante: descuento de 30 %.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_USUARIOESTUDIANTE_H
#define PROYECTIO_BUZZIO_USUARIOESTUDIANTE_H

#include "Usuario.h"

using namespace std;

// Herencia publica: UsuarioEstudiante ES un Usuario.
class UsuarioEstudiante : public Usuario {
public:
    // Constructores: pasan los datos al constructor de Usuario
    UsuarioEstudiante();
    UsuarioEstudiante(const string& codigo, const string& nombre, const string& dni, const string& codigoTarjeta);

    // Redefine el metodo virtual: devuelve 30
    int obtenerDescuento() const override;
};

#endif
