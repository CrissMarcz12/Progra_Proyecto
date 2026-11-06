#include "SistemaTransporte.h"

#include "Constantes.h"
#include "Utilidades.h"

#include <cctype>
#include <iostream>

using namespace std;

SistemaTransporte::SistemaTransporte()
{
    cantidadUsuarios = 0;
    capacidadUsuarios = CAPACIDAD_INICIAL;
    cantidadViajes = 0;
    capacidadViajes = CAPACIDAD_INICIAL;
    usuarios = new Usuario[capacidadUsuarios];
    viajes = new Viaje[capacidadViajes];
}

SistemaTransporte::~SistemaTransporte() {
    delete[] usuarios;
    delete[] viajes;
}

void SistemaTransporte::asegurarEspacioUsuarios() {
    if (cantidadUsuarios < capacidadUsuarios) return;
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario* nuevos = new Usuario[nuevaCapacidad];
    for (int i = 0; i < cantidadUsuarios; ++i) nuevos[i] = usuarios[i];
    delete[] usuarios;
    usuarios = nuevos;
    capacidadUsuarios = nuevaCapacidad;
}

void SistemaTransporte::asegurarEspacioViajes() {
    if (cantidadViajes < capacidadViajes) return;
    int nuevaCapacidad = capacidadViajes * 2;
    Viaje* nuevos = new Viaje[nuevaCapacidad];
    for (int i = 0; i < cantidadViajes; ++i) nuevos[i] = viajes[i];
    delete[] viajes;
    viajes = nuevos;
    capacidadViajes = nuevaCapacidad;
}

int SistemaTransporte::ultimoViajeDe(int posicionUsuario) const {
    for (int i = cantidadViajes - 1; i >= 0; --i) {
        if (viajes[i].obtenerUsuario() == posicionUsuario) return i;
    }
    return -1;
}

bool SistemaTransporte::estacionValida(int estacion) const {
    return estacion >= 0 && estacion < CANT_ESTACIONES;
}

bool SistemaTransporte::medioValido(int medio) const {
    return medio >= 0 && medio < CANT_MEDIOS;
}

bool SistemaTransporte::tipoValido(int tipo) const {
    return tipo >= 0 && tipo < CANT_TIPOS;
}

bool SistemaTransporte::medioPasaPor(int medio, int estacion) const {
    if (!medioValido(medio) || !estacionValida(estacion)) return false;
    for (int i = 0; i < LONG_RUTA; ++i) {
        if (RUTAS[medio][i] == estacion) return true;
    }
    return false;
}

bool SistemaTransporte::rutaValida(int medio, int origen, int destino) const {
    return medioPasaPor(medio, origen) && medioPasaPor(medio, destino);
}

bool SistemaTransporte::esEstacionConexion(int estacion) const {
    if (!estacionValida(estacion)) return false;
    int mediosQuePasan = 0;
    for (int medio = 0; medio < CANT_MEDIOS; ++medio) {
        if (medioPasaPor(medio, estacion)) ++mediosQuePasan;
    }
    return mediosQuePasan >= 2;
}

bool SistemaTransporte::dniValido(const string& dni) const {
    if (dni.length() != 8) {
        return false;
    }

    for (int i = 0; i < 8; ++i) {
        if (!isdigit(dni[i])) {
            return false;
        }
    }

    return true;
}

int SistemaTransporte::buscarUsuarioPorDni(const string& dni) const {
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (usuarios[i].obtenerDni() == dni) return i;
    }
    return -1;
}

int SistemaTransporte::registrarUsuario(const string& nombre, const string& dni, int tipo) {
    if (nombre.empty() || !dniValido(dni) || !tipoValido(tipo)) return ERR_DNI;
    if (buscarUsuarioPorDni(dni) != -1) return ERR_DNI_REPETIDO;
    asegurarEspacioUsuarios();
    int numero = cantidadUsuarios + 1;
    usuarios[cantidadUsuarios] = Usuario(codigoConCeros("U", numero), nombre, dni, tipo,
                                          codigoConCeros("T", numero));
    ++cantidadUsuarios;
    return OK;
}

int SistemaTransporte::recargarTarjeta(int posicionUsuario, int monto) {
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) return ERR_USUARIO;
    return usuarios[posicionUsuario].obtenerTarjeta().recargar(monto) ? OK : ERR_MONTO;
}

