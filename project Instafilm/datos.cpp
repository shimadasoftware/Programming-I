/**
    GNU GCC 8.1 C++17
    datos.cpp
    Purpose: Gestiona la estructura de datos y la persistencia del módulo de usuarios de InstaFilm

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include <fstream>
#include <string>
#include "datos.h"

using namespace std;

// Determina si un archivo existe.
bool existe_archivo(std::string &nombre_archivo)
{
    std::ifstream archivo(nombre_archivo.c_str());
    return archivo.good();
}

// Parte (divide) una cadena de caracteres en un arreglo de strings según el delimitador.
int partir(std::string linea, char delimitador, std::string campos[])
{
    int cantidad_campos = 0;
    std::string temp = "";

    for (unsigned int i = 0; i < linea.length(); i++)
    {
        if (linea.at(i) != delimitador)
        {
            temp += linea.at(i);
        }
        else
        {
            campos[cantidad_campos++] = temp;
            temp = "";
        }
    }

    if (linea.length() > (unsigned)0)
    {
        campos[cantidad_campos++] = temp;
    }

    return cantidad_campos;
}

// Compara dos fechas.
int compare_fechas(fecha fecha1, fecha fecha2)
{
    if (fecha1.anio > fecha2.anio)
    {
        return 1;
    }
    if (fecha1.anio < fecha2.anio)
    {
        return -1;
    }
    if (fecha1.mes > fecha2.mes)
    {
        return 1;
    }
    if (fecha1.mes < fecha2.mes)
    {
        return -1;
    }
    if (fecha1.dia > fecha2.dia)
    {
        return 1;
    }
    if (fecha1.dia < fecha2.dia)
    {
        return -1;
    }
    return 0;
}

// Lee desde disco el archivo de usuarios y lo almacena en el arreglo usuarios.
int leer_archivo_usuarios(usuario usuarios[])
{
    int cantidad_registros = 0;

    std::string nombre_archivo = NOMBRE_ARCHIVO_USUARIOS;
    if (existe_archivo(nombre_archivo))
    {
        std::ifstream archivo;
        archivo.open(nombre_archivo.c_str());
        while (archivo.good())
        {
            std::string linea;
            getline(archivo, linea, '\n');
            usuario usuario1 = archivo_estructura_usuarios(linea, 14);
            if (usuario1.alias.length() > (unsigned)0)
            {
                usuarios[cantidad_registros++] = usuario1;
            }
        }
        archivo.close();
    }

    return cantidad_registros;
}

// Agrega (guarda) un usuario al archivo de usuarios.
void agregar_usuario_archivo(usuario nuevo_usuario)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_USUARIOS;

    if (!existe_archivo(nombre_archivo))
    {
        nuevo_usuario.administrador = true;
    }

    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out | ios::app);
    if (archivo.is_open())
    {
        std::string linea = estructura_archivo_usuarios(nuevo_usuario);
        archivo << linea;
        archivo.close();
    }
}

// Actualiza el archivo de usuarios con un arreglo de usuarios.
void actualizar_archivo_usuarios(usuario usuarios[], int cantidad_usuarios)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_USUARIOS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
        for (int i = 0; i < cantidad_usuarios; i++)
        {
            std::string linea = estructura_archivo_usuarios(usuarios[i]);
            archivo << linea;
        }
        archivo.close();
    }
}

// Convierte la estructura de un usuario en una línea de texto para guardarla en el archivo.
std::string estructura_archivo_usuarios(usuario usuario1)
{
    std::string linea = "";

    linea += usuario1.alias;
    linea += SEPARADOR + usuario1.contrasenia;
    linea += SEPARADOR + usuario1.nombres;
    linea += SEPARADOR + (usuario1.nombres_publico ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + usuario1.apellidos;
    linea += SEPARADOR + (usuario1.apellidos_publico ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + (usuario1.genero == 'f' ? (std::string)"f" : (std::string)"m");
    linea += SEPARADOR + (usuario1.genero_publico ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + usuario1.email;
    linea += SEPARADOR + (usuario1.email_publico ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + std::to_string(usuario1.fecha_nacimiento.dia);
    linea += SEPARADOR_FECHA + std::to_string(usuario1.fecha_nacimiento.mes);
    linea += SEPARADOR_FECHA + std::to_string(usuario1.fecha_nacimiento.anio);
    linea += SEPARADOR + (usuario1.fecha_nacimiento_publico ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + (usuario1.administrador ? (std::string)"1" : (std::string)"0");
    linea += SEPARADOR + (usuario1.activo ? (std::string)"1" : (std::string)"0");
    linea += '\n';

    return linea;
}

// Convierte un registro del archivo a una estructura de usuario.
usuario archivo_estructura_usuarios(std::string linea, int cantidad_campos)
{
    usuario usuario1;
    usuario1.alias = "";

    std::string campos[MAX_CAMPOS];
    int numero_campos = partir(linea, SEPARADOR, campos);

    if ((numero_campos == cantidad_campos) && (campos[0].length() > (unsigned)0))
    {
        usuario1.alias = campos[0];
        usuario1.contrasenia = campos[1];
        usuario1.nombres = campos[2];
        usuario1.nombres_publico = (campos[3].compare("1") == 0);
        usuario1.apellidos = campos[4];
        usuario1.apellidos_publico = (campos[5].compare("1") == 0);
        usuario1.genero = campos[6].at(0);
        usuario1.genero_publico = (campos[7].compare("1") == 0);
        usuario1.email = campos[8];
        usuario1.email_publico = (campos[9].compare("1") == 0);

        std::string campos_fecha[3];
        numero_campos = partir(campos[10], SEPARADOR_FECHA, campos_fecha);
        usuario1.fecha_nacimiento.dia = stoi(campos_fecha[0]);
        usuario1.fecha_nacimiento.mes = stoi(campos_fecha[1]);
        usuario1.fecha_nacimiento.anio = stoi(campos_fecha[2]);

        usuario1.fecha_nacimiento_publico = (campos[11].compare("1") == 0);
        usuario1.administrador = (campos[12].compare("1") == 0);
        usuario1.activo = (campos[13].compare("1") == 0);
    }

    return usuario1;
}

// Lee desde disco el archivo de películas y lo almacena en el arreglo películas.
int leer_archivo_peliculas(pelicula peliculas[])
{
    int cantidad_registros = 0;

    std::string nombre_archivo = NOMBRE_ARCHIVO_PELICULAS;
    if (existe_archivo(nombre_archivo))
    {
        std::ifstream archivo;
        archivo.open(nombre_archivo.c_str());
        while (archivo.good())
        {
            std::string linea;
            getline(archivo, linea, '\n');
            pelicula pelicula1 = archivo_estructura_peliculas(linea, 4);
            if (pelicula1.nombre.length() > (unsigned)0)
            {
                peliculas[cantidad_registros++] = pelicula1;
            }
        }
        archivo.close();
    }

    return cantidad_registros;
}

// Convierte un registro del archivo a una estructura de película.
pelicula archivo_estructura_peliculas(std::string linea, int cantidad_campos)
{
    pelicula pelicula1;
    pelicula1.nombre = "";

    std::string campos[MAX_CAMPOS];
    int numero_campos = partir(linea, SEPARADOR, campos);

    if ((numero_campos == cantidad_campos) && (campos[1].length() > (unsigned)0))
    {
        pelicula1.codigo = stoi(campos[0]);
        pelicula1.nombre = campos[1];
        pelicula1.genero = campos[2];
        pelicula1.descripcion = campos[3];
    }

    return pelicula1;
}

// Agrega (guarda) una película al archivo de películas.
void agregar_pelicula_archivo(pelicula nueva_pelicula)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_PELICULAS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out | ios::app);

    if (archivo.is_open())
    {
        std::string linea = estructura_archivo_pelicula(nueva_pelicula);
        archivo << linea;
        archivo.close();
    }
}

// Convierte la estructura de una película en una línea de texto para guardarla en el archivo.
std::string estructura_archivo_pelicula(pelicula pelicula1)
{
    std::string linea = "";

    linea += std::to_string(pelicula1.codigo);
    linea += SEPARADOR + pelicula1.nombre;
    linea += SEPARADOR + pelicula1.genero;
    linea += SEPARADOR + pelicula1.descripcion;
    linea += '\n';

    return linea;
}

// Genera automáticamente el código para una nueva película.
int nuevo_codigo_pelicula()
{
    pelicula peliculas[MAX_REGISTROS];
    int cantidad_peliculas = leer_archivo_peliculas(peliculas);
    int codigo = 0;

    for (int i = 0; i < cantidad_peliculas; i++)
    {
        if (peliculas[i].codigo > codigo)
        {
            codigo = peliculas[i].codigo;
        }
    }

    return ++codigo;
}

// Actualiza el archivo de películas con un arreglo de películas.
void actualizar_archivo_peliculas(pelicula peliculas[], int cantidad_peliculas)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_PELICULAS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
        for (int i = 0; i < cantidad_peliculas; i++)
        {
            std::string linea = estructura_archivo_pelicula(peliculas[i]);
            archivo << linea;
        }
        archivo.close();
    }
}

// Lee desde disco el archivo de amigos y lo almacena en el arreglo amigos.
int leer_archivo_amigos(amigo amigos[])
{
    int cantidad_registros = 0;

    std::string nombre_archivo = NOMBRE_ARCHIVO_AMIGOS;
    if (existe_archivo(nombre_archivo))
    {
        std::ifstream archivo;
        archivo.open(nombre_archivo.c_str());
        while (archivo.good())
        {
            std::string linea;
            getline(archivo, linea, '\n');
            amigo amigo1 = archivo_estructura_amigos(linea, 3);
            if (amigo1.alias_anfitrion.length() > (unsigned)0)
            {
                amigos[cantidad_registros++] = amigo1;
            }
        }
        archivo.close();
    }

    return cantidad_registros;
}

// Convierte un registro del archivo a una estructura de amigos.
amigo archivo_estructura_amigos(std::string linea, int cantidad_campos)
{
    amigo amigo1;
    amigo1.alias_anfitrion = "";

    std::string campos[MAX_CAMPOS];
    int numero_campos = partir(linea, SEPARADOR, campos);

    if ((numero_campos == cantidad_campos) && (campos[0].length() > (unsigned)0))
    {
        amigo1.alias_anfitrion = campos[0];
        amigo1.alias_invitado = campos[1];
        amigo1.solicitud = (campos[2].compare("1") == 0);
    }

    return amigo1;
}

// Agrega (guarda) una amistad al archivo de amigos.
void agregar_amistad_archivo(amigo nueva_amistad)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_AMIGOS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out | ios::app);
    if (archivo.is_open())
    {
        std::string linea = estructura_archivo_amigos(nueva_amistad);
        archivo << linea;
        archivo.close();
    }
}

// Convierte la estructura de una amistad en una línea de texto para guardarla en el archivo.
std::string estructura_archivo_amigos(amigo amigo1)
{
    std::string linea = "";

    linea += amigo1.alias_anfitrion;
    linea += SEPARADOR + amigo1.alias_invitado;
    linea += SEPARADOR + (amigo1.solicitud ? (std::string)"1" : (std::string)"0");
    linea += '\n';

    return linea;
}

// Actualiza el archivo de amistades con un arreglo de amistades.
void actualizar_archivo_amigos(amigo amigos[], int cantidad_amigos)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_AMIGOS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
        for (int i = 0; i < cantidad_amigos; i++)
        {
            std::string linea = estructura_archivo_amigos(amigos[i]);
            archivo << linea;
        }
        archivo.close();
    }
}

// Lee desde disco el archivo de películas favoritas y lo almacena en el arreglo favoritas.
int leer_archivo_favoritas(favorita favoritas[])
{
    int cantidad_registros = 0;

    std::string nombre_archivo = NOMBRE_ARCHIVO_FAVORITAS;
    if (existe_archivo(nombre_archivo))
    {
        std::ifstream archivo;
        archivo.open(nombre_archivo.c_str());
        while (archivo.good())
        {
            std::string linea;
            getline(archivo, linea, '\n');
            favorita favorita1 = archivo_estructura_favoritas(linea, 2);
            if (favorita1.alias.length() > (unsigned)0)
            {
                favoritas[cantidad_registros++] = favorita1;
            }
        }
        archivo.close();
    }

    return cantidad_registros;
}

// Convierte un registro del archivo a una estructura de películas favoritas.
favorita archivo_estructura_favoritas(std::string linea, int cantidad_campos)
{
    favorita favorita1;
    favorita1.alias = "";

    std::string campos[MAX_CAMPOS];
    int numero_campos = partir(linea, SEPARADOR, campos);

    if ((numero_campos == cantidad_campos) && (campos[0].length() > (unsigned)0))
    {
        favorita1.alias = campos[0];
        favorita1.codigo = atoi(campos[1].c_str());
    }

    return favorita1;
}

// Agrega (guarda) una película favorita al archivo de favoritas.
void agregar_favorita_archivo(favorita nueva_favorita)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_FAVORITAS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out | ios::app);
    if (archivo.is_open())
    {
        std::string linea = estructura_archivo_favoritas(nueva_favorita);
        archivo << linea;
        archivo.close();
    }
}

// Convierte la estructura de una película favorita en una línea de texto para guardarla en el archivo.
std::string estructura_archivo_favoritas(favorita favorita1)
{
    std::string linea = "";

    linea += favorita1.alias;
    linea += SEPARADOR + to_string(favorita1.codigo);
    linea += '\n';

    return linea;
}

// Actualiza el archivo de películas favoritas con un arreglo de favoritas.
void actualizar_archivo_favoritas(favorita favoritas[], int cantidad_favoritas)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_FAVORITAS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
        for (int i = 0; i < cantidad_favoritas; i++)
        {
            std::string linea = estructura_archivo_favoritas(favoritas[i]);
            archivo << linea;
        }
        archivo.close();
    }
}

// Lee desde disco el archivo de estadísticas y lo almacena en el arreglo estadísticas.
int leer_archivo_estadisticas(estadistica estadisticas[])
{
    int cantidad_registros = 0;

    std::string nombre_archivo = NOMBRE_ARCHIVO_JUEGOS;
    if (existe_archivo(nombre_archivo))
    {
        std::ifstream archivo;
        archivo.open(nombre_archivo.c_str());
        while (archivo.good())
        {
            std::string linea;
            getline(archivo, linea, '\n');
            estadistica estadistica1 = archivo_estructura_estadisticas(linea, 3);
            if (estadistica1.alias.length() > (unsigned)0)
            {
                estadisticas[cantidad_registros++] = estadistica1;
            }
        }
        archivo.close();
    }

    return cantidad_registros;
}

// Convierte un registro del archivo a una estructura de estadísticas.
estadistica archivo_estructura_estadisticas(std::string linea, int cantidad_campos)
{
    estadistica estadistica1;
    estadistica1.alias = "";

    std::string campos[MAX_CAMPOS];
    int numero_campos = partir(linea, SEPARADOR, campos);

    if ((numero_campos == cantidad_campos) && (campos[0].length() > (unsigned)0))
    {
        estadistica1.alias = campos[0];
        estadistica1.juego = campos[1];
        estadistica1.resultado = atoi(campos[2].c_str());
    }

    return estadistica1;
}

// Agrega (guarda) una estadística al archivo de estadísticas.
void agregar_estadistica_archivo(estadistica nueva_estadistica)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_JUEGOS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out | ios::app);
    if (archivo.is_open())
    {
        std::string linea = estructura_archivo_estadisticas(nueva_estadistica);
        archivo << linea;
        archivo.close();
    }
}

// Convierte la estructura de una estadística en una línea de texto para guardarla en el archivo.
std::string estructura_archivo_estadisticas(estadistica estadistica1)
{
    std::string linea = "";

    linea += estadistica1.alias;
    linea += SEPARADOR + estadistica1.juego;
    linea += SEPARADOR + to_string(estadistica1.resultado);
    linea += '\n';

    return linea;
}

// Actualiza el archivo de estadísticas con un arreglo de estadísticas.
void actualizar_archivo_estadisticas(estadistica estadisticas[], int cantidad_estadisticas)
{
    std::string nombre_archivo = NOMBRE_ARCHIVO_JUEGOS;
    std::ofstream archivo;
    archivo.open(nombre_archivo, ios::out);

    if (archivo.is_open())
    {
        for (int i = 0; i < cantidad_estadisticas; i++)
        {
            std::string linea = estructura_archivo_estadisticas(estadisticas[i]);
            archivo << linea;
        }
        archivo.close();
    }
}

