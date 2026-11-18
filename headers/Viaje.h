/*
 * ==============================================================
 *  Archivo:  headers/Viaje.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de la clase Viaje.
 *    - Un viaje es un registro del historial: quien viajo, de donde a donde,
 *      en que medio, cuando, cuanto pago y si fue transbordo.
 *    - Solo se crean viajes aceptados; los rechazados no se guardan.
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_VIAJE_H
#define PROYECTIO_BUZZIO_VIAJE_H

// Viaje: los guarda SistemaTransporte en su arreglo dinamico de viajes.
class Viaje {
private:
    // Posicion del usuario en el arreglo de usuarios del sistema
    int usuario;
    // Numeros de estacion (0-7) y de medio (0 Bus, 1 Metro, 2 Tranvia)
    int origen;
    int destino;
    int medio;
    // Fecha AAAAMMDD, hora HHMM y tarifa pagada en centimos
    int fecha;
    int hora;
    int tarifa;
    // true si se le aplico el descuento de transbordo
    bool transbordo;

public:
    // Constructores
    Viaje();
    Viaje(int nuevoUsuario, int nuevoOrigen, int nuevoDestino, int nuevoMedio, int nuevaFecha, int nuevaHora,
          int nuevaTarifa, bool esTransbordo);

    // Consultas de cada dato (solo lectura)
    int obtenerUsuario() const;
    int obtenerOrigen() const;
    int obtenerDestino() const;
    int obtenerMedio() const;
    int obtenerFecha() const;
    int obtenerHora() const;
    int obtenerTarifa() const;
    bool esTransbordo() const;
    // Fecha y hora del viaje convertidas a minutos (para comparar viajes)
    int obtenerMinutosAbsolutos() const;
};

#endif
