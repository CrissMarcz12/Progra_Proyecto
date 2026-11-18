/*
 * ==============================================================
 *  Archivo:  clases/Viaje.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de la clase Viaje: constructores y consultas.
 * ==============================================================
 */

#include "Viaje.h"

#include "Utilidades.h"

// ------------------------------------------------------------
// Viaje()  -- constructor por defecto
// Que hace: crea un viaje vacio (valores -1 y 0). Se necesita porque el
//           arreglo dinamico new Viaje[n] crea los objetos con este constructor.
// ------------------------------------------------------------
Viaje::Viaje()
{
    // Los valores -1 indican que aun no existe un viaje valido.
    usuario = -1;
    origen = -1;
    destino = -1;
    medio = -1;
    fecha = 0;
    hora = 0;
    tarifa = 0;
    transbordo = false;
}

// ------------------------------------------------------------
// Viaje(usuario, origen, destino, medio, fecha, hora, tarifa, transbordo)
// Que hace: guarda todos los datos de un viaje ya aceptado y cobrado.
// ------------------------------------------------------------
Viaje::Viaje(int nuevoUsuario, int nuevoOrigen, int nuevoDestino, int nuevoMedio, int nuevaFecha, int nuevaHora,
             int nuevaTarifa, bool esTransbordo)
{
    usuario = nuevoUsuario;
    origen = nuevoOrigen;
    destino = nuevoDestino;
    medio = nuevoMedio;
    fecha = nuevaFecha;
    hora = nuevaHora;
    tarifa = nuevaTarifa;
    transbordo = esTransbordo;
}

// Devuelve la posicion del usuario que hizo el viaje.
int Viaje::obtenerUsuario() const
{
    return usuario;
}

// Devuelve la estacion de origen.
int Viaje::obtenerOrigen() const
{
    return origen;
}

// Devuelve la estacion de destino.
int Viaje::obtenerDestino() const
{
    return destino;
}

// Devuelve el medio usado (0 Bus, 1 Metro, 2 Tranvia).
int Viaje::obtenerMedio() const
{
    return medio;
}

// Devuelve la fecha (AAAAMMDD).
int Viaje::obtenerFecha() const
{
    return fecha;
}

// Devuelve la hora (HHMM).
int Viaje::obtenerHora() const
{
    return hora;
}

// Devuelve la tarifa pagada en centimos.
int Viaje::obtenerTarifa() const
{
    return tarifa;
}

// Devuelve true si el viaje fue un transbordo.
bool Viaje::esTransbordo() const
{
    return transbordo;
}

// ------------------------------------------------------------
// obtenerMinutosAbsolutos()
// Que hace: convierte la fecha y hora del viaje a minutos con la
//           funcion minutosAbsolutos() de Utilidades.
// ------------------------------------------------------------
int Viaje::obtenerMinutosAbsolutos() const
{
    // Sirve para comparar la fecha y hora con un viaje anterior.
    return minutosAbsolutos(fecha, hora);
}
