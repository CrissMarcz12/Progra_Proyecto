/*
 * ==============================================================
 *  Archivo:  clases/UsuarioEstudiante.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de UsuarioEstudiante.
 *    - Solo define sus constructores y su descuento: todo lo demas
 *      (datos, tarjeta, consultas) lo hereda de Usuario.
 * ==============================================================
 */

#include "UsuarioEstudiante.h"

#include "Constantes.h"

using namespace std;

// ------------------------------------------------------------
// UsuarioEstudiante()  -- constructor por defecto
// Que hace: llama al constructor por defecto de Usuario.
// ------------------------------------------------------------
UsuarioEstudiante::UsuarioEstudiante()
    : Usuario()
{
}

// ------------------------------------------------------------
// UsuarioEstudiante(codigo, nombre, dni, codigoTarjeta)
// Que hace: llama al constructor de Usuario con el tipo ESTUDIANTE ya fijado.
// ------------------------------------------------------------
UsuarioEstudiante::UsuarioEstudiante(const string& codigo, const string& nombre, const string& dni,
                                     const string& codigoTarjeta)
    : Usuario(codigo, nombre, dni, ESTUDIANTE, codigoTarjeta)
{
}

// ------------------------------------------------------------
// obtenerDescuento()  -- POLIMORFISMO
// Que hace: devuelve DESCUENTOS[ESTUDIANTE] = 30 %.
// calcularTarifa() llama a este metodo sin saber el tipo de usuario.
// ------------------------------------------------------------
int UsuarioEstudiante::obtenerDescuento() const
{
    return DESCUENTOS[ESTUDIANTE];
}