int SistemaTransporte::cambiarEstadoTarjeta(int posicionUsuario, bool activa) {
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) return ERR_USUARIO;
    usuarios[posicionUsuario].obtenerTarjeta().cambiarEstado(activa);
    return OK;
}

int SistemaTransporte::calcularTarifa(int tipoUsuario, int medio, bool transbordo) const {
    int tarifa = TARIFAS_BASE[medio];
    tarifa = (tarifa * (100 - DESCUENTOS[tipoUsuario]) + 50) / 100;
    if (transbordo) tarifa = (tarifa * 50 + 50) / 100;
    return tarifa;
}

bool SistemaTransporte::esTransbordo(int posicionUsuario, int origen, int medio, int minutosNuevo) const {
    int posicionUltimo = ultimoViajeDe(posicionUsuario);
    if (posicionUltimo == -1) return false;
    const Viaje& anterior = viajes[posicionUltimo];
    int diferencia = minutosNuevo - anterior.obtenerMinutosAbsolutos();
    return anterior.obtenerMedio() != medio && anterior.obtenerDestino() == origen &&
           esEstacionConexion(origen) && diferencia >= 0 && diferencia <= 30;
}

int SistemaTransporte::registrarViaje(int posicionUsuario, int origen, int destino, int medio, int fecha, int hora,
                                      int* tarifaCobrada, bool* fueTransbordo) {
    if (tarifaCobrada != NULL) {
        *tarifaCobrada = 0;
    }

    if (fueTransbordo != NULL) {
        *fueTransbordo = false;
    }
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) return ERR_USUARIO;
    if (!usuarios[posicionUsuario].obtenerTarjeta().estaActiva()) return ERR_TARJETA_INACTIVA;
    if (!estacionValida(origen) || !estacionValida(destino)) return ERR_ESTACION;
    if (origen == destino) return ERR_MISMA_ESTACION;
    if (!medioValido(medio)) return ERR_MEDIO;
    if (!rutaValida(medio, origen, destino)) return ERR_RUTA;
    if (!fechaValida(fecha) || !horaValida(hora)) return ERR_FECHA_HORA;

    int minutosNuevo = minutosAbsolutos(fecha, hora);
    int posicionUltimo = ultimoViajeDe(posicionUsuario);
    if (posicionUltimo != -1 && minutosNuevo < viajes[posicionUltimo].obtenerMinutosAbsolutos()) {
        return ERR_CRONOLOGIA;
    }

    bool transbordo = esTransbordo(posicionUsuario, origen, medio, minutosNuevo);
    int tarifa = calcularTarifa(usuarios[posicionUsuario].obtenerTipo(), medio, transbordo);
    if (usuarios[posicionUsuario].obtenerTarjeta().consultarSaldo() < tarifa) return ERR_SALDO;

    asegurarEspacioViajes();
    usuarios[posicionUsuario].obtenerTarjeta().descontar(tarifa);
    viajes[cantidadViajes] = Viaje(posicionUsuario, origen, destino, medio, fecha, hora, tarifa, transbordo);
    ++cantidadViajes;
    if (tarifaCobrada != NULL) {
        *tarifaCobrada = tarifa;
    }

    if (fueTransbordo != NULL) {
        *fueTransbordo = transbordo;
    }
    return OK;
}

void SistemaTransporte::imprimirViaje(const Viaje& viaje, int numero) const {
    const Usuario& usuario = usuarios[viaje.obtenerUsuario()];
    cout << numero << ". " << usuario.obtenerNombre() << " (" << usuario.obtenerCodigo() << ") | "
         << NOMBRES_ESTACION[viaje.obtenerOrigen()] << " -> " << NOMBRES_ESTACION[viaje.obtenerDestino()]
         << " | " << NOMBRES_MEDIO[viaje.obtenerMedio()] << " | "
         << fechaHoraTexto(viaje.obtenerFecha(), viaje.obtenerHora()) << " | "
         << montoTexto(viaje.obtenerTarifa()) << " | "
         << (viaje.esTransbordo() ? "Transbordo" : "Viaje normal") << '\n';
}

