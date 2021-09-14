/**
    GNU GCC 8.1 C++17
    datos.h
    Purpose: Gestiona la estructura de datos y la persistencia de la aplicación InstaFilm

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef DATOS_H
#define DATOS_H

#include <string>

// Cantidad máxima de campos por registro del archivo de datos.
const int MAX_CAMPOS = 100;

// Cantidad máxima de registros del archivo de datos.
const int MAX_REGISTROS = 10000;

// Nombre del archivo del módulo de usuarios de InstaFilm.
const std::string NOMBRE_ARCHIVO_USUARIOS = "usuarios.csv";

// Nombre del archivo del módulo de películas de InstaFilm.
const std::string NOMBRE_ARCHIVO_PELICULAS = "peliculas.csv";

// Nombre del archivo del módulo de amigos de InstaFilm.
const std::string NOMBRE_ARCHIVO_AMIGOS = "amigos.csv";

// Nombre del archivo del módulo de películas favoritas de InstaFilm.
const std::string NOMBRE_ARCHIVO_FAVORITAS = "favoritas.csv";

// Nombre del archivo del módulo de estadísticas de juegos de InstaFilm.
const std::string NOMBRE_ARCHIVO_JUEGOS = "juegos.csv";

// Caracter separador de campos del registro del archivo de datos.
const char SEPARADOR = '|';

// Caracter separador de los datos de una fecha: dd/mm/aaaa.
const char SEPARADOR_FECHA = '/';

// Estructura de los datos tipo fecha.
struct fecha
{
    int dia;
    int mes;
    int anio;
};

// Estructura de datos para un usuario del sistema.
struct usuario
{
    // Nombre del usuario del sistema
    std::string alias;

    // Contraseña del usuario del sistema
    std::string contrasenia;

    // Nombres de la persona
    std::string nombres;

    // Son públicos los nombres de la persona?
    bool nombres_publico;

    // Apellidos de la persona
    std::string apellidos;

    // Son públicos los apellidos de la persona?
    bool apellidos_publico;

    // Género de la persona ('f': femenino, 'm': masculino)
    char genero;

    // Es público el género de la persona?
    bool genero_publico;

    // Cuenta de correo electrónico de la persona
    std::string email;

    // Es pública la cuenta de correo de la persona?
    bool email_publico;

    // Fecha de nacimiento de la persona
    fecha fecha_nacimiento;

    // Es pública la fecha de nacimiento?
    bool fecha_nacimiento_publico;

    // Es administrador de la aplicación?
    bool administrador;

    // Está activo el usuario?
    bool activo;
};

// Estructura de datos para las películas.
struct pelicula
{
    // Código de la película
    int codigo;

    // Nombre de la película
    std::string nombre;

    // Género de la película
    std::string genero;

    // Resumen de la película
    std::string descripcion;
};

// Estructura de datos para relaciones de amistad.
struct amigo
{
    std::string alias_anfitrion;
    std::string alias_invitado;
    bool solicitud;
};

// Estructura de datos para el gusto de películas.
//  alias Usuario
//  codigo Código de la Película
struct favorita
{
    std::string alias;
    int codigo;
};

// Estadisticas de juegos.
struct estadistica
{
    std::string alias;
    std::string juego;
    int resultado;
};

/**
    Parte (divide) una cadena de caracteres en un arreglo de strings según el delimitador.

    @param linea La cadena de caracteres a partir.
    @param delimitador
    @param campos Campos resultantes de la partición de la línea de texto.
    @return La cantidad de campos del arreglo resultante
*/
int partir(std::string linea, char delimitador, std::string campos[]);

/**
    Compara dos fechas.

    @param fecha1 La fecha de referencia a comparar
    @param fecha2 La segunda fecha a comparar
    @return -1: fecha1 < fecha2; 0: las fechas son iguales; 1: fecha1 > fecha2
*/
int compare_fechas(fecha fecha1, fecha fecha2);

/**
    Determina si un archivo existe.

    @param nombre_archivo Nombre del archivo a buscar
    @return Si el archivo existe (true)
*/
bool existe_archivo(const char *nombre_archivo);

/**
    Lee desde disco el archivo de usuarios y lo almacena en el arreglo usuarios.

    @param usuarios El arreglo de usuarios.
    @return La cantidad de usuarios encontrados en el archivo.
*/
int leer_archivo_usuarios(usuario usuarios[]);

/**
    Agrega (guarda) un usuario al archivo de usuarios.

    @param nuevo_usuario El usuario a agregar al archivo.
*/
void agregar_usuario_archivo(usuario nuevo_usuario);

/**
    Actualiza el archivo de usuarios con un arreglo de usuarios.

    @param usuarios El arreglo de usuarios a almacenar en el archivo.
    @param cantidad_usuarios Cantidad de usuarios a almacenar en el archivo.
*/
void actualizar_archivo_usuarios(usuario usuarios[], int cantidad_usuarios);

/**
    Convierte la estructura de un usuario en una línea de texto para guardarla en el archivo.

    @param usuario1 Estructura usuario a convertir.
    @return Cadena de caracteres con los datos del usuario para almacenarla en el archivo.
*/
std::string estructura_archivo_usuarios(usuario usuario1);

/**
    Convierte un registro del archivo a una estructura de usuario.

    @param linea Registro del archivo de texto.
    @param cantidad_campos Candidad de campos a extraer del registro del archivo.
    @return Estructura de datos de un usuario.
*/
usuario archivo_estructura_usuarios(std::string linea, int cantidad_campos);

/**
    Lee desde disco el archivo de películas y lo almacena en el arreglo películas.

    @param peliculas El arreglo de películas.
    @return La cantidad de películas encontradas en el archivo.
*/
int leer_archivo_peliculas(pelicula peliculas[]);

