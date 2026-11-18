/*
 * ==============================================================
 *  Archivo:  clases/UsuarioRegular.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de UsuarioRegular.
 *    - Solo define sus constructores y su descuento: todo lo demas
 *      (datos, tarjeta, consultas) lo hereda de Usuario.
 * ==============================================================
 */

#include "UsuarioRegular.h"

#include "Constantes.h"

using namespace std;

// ------------------------------------------------------------
// UsuarioRegular()  -- constructor por defecto
// Que hace: llama al constructor por defecto de Usuario.
// ------------------------------------------------------------
UsuarioRegular::UsuarioRegular()
    : Usuario()
{
}

// ------------------------------------------------------------
// UsuarioRegular(codigo, nombre, dni, codigoTarjeta)
// Que hace: llama al constructor de Usuario con el tipo REGULAR ya fijado.
// ------------------------------------------------------------
UsuarioRegular::UsuarioRegular(const string& codigo, const string& nombre, const string& dni,
                               const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, REGULAR, codigoTarjeta)
{
}

// ------------------------------------------------------------
// obtenerDescuento()  -- POLIMORFISMO
// Que hace: devuelve DESCUENTOS[REGULAR] = 0 %.
// calcularTarifa() llama a este metodo sin saber el tipo de usuario.
// ------------------------------------------------------------
int UsuarioRegular::obtenerDescuento() const
{
    return DESCUENTOS[REGULAR];
}
