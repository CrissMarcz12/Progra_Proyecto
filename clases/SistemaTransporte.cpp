/*
 * ==============================================================
 *  Archivo:  clases/SistemaTransporte.cpp
 *  Proyecto: Sistema Integrado de Gestion de Transporte Publico
 *            Programacion II (CS6003) - UTEC 2026-II
 *
 *  Que tiene este archivo:
 *    - La implementacion de SistemaTransporte:
 *        1. Memoria dinamica: crear, agrandar y liberar los arreglos.
 *        2. Validaciones de la red: estaciones, medios, rutas y conexiones.
 *        3. Usuarios y tarjetas: registrar, recargar, activar/desactivar.
 *        4. Viajes: tarifa con descuentos, transbordo y registro del viaje.
 *        5. Reportes: usuarios, historial, estadisticas y red.
 *        6. Datos de demostracion y pruebas internas.
 *    - Los montos estan en centimos y las horas se comparan en minutos.
 * ==============================================================
 */

#include "SistemaTransporte.h"

#include "Constantes.h"
#include "Utilidades.h"
#include "UsuarioAdultoMayor.h"
#include "UsuarioEstudiante.h"
#include "UsuarioRegular.h"

#include <cctype>
#include <iostream>

using namespace std;

// ------------------------------------------------------------
// SistemaTransporte()  -- constructor
// Que hace: crea los dos arreglos dinamicos con CAPACIDAD_INICIAL (4)
//           y deja el sistema sin usuarios ni viajes.
// ------------------------------------------------------------
SistemaTransporte::SistemaTransporte()
{
    cantidadUsuarios = 0;
    capacidadUsuarios = CAPACIDAD_INICIAL;
    cantidadViajes = 0;
    capacidadViajes = CAPACIDAD_INICIAL;
    usuarios = new Usuario*[capacidadUsuarios];

    for (int i = 0; i < capacidadUsuarios; ++i) {
        usuarios[i] = nullptr;
    }

    viajes = new Viaje[capacidadViajes];
}

// ------------------------------------------------------------
// ~SistemaTransporte()  -- destructor
// Que hace: borra cada usuario (delete) y luego los dos arreglos (delete[]).
//           Asi no queda memoria sin liberar al cerrar el programa.
// ------------------------------------------------------------
SistemaTransporte::~SistemaTransporte()
{
    // El sistema creo los dos arreglos, por eso tambien los libera.
    limpiarUsuarios();
    delete[] usuarios;
    delete[] viajes;
}

// ------------------------------------------------------------
// limpiarUsuarios()
// Que hace: libera cada usuario creado con new y deja la cantidad en 0.
//           Se usa en el destructor y antes de cargar la demostracion.
// ------------------------------------------------------------
void SistemaTransporte::limpiarUsuarios()
{
    for (int i = 0; i < cantidadUsuarios; ++i) {
        delete usuarios[i];
        usuarios[i] = nullptr;
    }

    cantidadUsuarios = 0;
}

// ------------------------------------------------------------
// asegurarEspacioUsuarios()
// Que hace: si el arreglo de usuarios esta lleno, crea uno del doble,
//           copia los punteros, libera el anterior y apunta al nuevo.
//           Si todavia hay espacio, no hace nada.
// ------------------------------------------------------------
void SistemaTransporte::asegurarEspacioUsuarios()
{
    if (cantidadUsuarios < capacidadUsuarios) {
        return;
    }

    // Cuando no queda espacio se crea un arreglo mas grande.
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario** nuevos = new Usuario*[nuevaCapacidad];

    for (int i = 0; i < cantidadUsuarios; ++i) {
        nuevos[i] = usuarios[i];
    }

    for (int i = cantidadUsuarios; i < nuevaCapacidad; ++i) {
        nuevos[i] = nullptr;
    }

    delete[] usuarios;
    usuarios = nuevos;
    capacidadUsuarios = nuevaCapacidad;
}

