#include "Viaje.h"

#include "Utilidades.h"

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

int Viaje::obtenerUsuario() const
{
    return usuario;
}

int Viaje::obtenerOrigen() const
{
    return origen;
}

int Viaje::obtenerDestino() const
{
    return destino;
}

int Viaje::obtenerMedio() const
{
    return medio;
}

int Viaje::obtenerFecha() const
{
    return fecha;
}

int Viaje::obtenerHora() const
{
    return hora;
}

int Viaje::obtenerTarifa() const
{
    return tarifa;
}

bool Viaje::esTransbordo() const
{
    return transbordo;
}

int Viaje::obtenerMinutosAbsolutos() const
{
    // Sirve para comparar la fecha y hora con un viaje anterior.
    return minutosAbsolutos(fecha, hora);
}
