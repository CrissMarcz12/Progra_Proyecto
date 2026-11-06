#ifndef PROYECTIO_BUZZIO_CONSTANTES_H
#define PROYECTIO_BUZZIO_CONSTANTES_H

extern const int CANT_ESTACIONES;
extern const int CANT_MEDIOS;
extern const int CANT_TIPOS;
extern const int LONG_RUTA;
extern const int CAPACIDAD_INICIAL;
extern const int RECARGA_MAXIMA;

extern const int BUS;
extern const int METRO;
extern const int TRANVIA;

extern const int REGULAR;
extern const int ESTUDIANTE;
extern const int ADULTO_MAYOR;

extern const int OK;
extern const int ERR_USUARIO;
extern const int ERR_TARJETA_INACTIVA;
extern const int ERR_ESTACION;
extern const int ERR_MISMA_ESTACION;
extern const int ERR_MEDIO;
extern const int ERR_RUTA;
extern const int ERR_FECHA_HORA;
extern const int ERR_CRONOLOGIA;
extern const int ERR_SALDO;
extern const int ERR_MONTO;
extern const int ERR_DNI;
extern const int ERR_DNI_REPETIDO;

extern const char* CODIGOS_ESTACION[];
extern const char* NOMBRES_ESTACION[];
extern const char* NOMBRES_MEDIO[];
extern const int TARIFAS_BASE[];
extern const char* NOMBRES_TIPO[];
extern const int DESCUENTOS[];
extern const int RUTAS[3][5];

#endif