// ------------------------------------------------------------
// asegurarEspacioViajes()
// Que hace: lo mismo que la anterior, pero con el historial de viajes.
// ------------------------------------------------------------
void SistemaTransporte::asegurarEspacioViajes()
{
    if (cantidadViajes < capacidadViajes) {
        return;
    }

    // Los viajes tambien se guardan en un arreglo dinamico.
    int nuevaCapacidad = capacidadViajes * 2;
    Viaje* nuevos = new Viaje[nuevaCapacidad];

    for (int i = 0; i < cantidadViajes; ++i) {
        nuevos[i] = viajes[i];
    }

    delete[] viajes;
    viajes = nuevos;
    capacidadViajes = nuevaCapacidad;
}

// ------------------------------------------------------------
// ultimoViajeDe(posicionUsuario)
// Que hace: recorre el historial de atras hacia adelante y devuelve la
//           posicion del viaje mas reciente de ese usuario, o -1 si no tiene.
// ------------------------------------------------------------
int SistemaTransporte::ultimoViajeDe(int posicionUsuario) const
{
    // Se recorre desde el final para encontrar el viaje mas reciente.
    for (int i = cantidadViajes - 1; i >= 0; --i) {
        if (viajes[i].obtenerUsuario() == posicionUsuario) {
            return i;
        }
    }

    return -1;
}

// Devuelve true si la estacion esta entre 0 y 7.
bool SistemaTransporte::estacionValida(int estacion) const
{
    return estacion >= 0 && estacion < CANT_ESTACIONES;
}

// Devuelve true si el medio es 0 (Bus), 1 (Metro) o 2 (Tranvia).
bool SistemaTransporte::medioValido(int medio) const
{
    return medio >= 0 && medio < CANT_MEDIOS;
}

// Devuelve true si el tipo de usuario es 0, 1 o 2.
bool SistemaTransporte::tipoValido(int tipo) const
{
    return tipo >= 0 && tipo < CANT_TIPOS;
}

// ------------------------------------------------------------
// medioPasaPor(medio, estacion)
// Que hace: recorre la fila RUTAS[medio] (i = 0 .. 4) buscando la estacion.
// Devuelve: true si la encuentra, false si termina el ciclo sin hallarla.
// ------------------------------------------------------------
bool SistemaTransporte::medioPasaPor(int medio, int estacion) const
{
    if (!medioValido(medio) || !estacionValida(estacion)) {
        return false;
    }

    for (int i = 0; i < LONG_RUTA; ++i) {
        if (RUTAS[medio][i] == estacion) {
            return true;
        }
    }

    return false;
}

// ------------------------------------------------------------
// rutaValida(medio, origen, destino)
// Que hace: el viaje es posible si el medio pasa por el origen Y por el
//           destino. Como cada ruta es una sola linea, vale en ambos sentidos.
// ------------------------------------------------------------
bool SistemaTransporte::rutaValida(int medio, int origen, int destino) const
{
    bool origenDisponible = medioPasaPor(medio, origen);
    bool destinoDisponible = medioPasaPor(medio, destino);

    return origenDisponible && destinoDisponible;
}

// ------------------------------------------------------------
// esEstacionConexion(estacion)
// Que hace: cuenta cuantos medios pasan por la estacion.
// Devuelve: true si pasan 2 o mas (ahi se puede hacer transbordo).
// ------------------------------------------------------------
bool SistemaTransporte::esEstacionConexion(int estacion) const
{
    if (!estacionValida(estacion)) {
        return false;
    }

    int mediosQuePasan = 0;

    for (int medio = 0; medio < CANT_MEDIOS; ++medio) {
        if (medioPasaPor(medio, estacion)) {
            ++mediosQuePasan;
        }
    }

    return mediosQuePasan >= 2;
}

// ------------------------------------------------------------
// dniValido(dni)
// Que hace: revisa que el DNI tenga exactamente 8 caracteres y que todos
//           sean digitos del 0 al 9.
// ------------------------------------------------------------
bool SistemaTransporte::dniValido(const string& dni) const {
    if (dni.length() != 8) {
        return false;
    }

    for (int i = 0; i < 8; ++i) {
        if (dni[i] < '0' || dni[i] > '9') {
            return false;
        }
    }

    return true;
}

// ------------------------------------------------------------
// buscarUsuarioPorDni(dni)
// Que hace: busqueda lineal en el arreglo de usuarios.
// Devuelve: la posicion del usuario, o -1 si no existe.
// ------------------------------------------------------------
int SistemaTransporte::buscarUsuarioPorDni(const string& dni) const
{
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (usuarios[i]->obtenerDni() == dni) {
            return i;
        }
    }

    return -1;
}

