#ifndef PROYECTIO_BUZZIO_TARJETA_H
#define PROYECTIO_BUZZIO_TARJETA_H

#include <string>
#include <ostream>

using namespace std;

class Tarjeta {
private:
    string codigo;
    int saldoCentimos;
    bool activa;

public:
    Tarjeta();
    Tarjeta(const string& nuevoCodigo);

    const string& obtenerCodigo() const;
    int consultarSaldo() const;
    bool estaActiva() const;
    void cambiarEstado(bool nuevoEstado);
    bool recargar(int monto);
    bool descontar(int monto);

    Tarjeta& operator+=(int monto);

    friend ostream& operator<<(ostream& salida, const Tarjeta& tarjeta);
};

ostream& operator<<(ostream& salida, const Tarjeta& tarjeta);

#endif
