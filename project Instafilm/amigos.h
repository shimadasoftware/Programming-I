/**
    GNU GCC 8.1 C++17
    amigos.h
    Purpose: Módulo de usuarios (amigos) de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef AMIGOS_H
#define AMIGOS_H

#include "datos.h"

// Años que determinan la mayoría de edad.
const int MAYORIA_EDAD = 18;

/**
    Determina si una cuenta de correo electrónico tiene al menos los signos '@' y '.'.

    @param email Cuenta de correo electrónico.
    @return Si la cuenta de correo electrónico es válida (true).
*/
bool email_valido(std::string email);

/**
    Determina si la fecha de nacimiento corresponde a un menor de edad.

    @param fecha Fecha de nacimiento.
    @return Si la fecha de edad corresponde a un menor de edad (true).
*/
bool menor_edad(fecha fecha1, int mayoria_edad);

/**
    Determina si un año es bisiesto.

    @param anio Año a verificar.
    @return Si el año es bisiesto (true).
*/
bool es_bisiesto(int anio);

/**
    Lista los usuarios de la aplicación.

    @param administrador Privilegios para mostrar todos los datos aún si están restringidos (true).
    @param tabular Tipo de listado en columnas (true) o en detalle (false).
*/
void listar_usuarios(bool administrador, bool tabular);

/**
    Ordenar el arreglo de usuarios por un determinado campo y un tipo de orden.

    @param usuarios Arreglo de usuarios a ordenar.
    @param cantidad_usuarios Cantidad de usuarios que tiene el arreglo.
    @param campo Nombre del campo por el que se desea ordenar.
    @param ascendente Tipo de orden (true: ascendente, false: descendente).
*/
void ordenar_usuarios(usuario usuarios[], int cantidad_usuarios, std::string campo, bool ascendente);

/**
    Mostrar los datos de un usuario según privilegios y un tipo de listado.

    @param usuario1 Datos del usuario a mostrar.
    @param administrador Tipo de privilegios (true: total, false: restringido).
    @param tabular Tipo de listado (true: tabular en columnas, false: en detalle).
*/
void mostrar_usuario(usuario usuario1, bool administrador, bool tabular);

/**
    Obtiene los datos de un usuario buscándolo por un campo determinado.

    @param campo El campo por el cual se hace la búsqueda.
    @param valor La cadena de búsqueda.
*/
usuario obtener_usuario(std::string campo, std::string valor);

/**
    Pide una cuenta de correo electrónico y la busca en los usuarios del sistema.

    @param usuario_actual Usuario actual.
*/
void buscar_usuario_correo(usuario usuario_actual);

/**
    Pide una cuenta de correo electrónico para configurar a ese usuario como administrador.

    @param usuario_actual Usuario actual.
*/
void asignar_administrador(usuario usuario_actual);

/**
    Pide una cuenta de correo electrónico para quitarle provilegios de administrador.

    @param usuario_actual Usuario actual.
*/
void desasignar_administrador(usuario usuario_actual);

/**
    Actualiza los datos de un usuario en archivo.

    @param usuario1 Usuario a actualizar.
*/
void actualizar_usuario(usuario usuario1);

/**
    Encripta una cadena de texto.

    @param texto Cadena de texto a encriptar.
    @return Cadena de texto encriptada.
*/
std::string encriptar(std::string texto);

/**
    Lee desde teclado una cuenta de correo electrónico.

    @param registro True si se le la cuenta de correo con propósitos de registro de usuarios.
    @return Cuenta de correo electrónica leída.
*/
std::string leer_email(bool registro);

/**
    Lee los nombres de una persona.

    @return Nombres de la persona leídos.
*/
std::string leer_nombres();

/**
    Lee los apellidos de una persona.

    @return Apellidos de la persona leídos.
*/
std::string leer_apellidos();

/**
    Lee el nombre de usuario (alias).

    @return El alias leído.
*/
std::string leer_alias();

/**
    Lee la contraseña y la encripta.

    @return Contraseña encriptada.
*/
std::string leer_contrasenia();