// ------------------------------------------------------------
// registrarUsuario(nombre, dni, tipo)
// Que hace: 1) valida nombre, DNI y tipo; 2) revisa que el DNI no exista;
//           3) asegura espacio; 4) genera los codigos U00X y T00X;
//           5) crea con new el tipo de usuario elegido (con su tarjeta).
// Devuelve: OK, ERR_DNI o ERR_DNI_REPETIDO.
// ------------------------------------------------------------
int SistemaTransporte::registrarUsuario(const string& nombre, const string& dni, int tipo)
{
    if (nombre.empty() || !dniValido(dni) || !tipoValido(tipo)) {
        return ERR_DNI;
    }

    if (buscarUsuarioPorDni(dni) != -1) {
        return ERR_DNI_REPETIDO;
    }

    asegurarEspacioUsuarios();

    int numero = cantidadUsuarios + 1;
    string codigoUsuario = codigoConCeros("U", numero);
    string codigoTarjeta = codigoConCeros("T", numero);

    if (tipo == REGULAR) {
        usuarios[cantidadUsuarios] = new UsuarioRegular(codigoUsuario, nombre, dni, codigoTarjeta);
    } else if (tipo == ESTUDIANTE) {
        usuarios[cantidadUsuarios] = new UsuarioEstudiante(codigoUsuario, nombre, dni, codigoTarjeta);
    } else {
        usuarios[cantidadUsuarios] = new UsuarioAdultoMayor(codigoUsuario, nombre, dni, codigoTarjeta);
    }

    ++cantidadUsuarios;

    return OK;
}

// ------------------------------------------------------------
// recargarTarjeta(posicionUsuario, monto)
// Que hace: busca la tarjeta del usuario y le pide recargar el monto.
//           No revisa si la tarjeta esta activa: una inactiva tambien se recarga.
// Devuelve: OK, ERR_USUARIO o ERR_MONTO.
// ------------------------------------------------------------
int SistemaTransporte::recargarTarjeta(int posicionUsuario, int monto)
{
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) {
        return ERR_USUARIO;
    }

    if (usuarios[posicionUsuario]->obtenerTarjeta().recargar(monto)) {
        return OK;
    }

    return ERR_MONTO;
}

// ------------------------------------------------------------
// cambiarEstadoTarjeta(posicionUsuario, activa)
// Que hace: activa (true) o desactiva (false) la tarjeta del usuario.
// Devuelve: OK o ERR_USUARIO.
// ------------------------------------------------------------
int SistemaTransporte::cambiarEstadoTarjeta(int posicionUsuario, bool activa)
{
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) {
        return ERR_USUARIO;
    }

    usuarios[posicionUsuario]->obtenerTarjeta().cambiarEstado(activa);

    return OK;
}

// ------------------------------------------------------------
// calcularTarifa(usuario, medio, transbordo)
// Que hace: 1) toma la tarifa base del medio (Bus 150, Metro 200, Tranvia 180);
//           2) aplica el descuento del usuario con obtenerDescuento()
//              (POLIMORFISMO: cada tipo responde su propio %);
//           3) si es transbordo, aplica 50 % adicional sobre ese resultado.
// El "+ 50" antes de dividir entre 100 redondea al centimo mas cercano,
// porque la division entera corta los decimales.
// Ejemplo:  estudiante en Bus con transbordo: 150 -> 105 -> 53 (S/ 0.53).
// Devuelve: la tarifa en centimos.
// ------------------------------------------------------------
int SistemaTransporte::calcularTarifa(const Usuario& usuario, int medio, bool transbordo) const
{
    int tarifa = TARIFAS_BASE[medio];
    int descuento = usuario.obtenerDescuento();

    tarifa = (tarifa * (100 - descuento) + 50) / 100;

    if (transbordo) {
        tarifa = (tarifa * 50 + 50) / 100;
    }

    return tarifa;
}

