# Sistema Integrado de Gestion de Transporte Publico

Proyecto de Programacion II para CLion. Implementa la propuesta del grupo con POO, punteros y arreglos dinamicos (`new[]` y `delete[]`), sin `vector` ni otros contenedores STL. El archivo `main.cpp` solo crea el sistema y ejecuta la aplicacion.

## Abrir en CLion

1. Abre la carpeta `Proyectio_Buzzio` como proyecto.
2. CLion detectara `CMakeLists.txt`; selecciona un compilador C++ configurado en el IDE.
3. Ejecuta la configuracion `Proyectio_Buzzio`.

## Opciones principales

El menu permite registrar usuarios, recargar y cambiar el estado de tarjetas, registrar viajes, consultar el historial, ver estadisticas y la red. La opcion 9 carga los cinco usuarios y los doce intentos definidos en la propuesta; se aceptan nueve viajes. La opcion 10 comprueba reglas de fechas, rutas, DNI, tarifas, redondeo y transbordos.

Los importes se guardan como centimos enteros para evitar problemas de redondeo. Por ejemplo, para cargar diez soles se ingresa `10.00`.

## Carpetas

- `headers/`: declaraciones de las clases y funciones.
- `clases/`: codigo de las clases, las constantes, utilidades y menu.
- `main.cpp`: crea el sistema y ejecuta el menu.