/**
    Lee el género de una persona (f: femenino, m: masculino).

    @return Género de la persona leído.
*/
char leer_genero();

/**
    Lee una fecha.

    @return La fecha leída.
*/
fecha leer_fecha();

/**
    Menú para modificar los privilegios de publicación de cada dato del usuario.

    @param publicar Arreglo de privilegios de publicación de los datos del usuario.
*/
void menu_publicar(bool publicar[]);

/**
    Contabiliza los usuarios que son admistradores.

    @return Cantidad de usuarios que son administradores.
*/
int cantidad_administradores();

/**
    Modifica el perfil del usuario actual.

    @param usuario_actual Usuario Actual.
*/
void modificar_perfil(usuario usuario_actual);

/**
    Actualiza la contraseña.

    @param anterior_contrasenia Contraseña anterior.
    @return Nueva contraseña.
*/
std::string actualizar_contrasenia(std::string anterior_contrasenia);

/**
    Inactivar el perfil del usuario.

    @param usuario_actual Usuario actual.
*/
void inactivar_perfil(usuario usuario_actual);

/**
    Activar el perfil del usuario.

    @param usuario_actual Usuario actual.
*/
void activar_perfil(usuario usuario_actual);

/**
    Eliminar el perfil del usuario.

    @param usuario_actual Usuario actual.
*/
void eliminar_perfil(usuario usuario_actual);

/**
    Eliminar datos del usuario,

    @param usuario_actual Usuario actual.
*/
void eliminar_usuario(usuario usuario_actual);

/**
    Buscar amigos,

    @param usuario_actual Usuario actual.
*/
void buscar_amigos(usuario usuario_actual);

/**
    Buscar amigos por sus nombres.

    @param usuario_actual Usuario actual.
*/
void buscar_amigos_nombres(usuario usuario_actual);

/**
    Buscar amigos por sus apellidos.

    @param usuario_actual Usuario actual.
*/
void buscar_amigos_apellidos(usuario usuario_actual);

/**
    Verifica si dos usuarios son dos amigos.

    @param alias_anfitrion Amigo anfitrion.
    @param alias_invitado Amigo invitado.
    @return 0: No son amigos, 1: Son amigos, 2: solicitud pendiente.
*/
int es_amigo(std::string alias_anfitrion, std::string alias_invitado);

/**
    Hacer solicitudes de amistad.

    @param usuario_actual Usuario actual.
*/
void solicitud_amistad(usuario usuario_actual);

/**
    Nueva solicitud de amistad.

    @param anfitrion Alias de quien solicita la amistad.
    @param invitado Alias de a quien se le envía la solicitud de amistad.
*/
void nueva_solicitud_amistad(std::string anfitrion, std::string invitado);

/**
    Listar solicitudes pendientes de amistad.

    @param usuario_actual Usuario actual.
    @param aceptar true: Acepta solicitudes pendientes.
*/
void listar_solicitudes_pendientes(usuario usuario_actual, bool aceptar);

/**
    Listar los amigos del usuario actual.

    @param usuario_actual Usuario actual.
*/
void listar_amigos(usuario usuario_actual);

/**
    Lista los datos de un amigo y sus películas favoritas.

    @param usuario_actual Usuario actual.
*/
void listar_amigo_pelicula(usuario usuario_actual);

/**
    Detecta las películas favoritas en común con un amigo.

    @param usuario_actual Usuario actual.
*/
void peliculas_comun(usuario usuario_actual);

/**
    Deshace una amistad.

    @param usuario_actual Usuario actual.
*/
void deshacer_amistad(usuario usuario_actual);

/**
    Elimina la amistad entre dos usuarios.

    @param alias1 Amigo 1
    @param alias2 Amigo 2
*/
void elimina_amistad(std::string alias1, std::string alias2);

/**
    Eliminar un usuario de todas sus amistades.

    @param alias El usuario a eliminar.
*/
void eliminar_todos_amigos(std::string alias);

#endif // AMIGOS_H