// ------------------------------------------------------------
// esTransbordo(posicionUsuario, origen, medio, minutosNuevo)
// Que hace: compara el viaje nuevo con el ultimo viaje del mismo usuario.
// Es transbordo si se cumplen las 5 condiciones a la vez:
//   1. tiene un viaje anterior          2. cambio de medio
//   3. sube donde bajo antes            4. es estacion de conexion
//   5. pasaron entre 0 y 30 minutos
// ------------------------------------------------------------
bool SistemaTransporte::esTransbordo(int posicionUsuario, int origen, int medio, int minutosNuevo) const {
    int posicionUltimo = ultimoViajeDe(posicionUsuario);
    if (posicionUltimo == -1) return false;
    const Viaje& anterior = viajes[posicionUltimo];
    int diferencia = minutosNuevo - anterior.obtenerMinutosAbsolutos();
    return anterior.obtenerMedio() != medio && anterior.obtenerDestino() == origen &&
           esEstacionConexion(origen) && diferencia >= 0 && diferencia <= 30;
}

// ------------------------------------------------------------
// registrarViaje(...)  -- el proceso central del sistema
// Paso 1, validar en orden (si una falla, devuelve su error y no cobra):
//   usuario existe, tarjeta activa, estaciones validas, origen != destino,
//   medio valido, ruta valida, fecha y hora validas, y que no sea anterior
//   al ultimo viaje del usuario.
// Paso 2, cobrar: revisa transbordo, calcula la tarifa, compara con el
//   saldo, descuenta y guarda el viaje en el historial.
// tarifaCobrada y fueTransbordo son punteros de salida: ahi se devuelven
// la tarifa y si hubo transbordo (pueden ser NULL si no se necesitan).
// ------------------------------------------------------------
int SistemaTransporte::registrarViaje(int posicionUsuario, int origen, int destino, int medio, int fecha, int hora,
                                      int* tarifaCobrada, bool* fueTransbordo) {
    if (tarifaCobrada != NULL) {
        *tarifaCobrada = 0;
    }

    if (fueTransbordo != NULL) {
        *fueTransbordo = false;
    }
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) return ERR_USUARIO;
    if (!usuarios[posicionUsuario]->obtenerTarjeta().estaActiva()) {
        return ERR_TARJETA_INACTIVA;
    }
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
    int tarifa = calcularTarifa(*usuarios[posicionUsuario], medio, transbordo);

    if (usuarios[posicionUsuario]->obtenerTarjeta().consultarSaldo() < tarifa) {
        return ERR_SALDO;
    }

    asegurarEspacioViajes();
    usuarios[posicionUsuario]->obtenerTarjeta().descontar(tarifa);
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

// ------------------------------------------------------------
// imprimirViaje(viaje, numero)
// Que hace: muestra un viaje en una linea: usuario, ruta, medio, fecha,
//           tarifa y si fue transbordo.
// ------------------------------------------------------------
void SistemaTransporte::imprimirViaje(const Viaje& viaje, int numero) const {
    const Usuario& usuario = *usuarios[viaje.obtenerUsuario()];
    cout << numero << ". " << usuario.obtenerNombre() << " (" << usuario.obtenerCodigo() << ") | "
         << NOMBRES_ESTACION[viaje.obtenerOrigen()] << " -> " << NOMBRES_ESTACION[viaje.obtenerDestino()]
         << " | " << NOMBRES_MEDIO[viaje.obtenerMedio()] << " | "
         << fechaHoraTexto(viaje.obtenerFecha(), viaje.obtenerHora()) << " | "
         << montoTexto(viaje.obtenerTarifa()) << " | "
         << (viaje.esTransbordo() ? "Transbordo" : "Viaje normal") << '\n';
}