void SistemaTransporte::mostrarUsuarios() const {
    if (cantidadUsuarios == 0) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    cout << "\nUSUARIOS\n";
    for (int i = 0; i < cantidadUsuarios; ++i) {
        const Usuario& u = usuarios[i];
        cout << u.obtenerCodigo() << " | " << u.obtenerNombre() << " | DNI " << u.obtenerDni() << " | "
             << NOMBRES_TIPO[u.obtenerTipo()] << " | " << u.obtenerTarjeta().obtenerCodigo() << " | "
             << montoTexto(u.obtenerTarjeta().consultarSaldo()) << " | "
             << (u.obtenerTarjeta().estaActiva() ? "Activa" : "Inactiva") << '\n';
    }
}

void SistemaTransporte::mostrarHistorial(int posicionUsuario) const {
    if (cantidadViajes == 0) {
        cout << "No hay viajes registrados.\n";
        return;
    }
    bool encontro = false;
    cout << "\nHISTORIAL DE VIAJES\n";
    for (int i = 0; i < cantidadViajes; ++i) {
        if (posicionUsuario == -1 || viajes[i].obtenerUsuario() == posicionUsuario) {
            imprimirViaje(viajes[i], i + 1);
            encontro = true;
        }
    }
    if (!encontro) cout << "El usuario aun no tiene viajes aceptados.\n";
}

