/*
 * ==============================================================
 *  Archivo:  headers/Usuario.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de la clase base Usuario.
 *    - Es ABSTRACTA: obtenerDescuento() es virtual pura (= 0), asi que no se
 *      pueden crear objetos Usuario directamente, solo de sus tres tipos:
 *      UsuarioRegular, UsuarioEstudiante y UsuarioAdultoMayor.
 *    - Cada usuario contiene su Tarjeta (composicion).
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_USUARIO_H
#define PROYECTIO_BUZZIO_USUARIO_H

#include "Tarjeta.h"

#include <string>

using namespace std;

// Usuario: clase base de la herencia. Los hijos solo cambian el descuento.
class Usuario {
private:
    // Datos de la persona. tipo se usa para mostrar el nombre del tipo
    string codigo;
    string nombre;
    string dni;
    int tipo;
    // La tarjeta vive dentro del usuario: nace y muere con el
    Tarjeta tarjeta;

public:
    // Constructores
    Usuario();
    Usuario(const string& nuevoCodigo, const string& nuevoNombre, const string& nuevoDni,
            int nuevoTipo, const string& codigoTarjeta);

    // Consultas (const: no modifican al usuario)
    const string& obtenerCodigo() const;
    const string& obtenerNombre() const;
    const string& obtenerDni() const;
    int obtenerTipo() const;
    // POLIMORFISMO: cada tipo de usuario devuelve su propio descuento en %
    virtual int obtenerDescuento() const = 0;
    // Acceso a la tarjeta: la version sin const permite recargar o descontar
    Tarjeta& obtenerTarjeta();
    const Tarjeta& obtenerTarjeta() const;

    // Destructor virtual: al hacer delete sobre un Usuario* se destruye bien el objeto hijo
    virtual ~Usuario();
};

#endif
