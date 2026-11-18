/*
 * ==============================================================
 *  Archivo:  clases/UsuarioAdultoMayor.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de UsuarioAdultoMayor.
 *    - Solo define sus constructores y su descuento: todo lo demas
 *      (datos, tarjeta, consultas) lo hereda de Usuario.
 * ==============================================================
 */

#include "UsuarioAdultoMayor.h"

#include "Constantes.h"

using namespace std;

// ------------------------------------------------------------
// UsuarioAdultoMayor()  -- constructor por defecto
// Que hace: llama al constructor por defecto de Usuario.
// ------------------------------------------------------------
UsuarioAdultoMayor::UsuarioAdultoMayor()
    : Usuario()
{
}

// ------------------------------------------------------------
// UsuarioAdultoMayor(codigo, nombre, dni, codigoTarjeta)
// Que hace: llama al constructor de Usuario con el tipo ADULTO_MAYOR ya fijado.
// ------------------------------------------------------------
UsuarioAdultoMayor::UsuarioAdultoMayor(const string& codigo, const string& nombre, const string& dni,
                                       const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, ADULTO_MAYOR, codigoTarjeta)
{
}

// ------------------------------------------------------------
// obtenerDescuento()  -- POLIMORFISMO
// Que hace: devuelve DESCUENTOS[ADULTO_MAYOR] = 50 %.
// calcularTarifa() llama a este metodo sin saber el tipo de usuario.
// ------------------------------------------------------------
int UsuarioAdultoMayor::obtenerDescuento() const
{
    return DESCUENTOS[ADULTO_MAYOR];
}
