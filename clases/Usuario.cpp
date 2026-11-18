/*
 * ==============================================================
 *  Archivo:  clases/Usuario.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de la clase base Usuario: constructores y consultas.
 *    - obtenerDescuento() no esta aqui porque es virtual pura;
 *      la implementa cada clase hija.
 * ==============================================================
 */

#include "Usuario.h"

#include "Constantes.h"

using namespace std;

// ------------------------------------------------------------
// Usuario()  -- constructor por defecto
// Que hace: deja los datos vacios y el tipo en REGULAR.
//           Lo llaman los constructores por defecto de las clases hijas.
// ------------------------------------------------------------
Usuario::Usuario()
{
    // El usuario por defecto permite reservar espacio en el arreglo dinamico.
    codigo = "";
    nombre = "";
    dni = "";
    tipo = REGULAR;
}

// ------------------------------------------------------------
// Usuario(codigo, nombre, dni, tipo, codigoTarjeta)
// Que hace: guarda los datos de la persona y le crea su tarjeta con el
//           codigo indicado (saldo 0 y activa).
// ------------------------------------------------------------
Usuario::Usuario(const string& nuevoCodigo, const string& nuevoNombre, const string& nuevoDni, int nuevoTipo,
                 const string& codigoTarjeta)
{
    codigo = nuevoCodigo;
    nombre = nuevoNombre;
    dni = nuevoDni;
    tipo = nuevoTipo;
    tarjeta = Tarjeta(codigoTarjeta);
}

// Devuelve el codigo del usuario (ej. U001).
const string& Usuario::obtenerCodigo() const
{
    return codigo;
}

// Devuelve el nombre completo.
const string& Usuario::obtenerNombre() const
{
    return nombre;
}

// Devuelve el DNI (8 digitos, como texto).
const string& Usuario::obtenerDni() const
{
    return dni;
}

// Devuelve el tipo (0 Regular, 1 Estudiante, 2 Adulto mayor).
int Usuario::obtenerTipo() const
{
    return tipo;
}

// Devuelve la tarjeta por referencia para poder modificarla (recargar, descontar).
Tarjeta& Usuario::obtenerTarjeta()
{
    return tarjeta;
}

// Version const: devuelve la tarjeta solo para leerla.
const Tarjeta& Usuario::obtenerTarjeta() const
{
    return tarjeta;
}

// ------------------------------------------------------------
// ~Usuario()  -- destructor virtual
// Que hace: no necesita liberar nada (la tarjeta es un objeto, no un puntero),
//           pero es virtual para que delete funcione bien con las clases hijas.
// ------------------------------------------------------------
Usuario::~Usuario()
{
}
