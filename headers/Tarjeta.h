/*
 * ==============================================================
 *  Archivo:  headers/Tarjeta.h
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La declaracion de la clase Tarjeta.
 *    - Una tarjeta guarda su codigo, su saldo (en centimos) y si esta activa.
 *    - El saldo es privado: solo cambia con recargar() o descontar(),
 *      asi nunca puede quedar negativo (encapsulamiento).
 * ==============================================================
 */

#ifndef PROYECTIO_BUZZIO_TARJETA_H
#define PROYECTIO_BUZZIO_TARJETA_H

#include <string>
#include <ostream>

using namespace std;

// Tarjeta: cada Usuario tiene una dentro (composicion).
class Tarjeta {
private:
    // Codigo de la tarjeta, por ejemplo T001
    string codigo;
    // Saldo en centimos: S/ 15.20 se guarda como 1520
    int saldoCentimos;
    // true = activa, false = inactiva (no puede pagar viajes)
    bool activa;

public:
    // Constructores: la tarjeta nace con saldo 0 y activa
    Tarjeta();
    Tarjeta(const string& nuevoCodigo);

    // Consultas: no modifican la tarjeta (por eso son const)
    const string& obtenerCodigo() const;
    int consultarSaldo() const;
    bool estaActiva() const;
    // Activa o desactiva la tarjeta
    void cambiarEstado(bool nuevoEstado);
    // Suma saldo si el monto es valido (0 < monto <= S/ 500.00)
    bool recargar(int monto);
    // Resta saldo solo si alcanza; devuelve false si no
    bool descontar(int monto);

    // Sobrecarga de += : suma una recarga al saldo
    Tarjeta& operator+=(int monto);

    // Sobrecarga de << : imprime "T001 | S/ 15.20 | Activa". Es friend para leer los datos privados
    friend ostream& operator<<(ostream& salida, const Tarjeta& tarjeta);
};

ostream& operator<<(ostream& salida, const Tarjeta& tarjeta);

#endif
