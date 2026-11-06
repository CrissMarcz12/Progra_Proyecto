#ifndef PROYECTIO_BUZZIO_TARJETA_H
#define PROYECTIO_BUZZIO_TARJETA_H

#include <string>

class Tarjeta {
private:
    std::string codigo;
    int saldoCentimos;
    bool activa;

public:
    Tarjeta();
    Tarjeta(const std::string& nuevoCodigo);

    const std::string& obtenerCodigo() const;
    int consultarSaldo() const;
    bool estaActiva() const;
    void cambiarEstado(bool nuevoEstado);
    bool recargar(int monto);
    bool descontar(int monto);
};

#endif
