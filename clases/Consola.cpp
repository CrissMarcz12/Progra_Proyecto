#include "Consola.h"
#include "Constantes.h"
#include "Utilidades.h"

#include <iostream>
#include <string>

using namespace std;

string leerLinea(const string& mensaje)
{
    cout << mensaje;

    string texto;
    getline(cin, texto);

    return texto;
}

int leerEntero(const string& mensaje, int minimo, int maximo)
{
    while (true) {
        int valor;

        cout << mensaje;
        cin >> valor;

        if (!cin.fail() && valor >= minimo && valor <= maximo) {
            cin.ignore(1000, '\n');
            return valor;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ingrese un numero entero entre " << minimo << " y " << maximo << ".\n";
    }
}

int leerMontoEnCentimos(const string& mensaje)
{
    while (true) {
        int monto;
        string texto = leerLinea(mensaje);

        if (convertirMontoACentimos(texto, monto)) {
            return monto;
        }

        cout << "Ingrese un monto con hasta dos decimales. Ejemplo: 12.50\n";
    }
}

int buscarUsuarioDesdeConsola(const SistemaTransporte& sistema)
{
    string dni = leerLinea("DNI del usuario: ");
    int posicion = sistema.buscarUsuarioPorDni(dni);

    if (posicion == -1) {
        cout << "No existe un usuario con ese DNI.\n";
    }

    return posicion;
}

const char* mensajeError(int codigo)
{
    switch (codigo) {
        case 0:
            return "Operacion realizada correctamente.";
        case 1:
            return "El usuario no existe.";
        case 2:
            return "La tarjeta esta inactiva.";
        case 3:
            return "La estacion es invalida.";
        case 4:
            return "El origen y el destino no pueden ser iguales.";
        case 5:
            return "El medio de transporte es invalido.";
        case 6:
            return "El medio no conecta las estaciones indicadas.";
        case 7:
            return "La fecha o la hora son invalidas.";
        case 8:
            return "La fecha y hora son anteriores al ultimo viaje de la tarjeta.";
        case 9:
            return "Saldo insuficiente para realizar el viaje.";
        case 10:
            return "Monto de recarga invalido. Debe ser mayor que cero y no superar S/ 500.00.";
        case 11:
            return "Datos invalidos. El DNI debe tener exactamente 8 digitos.";
        case 12:
            return "Ya existe un usuario con ese DNI.";
        default:
            return "Error no identificado.";
    }
}

void mostrarMenu()
{
    cout << "\n==============================================\n";
    cout << " SISTEMA INTEGRADO DE GESTION DE TRANSPORTE\n";
    cout << "==============================================\n";
    cout << " 1. Registrar usuario\n";
    cout << " 2. Recargar tarjeta\n";
    cout << " 3. Consultar saldo\n";
    cout << " 4. Activar o desactivar tarjeta\n";
    cout << " 5. Registrar viaje\n";
    cout << " 6. Ver historial de viajes\n";
    cout << " 7. Ver estadisticas\n";
    cout << " 8. Ver red de transporte\n";
    cout << " 9. Cargar datos de demostracion\n";
    cout << "10. Ejecutar pruebas\n";
    cout << "11. Ver usuarios\n";
    cout << " 0. Salir\n";
}

void opcionRegistrarUsuario(SistemaTransporte& sistema)
{
    string nombre;

    do {
        nombre = leerLinea("Nombre completo: ");

        if (nombre.empty()) {
            cout << "El nombre no puede estar vacio.\n";
        }
    } while (nombre.empty());

    string dni = leerLinea("DNI (8 digitos): ");

    cout << "Tipo de usuario: 0. Regular  1. Estudiante  2. Adulto mayor\n";
    int tipo = leerEntero("Opcion: ", 0, 2);
    int resultado = sistema.registrarUsuario(nombre, dni, tipo);

    cout << mensajeError(resultado) << '\n';
}

void opcionRecargar(SistemaTransporte& sistema)
{
    int usuario = buscarUsuarioDesdeConsola(sistema);

    if (usuario == -1) {
        return;
    }

    int monto = leerMontoEnCentimos("Monto a recargar (ejemplo 10.50): ");
    int resultado = sistema.recargarTarjeta(usuario, monto);

    cout << mensajeError(resultado) << '\n';

    if (resultado == OK) {
        cout << "Nuevo saldo: " << montoTexto(sistema.obtenerSaldo(usuario)) << '\n';
    }
}

void opcionConsultarSaldo(const SistemaTransporte& sistema)
{
    int usuario = buscarUsuarioDesdeConsola(sistema);

    if (usuario != -1) {
        cout << "Saldo actual: " << montoTexto(sistema.obtenerSaldo(usuario)) << '\n';
    }
}

void opcionEstadoTarjeta(SistemaTransporte& sistema)
{
    int usuario = buscarUsuarioDesdeConsola(sistema);

    if (usuario == -1) {
        return;
    }

    int opcion = leerEntero("1. Activar  2. Desactivar: ", 1, 2);
    int resultado = sistema.cambiarEstadoTarjeta(usuario, opcion == 1);

    cout << mensajeError(resultado) << '\n';
}

void opcionRegistrarViaje(SistemaTransporte& sistema)
{
    int usuario = buscarUsuarioDesdeConsola(sistema);

    if (usuario == -1) {
        return;
    }

    cout << "Estaciones: 0 Norte, 1 Central, 2 Mercado, 3 Hospital, 4 Terminal, 5 Sur, 6 Universidad, 7 Parque\n";
    int origen = leerEntero("Origen: ", 0, 7);
    int destino = leerEntero("Destino: ", 0, 7);

    cout << "Medios: 0 Bus, 1 Metro, 2 Tranvia\n";
    int medio = leerEntero("Medio: ", 0, 2);
    int fecha = leerEntero("Fecha (AAAAMMDD): ", 20000101, 20991231);
    int hora = leerEntero("Hora (HHMM): ", 0, 2359);
    int tarifa;
    bool transbordo;

    int resultado = sistema.registrarViaje(usuario, origen, destino, medio, fecha, hora, &tarifa, &transbordo);

    cout << mensajeError(resultado) << '\n';

    if (resultado == OK) {
        cout << "Tarifa cobrada: " << montoTexto(tarifa) << '\n';

        if (transbordo) {
            cout << "Se aplico descuento por transbordo.\n";
        } else {
            cout << "No corresponde transbordo.\n";
        }

        cout << "Saldo restante: " << montoTexto(sistema.obtenerSaldo(usuario)) << '\n';
    }
}

void opcionHistorial(const SistemaTransporte& sistema)
{
    int opcion = leerEntero("1. Todos los usuarios  2. Un usuario: ", 1, 2);

    if (opcion == 1) {
        sistema.mostrarHistorial();
    } else {
        int usuario = buscarUsuarioDesdeConsola(sistema);

        if (usuario != -1) {
            sistema.mostrarHistorial(usuario);
        }
    }
}

void ejecutarAplicacion(SistemaTransporte& sistema)
{
    cout << "Bienvenido. Los montos se almacenan internamente en centimos.\n";

    int opcion;

    do {
        mostrarMenu();
        opcion = leerEntero("Seleccione una opcion: ", 0, 11);

        switch (opcion) {
            case 1:
                opcionRegistrarUsuario(sistema);
                break;
            case 2:
                opcionRecargar(sistema);
                break;
            case 3:
                opcionConsultarSaldo(sistema);
                break;
            case 4:
                opcionEstadoTarjeta(sistema);
                break;
            case 5:
                opcionRegistrarViaje(sistema);
                break;
            case 6:
                opcionHistorial(sistema);
                break;
            case 7:
                sistema.mostrarEstadisticas();
                break;
            case 8:
                sistema.mostrarRed();
                break;
            case 9:
                sistema.cargarDatosDemo();
                break;
            case 10:
                sistema.ejecutarPruebas();
                break;
            case 11:
                sistema.mostrarUsuarios();
                break;
            case 0:
                cout << "Memoria dinamica liberada. Hasta luego.\n";
                break;
        }
    } while (opcion != 0);
}
