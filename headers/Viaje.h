#ifndef PROYECTIO_BUZZIO_VIAJE_H
#define PROYECTIO_BUZZIO_VIAJE_H

class Viaje {
private:
    int usuario;
    int origen;
    int destino;
    int medio;
    int fecha;
    int hora;
    int tarifa;
    bool transbordo;

public:
    Viaje();
    Viaje(int nuevoUsuario, int nuevoOrigen, int nuevoDestino, int nuevoMedio, int nuevaFecha, int nuevaHora,
          int nuevaTarifa, bool esTransbordo);

    int obtenerUsuario() const;
    int obtenerOrigen() const;
    int obtenerDestino() const;
    int obtenerMedio() const;
    int obtenerFecha() const;
    int obtenerHora() const;
    int obtenerTarifa() const;
    bool esTransbordo() const;
    int obtenerMinutosAbsolutos() const;
};

#endif
