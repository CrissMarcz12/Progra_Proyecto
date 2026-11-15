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
