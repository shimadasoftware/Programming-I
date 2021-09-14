/**
    GNU GCC 8.1 C++17
    registro.cpp
    Purpose: Registro de un nuevo usuario de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include "registro.h"
#include "consola.h"
#include "amigos.h"
#include "datos.h"

using namespace std;

// Registrar un nuevo usuario en la aplicación.
void registro()
{
    mensaje("Primer paso:", "Digita tu cuenta de correo electronico: ", false);
    string email = leer_email(true);

    mensaje("Segundo paso:", "Digita tus nombres y apellidos", false);
    string nombres = leer_nombres();
    string apellidos = leer_apellidos();

    mensaje("Tercer paso:", "Digita tu alias (asi te identificaran dentro de la red)", false);
    string alias = leer_alias();
    string contrasenia = leer_contrasenia();

    mensaje("Cuarto paso:", "Escoge tu genero", false);
    char genero = leer_genero();

    mensaje("Quinto paso:", "Digita tu fecha de nacimiento", false);
    fecha fecha_nacimiento = leer_fecha();

    bool publicar[] = {true, true, true, true, true};
    menu_publicar(publicar);

    usuario nuevo_usuario;
    nuevo_usuario.alias = alias;
    nuevo_usuario.contrasenia = contrasenia;
    nuevo_usuario.nombres = nombres;
    nuevo_usuario.nombres_publico = publicar[0];
    nuevo_usuario.apellidos = apellidos;
    nuevo_usuario.apellidos_publico = publicar[1];
    nuevo_usuario.genero = genero;
    nuevo_usuario.genero_publico = publicar[2];
    nuevo_usuario.email = email;
    nuevo_usuario.email_publico = publicar[3];
    nuevo_usuario.fecha_nacimiento = fecha_nacimiento;
    nuevo_usuario.fecha_nacimiento_publico = publicar[4];
    nuevo_usuario.administrador = false;
    nuevo_usuario.activo = true;

    agregar_usuario_archivo(nuevo_usuario);
}

