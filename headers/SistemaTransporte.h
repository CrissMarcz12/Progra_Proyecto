/*
 * ==============================================================
 *  Archivo:  headers/SistemaTransporte.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de SistemaTransporte, el "cerebro" del proyecto.
 *    - Guarda los usuarios (arreglo dinamico de punteros Usuario**) y el
 *      historial de viajes (arreglo dinamico de objetos Viaje*).
 *    - Valida, cobra y registra viajes, y calcula las estadisticas.
 *    - Las operaciones devuelven OK o un codigo de error (ver Constantes.h).
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_SISTEMATRANSPORTE_H
#define PROYECTIO_BUZZIO_SISTEMATRANSPORTE_H

#include "Usuario.h"
#include "Viaje.h"

#include <string>

using namespace std;

// SistemaTransporte: es dueno de los usuarios y viajes (composicion).
class SistemaTransporte {
private:
    // Arreglo dinamico de punteros: permite guardar los 3 tipos de usuario (polimorfismo)
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;
    // Arreglo dinamico con el historial de viajes aceptados
    Viaje* viajes;
    int cantidadViajes;
    int capacidadViajes;

    // Ayudantes privados: agrandar arreglos, liberar memoria y buscar el ultimo viaje
    void asegurarEspacioUsuarios();
    void asegurarEspacioViajes();
    void limpiarUsuarios();
    int ultimoViajeDe(int posicionUsuario) const;
    // Ayudantes privados para mostrar un viaje y para las pruebas internas
    void imprimirViaje(const Viaje& viaje, int numero) const;
    bool verificar(const string& nombre, bool condicion, int& aprobadas, int& total) const;

public:
    // Constructor y destructor: crean y liberan la memoria dinamica
    SistemaTransporte();
    ~SistemaTransporte();

    // Validaciones de datos y de la red de transporte
    bool estacionValida(int estacion) const;
    bool medioValido(int medio) const;
    bool tipoValido(int tipo) const;
    bool medioPasaPor(int medio, int estacion) const;
    bool rutaValida(int medio, int origen, int destino) const;
    bool esEstacionConexion(int estacion) const;
    bool dniValido(const string& dni) const;
    // Busca un usuario: devuelve su posicion o -1
    int buscarUsuarioPorDni(const string& dni) const;

    // Operaciones principales del sistema
    int registrarUsuario(const string& nombre, const string& dni, int tipo);
    int recargarTarjeta(int posicionUsuario, int monto);
    int cambiarEstadoTarjeta(int posicionUsuario, bool activa);
    int calcularTarifa(const Usuario& usuario, int medio, bool transbordo) const;
    bool esTransbordo(int posicionUsuario, int origen, int medio, int minutosNuevo) const;
    int registrarViaje(int posicionUsuario, int origen, int destino, int medio, int fecha, int hora,
                       int* tarifaCobrada, bool* fueTransbordo);

    // Mostrar informacion, cargar la demostracion y ejecutar las pruebas
    void mostrarUsuarios() const;
    void mostrarHistorial(int posicionUsuario = -1) const;
    void mostrarEstadisticas() const;
    void mostrarRed() const;
    void cargarDatosDemo();
    void ejecutarPruebas() const;

    // Consultas simples
    int obtenerCantidadUsuarios() const;
    int obtenerCantidadViajes() const;
    int obtenerSaldo(int posicionUsuario) const;
};

#endif
