/**
    GNU GCC 8.1 C++17
    ingreso.cpp
    Purpose: Módulo de ingreso a la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include "ingreso.h"
#include "consola.h"
#include "amigos.h"
#include "peliculas.h"
#include "triqui.h"

using namespace std;

// Valida el tipo de usuario a ingresar y determina sus privilegios.
void ingreso()
{
    mensaje("Bienvenid@s", "Por favor, ingresa tu correo electronico.", false);
    std::string email = leer_email(false);

    mensaje("Bienvenid@s", "Por favor, ingresa tu contrasena.", false);
    std::string contrasenia = leer_contrasenia();

    usuario usuario_actual = obtener_usuario("email", email);

    if (usuario_actual.genero == '#')
    {
        mensaje("Ingreso no autorizado!", "La combinacion de correo y contrasena no es correcta.", true);
    }
    else if (usuario_actual.contrasenia.compare(contrasenia) != 0)
    {
        mensaje("Ingreso no autorizado!", "La combinacion de correo y contrasena no es correcta.", true);
    }
    else if (usuario_actual.administrador)
    {
        menu_administrador(usuario_actual);
    }
    else
    {
        menu_usuario(usuario_actual);
    }
}

// Muestra el menú del administrador del sistema.
void menu_administrador(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Administracion",
            "2. Perfil",
            "3. Amigos",
            "4. Peliculas",
            "5. Juegos",
            "0. Cerrar sesion"
        };
        mostrar_menu("Administrador (" + usuario_actual.alias + ")", opciones, 6);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : menu_administracion(usuario_actual); break;
            case 2 : menu_perfil(usuario_actual); break;
            case 3 : menu_amigos(usuario_actual); break;
            case 4 : menu_peliculas(usuario_actual); break;
            case 5 : menu_juegos(usuario_actual); break;
        }

        usuario temporal = obtener_usuario("alias", usuario_actual.alias);
        usuario_actual.administrador = temporal.administrador;
    }
    while (opcion != 0);
}

// Muestra el menú del usuario del sistema.
void menu_usuario(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Perfil",
            "2. Amigos",
            "3. Peliculas",
            "4. Juegos",
            "0. Cerrar sesion"
        };
        mostrar_menu("Usuario (" + usuario_actual.alias + ")", opciones, 5);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : menu_perfil(usuario_actual); break;
            case 2 : menu_amigos(usuario_actual); break;
            case 3 : menu_peliculas(usuario_actual); break;
            case 4 : menu_juegos(usuario_actual); break;
        }

        usuario temporal = obtener_usuario("alias", usuario_actual.alias);
        usuario_actual.administrador = temporal.administrador;
    }
    while (opcion != 0);
}

// Menú administración del sistema.
void menu_administracion(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Asignar administradores",
            "2. Ver usuarios",
            "3. Ver usuarios en detalle",
            "4. Administrar peliculas",
            "0. Regresar menu Administrador"
        };
        mostrar_menu("Administracion", opciones, 5);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : menu_administradores(usuario_actual); break;
            case 2 : listar_usuarios(usuario_actual.administrador, true); break;
            case 3 : listar_usuarios(usuario_actual.administrador, false); break;
            case 4 : menu_gestion_peliculas(usuario_actual); break;
        }
        usuario temporal = obtener_usuario("alias", usuario_actual.alias);
        usuario_actual.administrador = temporal.administrador;
    }
    while (opcion != 0);
}

// Menú gestión de administradores.
void menu_administradores(usuario usuario_actual)
{
    std::string opciones[] =
    {
        "1. Buscar usuario por correo",
        "2. Asignar administrador",
        "3. Quitar asignacion como administrador",
        "0. Regresar menu Administracion"
    };
    int opcion;

    do
    {
        mostrar_menu("Gestionar Administradores", opciones, 4);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : buscar_usuario_correo(usuario_actual);    break;
            case 2 : asignar_administrador(usuario_actual);    break;
            case 3 : desasignar_administrador(usuario_actual); break;
        }

        usuario temporal = obtener_usuario("alias", usuario_actual.alias);
        usuario_actual.administrador = temporal.administrador;
    }
    while (opcion != 0);
}

// Menú de Gestión de películas.
void menu_gestion_peliculas(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Crear pelicula",
            "2. Modificar pelicula",
            "3. Eliminar pelicula",
            "4. Listar peliculas",
            "5. Listar peliculas en detalle",
            "0. Regresar menu Administracion"
        };
        mostrar_menu("Gestionar Peliculas", opciones, 6);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : crear_pelicula(usuario_actual); break;
            case 2 : modificar_pelicula(usuario_actual); break;
            case 3 : eliminar_pelicula(usuario_actual); break;
            case 4 : { listar_peliculas(true); pausar(); } break;
            case 5 : { listar_peliculas(false); pausar(); } break;
        }
    }
    while (opcion != 0);
}

// Menú del perfil del usuario.
void menu_perfil(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Modificar perfil",
            "2. Inactivar perfil",
            "3. Activar perfil",
            "4. Eliminar perfil",
            "0. Regresar"
        };
        mostrar_menu("Perfil", opciones, 5);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : modificar_perfil(usuario_actual); break;
            case 2 : inactivar_perfil(usuario_actual); break;
            case 3 : activar_perfil(usuario_actual); break;
            case 4 : eliminar_perfil(usuario_actual); break;
        }
        usuario temporal = obtener_usuario("alias", usuario_actual.alias);
        usuario_actual = temporal;
    }
    while (opcion != 0);
}

// Menú de amigos.
void menu_amigos(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Buscar amigos",
            "2. Hacer solicitudes de amistad",
            "3. Ver solicitudes pendientes",
            "4. Aceptar solicitudes de amistad",
            "5. Ver amigos",
            "6. Ver informacion de un amigo",
            "7. Ver peliculas en comun",
            "8. Deshacer amistad",
            "0. Regresar"
        };
        mostrar_menu("Amigos", opciones, 9);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : buscar_amigos(usuario_actual); break;
            case 2 : solicitud_amistad(usuario_actual); break;
            case 3 : listar_solicitudes_pendientes(usuario_actual, false); break;
            case 4 : listar_solicitudes_pendientes(usuario_actual, true); break;
            case 5 : listar_amigos(usuario_actual); break;
            case 6 : listar_amigo_pelicula(usuario_actual); break;
            case 7 : peliculas_comun(usuario_actual); break;
            case 8 : deshacer_amistad(usuario_actual); break;
        }
    }
    while (opcion != 0);
}

// Menú para escoger las películas de su gusto.
void menu_peliculas(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Peliculas que me gustan",
            "2. Peliculas que ya NO me gustan",
            "0. Regresar"
        };
        mostrar_menu("Amigos", opciones, 3);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : me_gusta(usuario_actual); break;
            case 2 : no_me_gusta(usuario_actual); break;
        }
    }
    while (opcion != 0);
}

// Menú de juegos.
void menu_juegos(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Triqui",
            "0. Volver"
        };
        mostrar_menu("Juegos", opciones, 2);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : menu_triqui(usuario_actual); break;
        }
    }
    while (opcion != 0);
}

// Menú Juego triqui.
void menu_triqui(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Jugar Triqui",
            "2. Estadisticas de Triqui",
            "0. Volver"
        };
        mostrar_menu("Triqui", opciones, 3);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : jugar_triqui(usuario_actual); break;
            case 2 : estadistica_triqui(usuario_actual); break;
        }
    }
    while (opcion != 0);
}

