/**
    GNU GCC 8.1 C++17
    ingreso.h
    Purpose: Módulo de ingreso a la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef INGRESO_H
#define INGRESO_H

#include "datos.h"

/**
    Valida el tipo de usuario a ingresar y determina sus privilegios.
*/
void ingreso();

/**
    Muestra el menú del administrador del sistema.

    @param usuario_actual.
*/
void menu_administrador(usuario usuario_actual);

/**
    Muestra el menú del usuario del sistema.

    @param usuario_actual.
*/
void menu_usuario(usuario usuario_actual);

/**
    Menú administración del sistema.

    @param usuario_actual.
*/
void menu_administracion(usuario usuario_actual);

/**
    Menú gestión de administradores.

    @param usuario_actual.
*/
void menu_administradores(usuario usuario_actual);

/**
    Menú de Gestión de películas.

    @param usuario_actual.
*/
void menu_gestion_peliculas(usuario usuario_actual);

/**
    Menú del perfil del usuario.

    @param usuario_actual.
*/
void menu_perfil(usuario usuario_actual);

/**
    Menú de amigos.

    @param usuario_actual.
*/
void menu_amigos(usuario usuario_actual);

/**
    Menú para escoger las películas de su gusto.

    @param usuario_actual.
*/
void menu_peliculas(usuario usuario_actual);

/**
    Menú de juegos.

    @param usuario_actual.
*/
void menu_juegos(usuario usuario_actual);

/**
    Menú Juego triqui.
*/
void menu_triqui(usuario usuario_actual);

#endif // INGRESO_H

