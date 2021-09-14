/**
    GNU GCC 8.1 C++17
    peliculas.h
    Purpose: Módulo de películas de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef PELICULAS_H
#define PELICULAS_H

#include "datos.h"

// Principales generos de películas según Wikipedia.
const std::string generos_peliculas[] =
{
    "Accion", "Ciencia ficcion", "Comedia", "Drama", "Fantasia", "Melodrama", "Musical", "Romance", "Suspenso", "Documental",
    "Terror", "Belico", "Animacion", "Infantil", "Epico", "Thriller", "Western", "Pornografico", "Erotico", "Otro"
};

/**
    Lee los datos de una película y los almacena en el archivo de películas.

    @param usuario_actual Usuario actual.
*/
void crear_pelicula(usuario usuario_actual);

/**
    Lee el nombre de la pelicula.

    @return Nombre de la película.
*/
std::string lee_nombre_pelicula();

/**
    Lee el genero de la película.

    @param titulo Título de la película
    @return Género de la película
*/
std::string lee_genero_pelicula(std::string titulo);

/**
    Lee la descripción de la película.

    @return Descripción de la película.
*/
std::string lee_descripcion_pelicula();

/**
    Lista las películas.

    @param tabular Tipo de listado (true: Por columnas, false: en detalle).
*/
void listar_peliculas(bool tabular);

/**
    Muestra los datos de una película en formato de columnas o en detalle.

    @param pelicula1 Datos de la película.
    @param tabular Tipo de listado (true: tabular, false: en detalle).
*/
void mostrar_pelicula(pelicula pelicula1, bool tabular);

/**
    Modifica los datos de una película.

    @param usuario_actual Usuario actual.
*/
void modificar_pelicula(usuario usuario_actual);

/**
    Obtiene los datos de una película buscándola por un campo determinado.

    @param campo Campo de búsqueda (código, título, genero, descripción).
    @param valor Valor de la búsqueda.
    @return Película buscada.
*/
pelicula obtener_pelicula(std::string campo, std::string valor);

/**
    Actualiza los datos de una película.

    @param pelicula1 Los datos originales de la película.
    @return Los datos modificados de la película.
*/
pelicula actualizar_pelicula(pelicula pelicula1);

/**
    Elimina una película.

    @param usuario_actual Usuario actual.
*/
void eliminar_pelicula(usuario usuario_actual);

/**
    Elimina una película según su código.

    @param codigo_pelicula Código de la película a eliminar.
    @return True, si la película fue eliminada.
*/
bool borra_pelicula(int codigo_pelicula);

/**
    Elimina una película de la lista de favoritas.

    @param codigo_pelicula Código de la película a eliminar.
*/
void eliminar_pelicula_favoritas(int codigo_pelicula);

/**
    Elimina un usuario de la lista de favoritas.

    @param alias Alias del usuario a eliminar de la lista de favoritas.
*/
void eliminar_usuario_favoritas(std::string alias);

/**
    Elimina un usuario de la lista de favoritas.

    @param campo El campo por el cual se va a buscar.
    @param value EL valor del campo de búsqueda.
*/
void eliminar_conjunto_favoritas(std::string campo, std::string valor);

/**
    Marcar una película como favorita.

    @param usuario_actual Usuario actual.
*/
void me_gusta(usuario usuario_actual);

/**
    Quitar una película de su listado de favoritas.

    @param usuario_actual Usuario actual.
*/
void no_me_gusta(usuario usuario_actual);

/**
    Verifica si la película es favorita de una persona (true: si, false: no).

    @param alias Alias de la persona.
    @param codigo Codigo de la película.
    @return Si la película es la favorita de esa persona.
*/
bool es_favorita(std::string alias, int codigo);

/**
    Elimina una película de la lista de favoritos.

    @param alias Alias de la persona.
    @param codigo Codigo de la película.
*/
void elimina_favorita(std::string alias, int codigo);

/**
    Muestra las películas favoritas de un usuario.

    @param alias La persona de las películas favoritas.
*/
void mostrar_peliculas_favoritas(std::string alias);

#endif // PELICULAS_H
