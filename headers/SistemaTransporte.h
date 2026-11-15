#ifndef PROYECTIO_BUZZIO_SISTEMATRANSPORTE_H
#define PROYECTIO_BUZZIO_SISTEMATRANSPORTE_H

#include "Usuario.h"
#include "Viaje.h"

#include <string>

using namespace std;

class SistemaTransporte {
private:
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidadUsuarios;
    Viaje* viajes;
    int cantidadViajes;
    int capacidadViajes;

    void asegurarEspacioUsuarios();
    void asegurarEspacioViajes();
    void limpiarUsuarios();
    int ultimoViajeDe(int posicionUsuario) const;
    void imprimirViaje(const Viaje& viaje, int numero) const;
    bool verificar(const string& nombre, bool condicion, int& aprobadas, int& total) const;

public:
    SistemaTransporte();
    ~SistemaTransporte();

    bool estacionValida(int estacion) const;
    bool medioValido(int medio) const;
    bool tipoValido(int tipo) const;
    bool medioPasaPor(int medio, int estacion) const;
    bool rutaValida(int medio, int origen, int destino) const;
    bool esEstacionConexion(int estacion) const;
    bool dniValido(const string& dni) const;
    int buscarUsuarioPorDni(const string& dni) const;

    int registrarUsuario(const string& nombre, const string& dni, int tipo);
    int recargarTarjeta(int posicionUsuario, int monto);
    int cambiarEstadoTarjeta(int posicionUsuario, bool activa);
    int calcularTarifa(const Usuario& usuario, int medio, bool transbordo) const;
    bool esTransbordo(int posicionUsuario, int origen, int medio, int minutosNuevo) const;
    int registrarViaje(int posicionUsuario, int origen, int destino, int medio, int fecha, int hora,
                       int* tarifaCobrada, bool* fueTransbordo);

    void mostrarUsuarios() const;
    void mostrarHistorial(int posicionUsuario = -1) const;
    void mostrarEstadisticas() const;
    void mostrarRed() const;
    void cargarDatosDemo();
    void ejecutarPruebas() const;

    int obtenerCantidadUsuarios() const;
    int obtenerCantidadViajes() const;
    int obtenerSaldo(int posicionUsuario) const;
};

#endif