/**
    Convierte un registro del archivo a una estructura de película.

    @param linea Registro del archivo de texto.
    @param cantidad_campos Candidad de campos a extraer del registro del archivo.
    @return Estructura de datos de una película.
*/
pelicula archivo_estructura_peliculas(std::string linea, int cantidad_campos);

/**
    Agrega (guarda) una película al archivo de películas.

    @param nueva_pelicula La película a agregar al archivo.
*/
void agregar_pelicula_archivo(pelicula nueva_pelicula);

/**
    Convierte la estructura de una película en una línea de texto para guardarla en el archivo.

    @param pelicula1 Estructura película a convertir.
    @return Cadena de caracteres con los datos de la película para almacenarla en el archivo.
*/
std::string estructura_archivo_pelicula(pelicula pelicula1);

/**
    Genera automáticamente el código para una nueva película.

    @return Código de la película.
*/
int nuevo_codigo_pelicula();

/**
    Actualiza el archivo de películas con un arreglo de películas.

    @param peliculas El arreglo de películas a almacenar en el archivo.
    @param cantidad_peliculas Cantidad de películas a almacenar en el archivo.
*/
void actualizar_archivo_peliculas(pelicula peliculas[], int cantidad_peliculas);

/**
    Lee desde disco el archivo de amigos y lo almacena en el arreglo amigos.

    @param amigos Arreglo de amigos.
    @return Cantidad de amigos.
*/
int leer_archivo_amigos(amigo amigos[]);

/**
    Convierte un registro del archivo a una estructura de amigos.

    @param linea Linea de texto a convertir en la estructura de amigos.
    @param cantidad_campos Cantidad de campos.
    @return Estructura de amigos.
*/
amigo archivo_estructura_amigos(std::string linea, int cantidad_campos);

/**
    Agrega (guarda) una amistad al archivo de amigos.

    @param nueva_amistad La amistad a agregar al archivo.
*/
void agregar_amistad_archivo(amigo nueva_amistad);

/**
    Convierte la estructura de una amistad en una línea de texto para guardarla en el archivo.

    @param amigo1 Estructura amistad a convertir.
    @return Cadena de caracteres con los datos de la amistad para almacenarla en el archivo.
*/
std::string estructura_archivo_amigos(amigo amigo1);

/**
    Actualiza el archivo de amistades con un arreglo de amistades.

    @param amigos El arreglo de amistades a almacenar en el archivo.
    @param cantidad_amistades Cantidad de amistades a almacenar en el archivo.
*/
void actualizar_archivo_amigos(amigo amigos[], int cantidad_amigos);

/**
    Lee desde disco el archivo de películas favoritas y lo almacena en el arreglo favoritas.

    @param amigos Arreglo de películas favoritas.
    @return Cantidad de películas favoritas.
*/
int leer_archivo_favoritas(favorita favoritas[]);

/**
    Convierte un registro del archivo a una estructura de amigos.

    @param linea Línea de texto a convertir en estructura.
    @param cantidad_campos Cantidad de campos.
    @return La estructura de películas favoritas.
*/
favorita archivo_estructura_favoritas(std::string linea, int cantidad_campos);

/**
    Agrega (guarda) una nueva película favorita al archivo de favoritas.

    @param nueva_favorita La nueva película favorita para agregar al archivo.
*/
void agregar_favorita_archivo(favorita nueva_favorita);

/**
    Convierte la estructura de una película favorita en una línea de texto para guardarla en el archivo.

    @param favorita1 Estructura de pelíclas favoritas a convertir.
    @return Cadena de caracteres con los datos de la película favorita para almacenarla en el archivo.
*/
std::string estructura_archivo_favoritas(favorita favorita1);

/**
    Actualiza el archivo de películas favoritas con un arreglo de favoritas.

    @param favoritas El arreglo de películas favoritas a almacenar en el archivo.
    @param cantidad_favoritas Cantidad de películas favoritas a almacenar en el archivo.
*/
void actualizar_archivo_favoritas(favorita favoritas[], int cantidad_favoritas);

/**
    Lee desde disco el archivo de estadísticas y lo almacena en el arreglo estadísticas.

    @param estadisticas Arreglo de estadísticas.
    @return Cantidad de estadísticas.
*/
int leer_archivo_estadisticas(estadistica estadisticas[]);

/**
    Convierte un registro del archivo a una estructura de estadísticas.

    @param linea Línea de texto a convertir en estructura.
    @param cantidad_campos Cantidad de campos.
    @return La estructura de estadísticas.
*/
estadistica archivo_estructura_estadisticas(std::string linea, int cantidad_campos);

/**
    Agrega (guarda) una estadística al archivo de estadísticas.

    @param nueva_estadistica La nueva estadística para agregar al archivo.
*/
void agregar_estadistica_archivo(estadistica nueva_estadistica);

/**
    Convierte la estructura de una estadística en una línea de texto para guardarla en el archivo.

    @param estadistica1 Estructura de estadísticas a convertir.
    @return Cadena de caracteres con los datos de estadísticas para almacenarla en el archivo.
*/
std::string estructura_archivo_estadisticas(estadistica estadistica1);

/**
    Actualiza el archivo de estadísticas con un arreglo de estadísticas.

    @param estadisticas El arreglo de estadísticas a almacenar en el archivo.
    @param cantidad_estadisticas Cantidad de estadísticas a almacenar en el archivo.
*/
void actualizar_archivo_estadisticas(estadistica estadisticas[], int cantidad_estadisticas);

#endif // DATOS_H