// ------------------------------------------------------------
// mostrarUsuarios()
// Que hace: lista cada usuario con su DNI, tipo y tarjeta.
//           La tarjeta se imprime con el operador << sobrecargado.
// ------------------------------------------------------------
void SistemaTransporte::mostrarUsuarios() const {
    if (cantidadUsuarios == 0) {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    cout << "\nUSUARIOS\n";
    for (int i = 0; i < cantidadUsuarios; ++i) {
        const Usuario& u = *usuarios[i];
        cout << u.obtenerCodigo() << " | " << u.obtenerNombre() << " | DNI " << u.obtenerDni() << " | "
             << NOMBRES_TIPO[u.obtenerTipo()] << " | " << u.obtenerTarjeta() << '\n';
    }
}

// ------------------------------------------------------------
// mostrarHistorial(posicionUsuario)
// Que hace: muestra todos los viajes (-1) o solo los de un usuario.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// mostrarEstadisticas()
// Que hace: recorre el historial UNA vez y cuenta: viajes por medio,
//           apariciones de cada estacion (origen + destino), recaudacion
//           y transbordos. Luego busca la estacion con mas apariciones.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// mostrarRed()
// Que hace: muestra las estaciones (marcando las de conexion), las rutas
//           de cada medio con su tarifa y los descuentos.
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// cargarDatosDemo()  -- opcion 9 del menu
// Que hace: borra lo registrado y carga 5 usuarios y 12 intentos de viaje.
// Resultado esperado: 9 aceptados y 3 rechazados; Bus 5, Metro 2,
// Tranvia 2, recaudacion S/ 9.94, Norte con 4 y 3 transbordos.
// ------------------------------------------------------------
void SistemaTransporte::cargarDatosDemo() {
    limpiarUsuarios();
    cantidadViajes = 0;
    registrarUsuario("Ana Torres", "70000001", REGULAR);
    registrarUsuario("Luis Quispe", "70000002", ESTUDIANTE);
    registrarUsuario("Rosa Huaman", "70000003", ADULTO_MAYOR);
    registrarUsuario("Diego Ramos", "70000004", ESTUDIANTE);
    registrarUsuario("Carla Mendoza", "70000005", REGULAR);
    recargarTarjeta(0, 2000);
    recargarTarjeta(1, 1500);
    recargarTarjeta(2, 1000);
    recargarTarjeta(3, 200);
    recargarTarjeta(4, 500);
    cambiarEstadoTarjeta(4, false);

    int tarifa;
    bool transbordo;
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

// ------------------------------------------------------------
// verificar(nombre, condicion, aprobadas, total)
// Que hace: imprime [OK] o [FALLO] para una prueba y actualiza los
//           contadores (por referencia).
// ------------------------------------------------------------
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

// ------------------------------------------------------------
// ejecutarPruebas()  -- opcion 10 del menu
// Que hace: ejecuta 15 pruebas internas de fechas, horas, DNI, rutas,
//           conexiones, tarifas, redondeo y tiempos de transbordo.
// ------------------------------------------------------------
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
    UsuarioEstudiante estudiante("U001", "Prueba", "70000001", "T001");
    UsuarioAdultoMayor adultoMayor("U002", "Prueba", "70000002", "T002");

    verificar("Tarifa estudiante en Metro", calcularTarifa(estudiante, METRO, false) == 140, aprobadas, total);
    verificar("Tarifa estudiante con transbordo", calcularTarifa(estudiante, METRO, true) == 70, aprobadas, total);
    verificar("Redondeo adulto mayor con transbordo", calcularTarifa(adultoMayor, BUS, true) == 38,
              aprobadas, total);
    verificar("30 minutos exactos entre viajes", minutosAbsolutos(20261005, 1030) - minutosAbsolutos(20261005, 1000) == 30,
              aprobadas, total);
    verificar("Transbordo que cruza medianoche", minutosAbsolutos(20261006, 10) - minutosAbsolutos(20261005, 2350) == 20,
              aprobadas, total);
    cout << "Resultado: " << aprobadas << " de " << total << " pruebas aprobadas.\n";
}

// Devuelve cuantos usuarios hay registrados.
int SistemaTransporte::obtenerCantidadUsuarios() const
{
    return cantidadUsuarios;
}

// Devuelve cuantos viajes hay en el historial.
int SistemaTransporte::obtenerCantidadViajes() const
{
    return cantidadViajes;
}

// ------------------------------------------------------------
// obtenerSaldo(posicionUsuario)
// Devuelve: el saldo de la tarjeta en centimos, o -1 si el usuario no existe.
// ------------------------------------------------------------
int SistemaTransporte::obtenerSaldo(int posicionUsuario) const {
    if (posicionUsuario < 0 || posicionUsuario >= cantidadUsuarios) {
        return -1;
    }

    return usuarios[posicionUsuario]->obtenerTarjeta().consultarSaldo();
}
