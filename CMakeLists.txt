# ==============================================================
# Archivo:  CMakeLists.txt
# Proyecto: Sistema Integrado de Gestion de Transporte Publico
#           Programacion II (CS6003) - UTEC 2026-II
#
# Que tiene este archivo:
#   - La configuracion para compilar el proyecto con CMake (CLion la usa sola).
#   - Estandar C++11 y la lista de archivos .cpp que forman el ejecutable.
#   - headers/ se agrega como carpeta de includes.
# ==============================================================

cmake_minimum_required(VERSION 3.20)
project(Proyectio_Buzzio)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Proyectio_Buzzio
        main.cpp
        clases/Constantes.cpp
        clases/Utilidades.cpp
        clases/Tarjeta.cpp
        clases/Usuario.cpp
        clases/UsuarioRegular.cpp
        clases/UsuarioEstudiante.cpp
        clases/UsuarioAdultoMayor.cpp
        clases/Viaje.cpp
        clases/SistemaTransporte.cpp
        clases/Consola.cpp)

target_include_directories(Proyectio_Buzzio PRIVATE headers)