void SistemaTransporte::mostrarEstadisticas() const {
    int porMedio[3] = {0, 0, 0};
    int usoEstacion[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int recaudacion = 0;
    int transbordos = 0;
    for (int i = 0; i < cantidadViajes; ++i) {
        ++porMedio[viajes[i].obtenerMedio()];
        ++usoEstacion[viajes[i].obtenerOrigen()];
        ++usoEstacion[viajes[i].obtenerDestino()];
        recaudacion += viajes[i].obtenerTarifa();
        if (viajes[i].esTransbordo()) ++transbordos;
    }
    int estacionMayorUso = 0;
    for (int i = 1; i < CANT_ESTACIONES; ++i) {
        if (usoEstacion[i] > usoEstacion[estacionMayorUso]) estacionMayorUso = i;
    }
    cout << "\nESTADISTICAS\n";
    cout << "Total de viajes realizados: " << cantidadViajes << '\n';
    cout << "Viajes por medio: Bus " << porMedio[BUS] << ", Metro " << porMedio[METRO]
         << ", Tranvia " << porMedio[TRANVIA] << '\n';
    cout << "Recaudacion total: " << montoTexto(recaudacion) << '\n';
    if (cantidadViajes == 0) cout << "Estacion con mas viajes: sin datos\n";
    else {
        cout << "Estacion con mas viajes: " << NOMBRES_ESTACION[estacionMayorUso] << " ("
             << usoEstacion[estacionMayorUso] << " apariciones)\n";
    }
    cout << "Total de transbordos: " << transbordos << '\n';
}

void SistemaTransporte::mostrarRed() const {
    cout << "\nRED DE TRANSPORTE\nEstaciones:\n";
    for (int i = 0; i < CANT_ESTACIONES; ++i) {
        cout << "  " << CODIGOS_ESTACION[i] << " - " << NOMBRES_ESTACION[i];
        if (esEstacionConexion(i)) cout << " (conexion)";
        cout << '\n';
    }
    cout << "\nRutas bidireccionales:\n";
    for (int medio = 0; medio < CANT_MEDIOS; ++medio) {
        cout << "  " << NOMBRES_MEDIO[medio] << " (" << montoTexto(TARIFAS_BASE[medio]) << "): ";
        bool primero = true;
        for (int i = 0; i < LONG_RUTA; ++i) {
            if (RUTAS[medio][i] == -1) continue;
            if (!primero) cout << " <-> ";
            cout << NOMBRES_ESTACION[RUTAS[medio][i]];
            primero = false;
        }
        cout << '\n';
    }
    cout << "\nDescuentos: Regular 0%, Estudiante 30%, Adulto mayor 50%.\n";
}

void SistemaTransporte::cargarDatosDemo() {
    cantidadUsuarios = 0;
    cantidadViajes = 0;
    registrarUsuario("Ana Torres", "70000001", REGULAR);
    registrarUsuario("Luis Quispe", "70000002", ESTUDIANTE);
    registrarUsuario("Rosa Huaman", "70000003", ADULTO_MAYOR);
    registrarUsuario("Diego Ramos", "70000004", ESTUDIANTE);
    registrarUsuario("Carla Mendoza", "70000005", REGULAR);
    recargarTarjeta(0, 2000); recargarTarjeta(1, 1500); recargarTarjeta(2, 1000);
    recargarTarjeta(3, 200); recargarTarjeta(4, 500); cambiarEstadoTarjeta(4, false);

    int tarifa; bool transbordo;
    registrarViaje(0, 0, 3, BUS, 20261005, 730, &tarifa, &transbordo);
    registrarViaje(1, 5, 1, METRO, 20261005, 740, &tarifa, &transbordo);
    registrarViaje(1, 1, 4, BUS, 20261005, 755, &tarifa, &transbordo);
    registrarViaje(2, 7, 2, TRANVIA, 20261005, 800, &tarifa, &transbordo);
    registrarViaje(2, 2, 0, BUS, 20261005, 820, &tarifa, &transbordo);
    registrarViaje(0, 3, 4, BUS, 20261005, 810, &tarifa, &transbordo);
    registrarViaje(0, 4, 6, TRANVIA, 20261005, 850, &tarifa, &transbordo);
    registrarViaje(3, 6, 0, METRO, 20261005, 900, &tarifa, &transbordo);
    registrarViaje(3, 0, 3, BUS, 20261005, 920, &tarifa, &transbordo);
    registrarViaje(3, 3, 4, BUS, 20261005, 940, &tarifa, &transbordo);
    registrarViaje(4, 0, 1, BUS, 20261005, 1000, &tarifa, &transbordo);
    registrarViaje(0, 0, 7, BUS, 20261005, 1100, &tarifa, &transbordo);

    cout << "Datos de demostracion cargados: 5 usuarios, 9 viajes aceptados y 3 rechazados.\n";
    cout << "Resultados esperados: Bus 5, Metro 2, Tranvia 2, recaudacion S/ 9.94, Norte 4, transbordos 3.\n";
}

bool SistemaTransporte::verificar(const string& nombre, bool condicion, int& aprobadas, int& total) const {
    ++total;
    if (condicion) {
        ++aprobadas;
        cout << "  [OK] " << nombre << '\n';
        return true;
    }
    cout << "  [FALLO] " << nombre << '\n';
    return false;
}

void SistemaTransporte::ejecutarPruebas() const {
    int aprobadas = 0;
    int total = 0;
    cout << "\nEJECUCION DE PRUEBAS\n";
    verificar("Fecha bisiesta valida (29/02/2028)", fechaValida(20280229), aprobadas, total);
    verificar("Fecha inexistente rechazada (31/02/2026)", !fechaValida(20260231), aprobadas, total);
    verificar("Hora 23:59 valida", horaValida(2359), aprobadas, total);
    verificar("Hora 24:00 rechazada", !horaValida(2400), aprobadas, total);
    verificar("DNI de 8 digitos valido", dniValido("71234567"), aprobadas, total);
    verificar("DNI con letra rechazado", !dniValido("7123456A"), aprobadas, total);
    verificar("Bus conecta Norte y Terminal", rutaValida(BUS, 0, 4), aprobadas, total);
    verificar("Bus no conecta Norte y Sur", !rutaValida(BUS, 0, 5), aprobadas, total);
    verificar("Central es estacion de conexion", esEstacionConexion(1), aprobadas, total);
    verificar("Hospital no es estacion de conexion", !esEstacionConexion(3), aprobadas, total);
    verificar("Tarifa estudiante en Metro", calcularTarifa(ESTUDIANTE, METRO, false) == 140, aprobadas, total);
    verificar("Tarifa estudiante con transbordo", calcularTarifa(ESTUDIANTE, METRO, true) == 70, aprobadas, total);
    verificar("Redondeo adulto mayor con transbordo", calcularTarifa(ADULTO_MAYOR, BUS, true) == 38,
              aprobadas, total);
    verificar("30 minutos exactos entre viajes", minutosAbsolutos(20261005, 1030) - minutosAbsolutos(20261005, 1000) == 30,
              aprobadas, total);
    verificar("Transbordo que cruza medianoche", minutosAbsolutos(20261006, 10) - minutosAbsolutos(20261005, 2350) == 20,
              aprobadas, total);
    cout << "Resultado: " << aprobadas << " de " << total << " pruebas aprobadas.\n";
}

int SistemaTransporte::obtenerCantidadUsuarios() const { return cantidadUsuarios; }
int SistemaTransporte::obtenerCantidadViajes() const { return cantidadViajes; }

int SistemaTransporte::obtenerSaldo(int posicionUsuario) const {
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) return -1;
    return usuarios[posicionUsuario].obtenerTarjeta().consultarSaldo();
}
