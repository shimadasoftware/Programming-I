/**
    GNU GCC 8.1 C++17
    amigos.cpp
    Purpose: Módulo de usuarios (amigos) de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include <string>
#include <ctime>
#include "amigos.h"
#include "consola.h"
#include "peliculas.h"

using namespace std;

// Determina si una cuenta de correo electrónico tiene al menos los signos '@' y '.'.
bool email_valido(std::string email)
{
    bool arroba = false;
    bool punto = false;

    for (unsigned i = 0; i < email.length(); i++)
    {
        if (email.at(i) == '@')
        {
            arroba = true;
        }
        if (email.at(i) == '.')
        {
            punto = true;
        }
    }
    return arroba && punto;
}

// Determina si la fecha de nacimiento corresponde a un menor de edad.
bool menor_edad(fecha fecha1, int mayoria_edad)
{
    std::time_t t = std::time(0);
    std::tm* ahora = std::localtime(&t);

    int anio = ahora->tm_year + 1900;
    int mes = ahora->tm_mon + 1;
    int dia = ahora->tm_mday;

    if (fecha1.anio < anio - mayoria_edad)
    {
        return false;
    }
    if (fecha1.anio > anio - mayoria_edad)
    {
        return true;
    }
    if (fecha1.mes < mes)
    {
        return false;
    }
    if (fecha1.mes > mes)
    {
        return true;
    }
    if (fecha1.dia <= dia)
    {
        return false;
    }
    return true;
}

// Determina si un año es bisiesto.
bool es_bisiesto(int anio)
{
    if (anio % 400 == 0)
    {
        return true;
    }
    if (anio % 100 == 0)
    {
        return false;
    }
    if (anio % 4 == 0)
    {
        return true;
    }
    return false;
}

// Lista los usuarios de la aplicación.
void listar_usuarios(bool administrador, bool tabular)
{
    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);
    ordenar_usuarios(usuarios, cantidad_usuarios, "apellidos", true);

    limpiar_pantalla();
    std::cout << centrar_mensaje("Listado de usuarios", ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    if (tabular)
    {
        std::cout << "Alias      |Nombres       |Apellidos     |G|email                |nacimiento|A|a" << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;
    }

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        mostrar_usuario(usuarios[i], administrador, tabular);
    }

    pausar();
}

// Ordenar el arreglo de usuarios por un determinado campo y un tipo de orden.
void ordenar_usuarios(usuario usuarios[], int cantidad_usuarios, std::string campo, bool ascendente)
{
    bool intercambio;

    for (int i = 0; i < cantidad_usuarios - 1; i++)
    {
        for (int j = i + 1; j < cantidad_usuarios; j++)
        {
            intercambio = false;

            if (ascendente)
            {
                if ((campo.compare("alias") == 0) && (usuarios[i].alias.compare(usuarios[j].alias) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("contrasenia") == 0) && (usuarios[i].contrasenia.compare(usuarios[j].contrasenia) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("nombres") == 0) && (usuarios[i].nombres.compare(usuarios[j].nombres) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("apellidos") == 0) && (usuarios[i].apellidos.compare(usuarios[j].apellidos) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("genero") == 0) && (usuarios[i].genero > usuarios[j].genero))
                {
                    intercambio = true;
                }
                else if ((campo.compare("email") == 0) && (usuarios[i].email.compare(usuarios[j].email) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("fecha_nacimiento") == 0) && (compare_fechas(usuarios[i].fecha_nacimiento, usuarios[j].fecha_nacimiento) > 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("administrador") == 0) && (usuarios[i].administrador && !(usuarios[i].administrador)))
                {
                    intercambio = true;
                }
                else if ((campo.compare("activo") == 0) && (usuarios[i].activo && !(usuarios[i].activo)))
                {
                    intercambio = true;
                }
            }
            else
            {
                if ((campo.compare("alias") == 0) && (usuarios[i].alias.compare(usuarios[j].alias) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("contrasenia") == 0) && (usuarios[i].contrasenia.compare(usuarios[j].contrasenia) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("nombres") == 0) && (usuarios[i].nombres.compare(usuarios[j].nombres) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("apellidos") == 0) && (usuarios[i].apellidos.compare(usuarios[j].apellidos) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("genero") == 0) && (usuarios[i].genero < usuarios[j].genero))
                {
                    intercambio = true;
                }
                else if ((campo.compare("email") == 0) && (usuarios[i].email.compare(usuarios[j].email) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("fecha_nacimiento") == 0) && (compare_fechas(usuarios[i].fecha_nacimiento, usuarios[j].fecha_nacimiento) < 0))
                {
                    intercambio = true;
                }
                else if ((campo.compare("administrador") == 0) && (!(usuarios[i].administrador) && usuarios[i].administrador))
                {
                    intercambio = true;
                }
                else if ((campo.compare("activo") == 0) && (!(usuarios[i].activo) && usuarios[i].activo))
                {
                    intercambio = true;
                }
            }

            if (intercambio)
            {
                usuario temporal = usuarios[i];
                usuarios[i] = usuarios[j];
                usuarios[j] = temporal;
            }
        }
    }
}

// Mostrar los datos de un usuario según privilegios y un tipo de listado.
void mostrar_usuario(usuario usuario1, bool administrador, bool tabular)
{
    if (usuario1.alias.length() <= (unsigned)0)
    {
        return;
    }
    if (tabular)
    {
        std::cout << centrar_mensaje(usuario1.alias, 11, ' ') << "|";
        if (administrador || (!administrador && usuario1.nombres_publico))
        {
            std::cout << centrar_mensaje(usuario1.nombres, 14, ' ') << "|";
        }
        else
        {
            std::cout << centrar_mensaje("-", 14, '-') << "|";
        }
        if (administrador || (!administrador && usuario1.apellidos_publico))
        {
            std::cout << centrar_mensaje(usuario1.apellidos, 14, ' ') << "|";
        }
        else
        {
            std::cout << centrar_mensaje("-", 14, '-') << "|";
        }
        if (administrador || (!administrador && usuario1.genero_publico))
        {
            std::cout << usuario1.genero << "|";
        }
        else
        {
            std::cout <<  "-|";
        }
        if (administrador || (!administrador && usuario1.email_publico))
        {
            std::cout << centrar_mensaje(usuario1.email, 21, ' ') << "|";
        }
        else
        {
            std::cout << centrar_mensaje("-", 21, '-') << "|";
        }
        if (administrador || (!administrador && usuario1.fecha_nacimiento_publico))
        {
            if (usuario1.fecha_nacimiento.dia > 9)
            {
                std::cout << std::to_string(usuario1.fecha_nacimiento.dia) << "/";
            }
            else
            {
                std::cout << "0" << std::to_string(usuario1.fecha_nacimiento.dia) << "/";
            }
            if (usuario1.fecha_nacimiento.mes > 9)
            {
                std::cout << std::to_string(usuario1.fecha_nacimiento.mes) << "/";
            }
            else
            {
                std::cout << "0" << std::to_string(usuario1.fecha_nacimiento.mes) << "/";
            }
            std::cout << std::to_string(usuario1.fecha_nacimiento.anio) << "|";
        }
        else
        {
            std::cout << centrar_mensaje("--/--/----", 10, '-') << "|";
        }
        if (administrador)
        {
            std::cout << (usuario1.administrador ? "x" : " ") << "|";
        }
        else
        {
            std::cout <<  "-|";
        }
        if (administrador)
        {
            std::cout << (usuario1.activo ? "x" : " ") << "|" << std::endl;
        }
        else
        {
            std::cout <<  "-|" << std::endl;
        }
    }
    else
    {
        std::cout << "Alias:               " << usuario1.alias << std::endl;
        if (administrador || (!administrador && usuario1.nombres_publico))
        {
            std::cout << "Nombres:             " << usuario1.nombres << std::endl;
        }
        if (administrador || (!administrador && usuario1.apellidos_publico))
        {
            std::cout << "Apellidos:           " << usuario1.apellidos << std::endl;
        }
        if (administrador || (!administrador && usuario1.genero_publico))
        {
            std::cout << "Genero:              " << ((usuario1.genero == 'f') ? "Femenino" : "Masculino") << std::endl;
        }
        if (administrador || (!administrador && usuario1.email_publico))
        {
            std::cout << "Correo electronico:  " << usuario1.email << std::endl;
        }
        if (administrador || (!administrador && usuario1.fecha_nacimiento_publico))
        {
            std::cout << "Fecha de nacimiento: " << std::to_string(usuario1.fecha_nacimiento.dia) << "/";
            std::cout << std::to_string(usuario1.fecha_nacimiento.mes) << "/";
            std::cout << std::to_string(usuario1.fecha_nacimiento.anio) << std::endl;
        }
        if (administrador)
        {
            std::cout << (usuario1.administrador ? "Tiene privilegios de administrador" : "NO tiene privilegios de administrador") << std::endl;
        }
        if (administrador)
        {
            std::cout << (usuario1.activo ? "Usuario activo" : "Usuario inactivo") << std::endl;
        }
        std::cout << std::endl;
    }
}

// Obtiene los datos de un usuario buscándolo por un campo determinado.
usuario obtener_usuario(std::string campo, std::string valor)
{
    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if ((campo.compare("alias") == 0) && (usuarios[i].alias.compare(valor) == 0))
        {
            return usuarios[i];
        }
        else if ((campo.compare("contrasenia") == 0) && (usuarios[i].contrasenia.compare(valor) == 0))
        {
            return usuarios[i];
        }
        else if ((campo.compare("nombres") == 0) && (usuarios[i].nombres.compare(valor) == 0))
        {
            return usuarios[i];
        }
        else if ((campo.compare("apellidos") == 0) && (usuarios[i].apellidos.compare(valor) == 0))
        {
            return usuarios[i];
        }
        else if ((campo.compare("genero") == 0) && (usuarios[i].genero == valor.at(0)))
        {
            return usuarios[i];
        }
        else if ((campo.compare("email") == 0) && (usuarios[i].email.compare(valor) == 0))
        {
            return usuarios[i];
        }
        else if (campo.compare("fecha_nacimiento") == 0)
        {
            int dia  = atoi(valor.substr(0, 2).c_str());
            int mes  = atoi(valor.substr(3, 2).c_str());
            int anio = atoi(valor.substr(6, 4).c_str());

            fecha fecha2;
            fecha2.dia = dia;
            fecha2.mes = mes;
            fecha2.anio = anio;

            if (compare_fechas(usuarios[i].fecha_nacimiento, fecha2) == 0)
            {
                return usuarios[i];
            }
        }
        else if (campo.compare("administrador") == 0)
        {
            bool administrador = (valor.compare("true") == 0);

            if (usuarios[i].administrador == administrador)
            {
                return usuarios[i];
            }
        }
        else if (campo.compare("activo") == 0)
        {
            bool activo = (valor.compare("true") == 0);

            if (usuarios[i].activo == activo)
            {
                return usuarios[i];
            }
        }
    }

    usuario usuario1;
    usuario1.genero = '#';
    return usuario1;
}

// Pide una cuenta de correo electrónico y la busca en los usuarios del sistema.
void buscar_usuario_correo(usuario usuario_actual)
{
    limpiar_pantalla();

    std::string email = leer_email(false);
    usuario usuario_buscar = obtener_usuario("email", email);

    if (usuario_buscar.genero == '#')
    {
        mensaje("Lo siento! No fue encontrado ningun usuario", ("con correo " + email + "."), ANCHO_VENTANA);
    }
    else
    {
        mostrar_usuario(usuario_buscar, usuario_actual.administrador, false);
        pausar();
    }
}

// Pide una cuenta de correo electrónico para configurar a ese usuario como administrador.
void asignar_administrador(usuario usuario_actual)
{
    limpiar_pantalla();

    if (usuario_actual.administrador)
    {
        std::string email = leer_email(false);
        usuario administrador = obtener_usuario("email", email);

        if (administrador.genero != '#')
        {
            if (administrador.administrador)
            {
                mensaje("No se aplicaron cambios!", "El usuario ya tenia privilegios de administrador", ANCHO_VENTANA);
            }
            else
            {
                administrador.administrador = true;
                actualizar_usuario(administrador);
                mensaje("El usuario con email (" + email + ")", "ahora tiene privilegios de administrador.", ANCHO_VENTANA);
            }
        }
        else
        {
            mensaje("Lo siento! El usuario con email (" + email + ")", "no fue encontrado.", ANCHO_VENTANA);
        }
    }
    else
    {
        mensaje("Lo siento! Usted no tiene los suficientes privilegios", "para ejecutar operacion.", ANCHO_VENTANA);
    }
}

// Pide una cuenta de correo electrónico para quitarle provilegios de administrador.
void desasignar_administrador(usuario usuario_actual)
{
    limpiar_pantalla();

    if (usuario_actual.administrador)
    {
        if (cantidad_administradores() > 1)
        {
            std::string email = leer_email(false);
            usuario administrador = obtener_usuario("email", email);

            if (administrador.genero != '#')
            {
                if (!administrador.administrador)
                {
                    mensaje("No se aplicaron cambios!", "Este usuario NO tenia privilegios de administrador", ANCHO_VENTANA);
                }
                else
                {
                    administrador.administrador = false;
                    actualizar_usuario(administrador);
                    mensaje("Al usuario con email (" + email + ")", "le fueron eliminados los privilegios de administrador.", ANCHO_VENTANA);
                }
            }
            else
            {
                mensaje("Lo siento! El usuario con email (" + email + ")", "no fue encontrado.", ANCHO_VENTANA);
            }
        }
        else
        {
            mensaje("Lo siento! Operacion cancelada.", "No existen suficientes administradores en el sistema.", ANCHO_VENTANA);
        }
    }
    else
    {
        mensaje("Lo siento! Usted no tiene los suficientes privilegios", "para ejecutar operacion.", ANCHO_VENTANA);
    }
}

// Actualiza los datos de un usuario en archivo.
void actualizar_usuario(usuario usuario1)
{
    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if (usuarios[i].email.compare(usuario1.email) == 0)
        {
            usuarios[i] = usuario1;
        }
    }

    actualizar_archivo_usuarios(usuarios, cantidad_usuarios);
}

// Encripta una cadena de texto.
std::string encriptar(std::string texto)
{
    std::string cadena = "";
    char clave = '4';

    for (unsigned i = 0; i < texto.length(); i++)
    {
        char caracter = texto.at(i) ^ clave;
        caracter = ((caracter == SEPARADOR) ? '#' : caracter);
        cadena += caracter;
    }

    return cadena;
}

// Lee desde teclado una cuenta de correo electrónico.
std::string leer_email(bool registro)
{
    bool valido = true;
    bool existe = false;
    std::string email;

    do
    {
        do
        {
            std::cout << "\t Correo electronico -> ";
            std::cin >> email;

            valido = email_valido(email);
            if (!valido)
            {
                mensaje("Lo siento! esta cuenta de correo electronico es invalida.", "Por favor, vuelve a digitarla.", false);
            }
        }
        while (!valido);

        if (registro)
        {
            usuario usuario1 = obtener_usuario("email", email);
            existe = (usuario1.genero != '#');
            if (existe)
            {
                mensaje("Lo siento! ya existe un registro con esta cuenta de correo.", "Por favor, digita otra.", false);
            }
        }
    }
    while (existe);

    return email;
}

// Lee los nombres de una persona.
std::string leer_nombres()
{
    std::string nombres = "";

    do
    {
        std::cout << "\t Nombres -> ";
        getline(std::cin, nombres);
    }
    while (nombres.length() <= 0);

    return nombres;
}

// Lee los apellidos de una persona.
std::string leer_apellidos()
{
    std::string apellidos = "";
    do
    {
        std::cout << "\t Apellidos -> ";
        getline(std::cin, apellidos);
    }
    while (apellidos.length() <= 0);

    return apellidos;
}

// Lee el nombre de usuario (alias).
std::string leer_alias()
{
    std::string alias = "";
    bool existe = false;

    do
    {
        do
        {
            std::cout << "\t Alias -> ";
            getline(std::cin, alias);
        }
        while (alias.length() <= 0);

        usuario usuario1 = obtener_usuario("alias", alias);
        if (usuario1.genero != '#')
        {
            mensaje("Lo siento! ya existe un registro con este alias.", "Por favor, digita otro.", false);
        }
    }
    while (existe);

    return alias;
}

// Lee la contraseña y la encripta.
std::string leer_contrasenia()
{
    std::string contrasenia;

    do
    {
        std::cout << "\t Contrasena -> ";
        getline(std::cin, contrasenia);
    }
    while (contrasenia.length() <= 0);

    contrasenia = encriptar(contrasenia);
    return contrasenia;
}

// Lee el género de una persona (f: femenino, m: masculino).
char leer_genero()
{
    char genero;

    do
    {
        std::cout << "\t Genero (f - femenino, m - masculino) -> ";
        std::cin >> genero;
        genero = tolower(genero);

        if (genero != 'f' && genero != 'm')
        {
            mensaje("Lo siento! debes digitar 'f' o 'm'.", "Por favor, vuelve a intentarlo.", false);
        }
    }
    while (genero != 'f' && genero != 'm');

    return genero;
}

// Lee una fecha.
fecha leer_fecha()
{
    fecha fecha1;
    int anio;
    int mes;
    int dia;
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool menor;

    do
    {
        std::cout << "\t Año -> ";
        std::cin >> anio;

        do
        {
            std::cout << "\t Mes (1-enero, 2-febrero, ... 12-diciembre) -> ";
            std::cin >> mes;
        }
        while (mes < 1 || mes > 12);

        if (es_bisiesto(anio))
        {
            dias_mes[1] = 29;
        }

        do
        {
            std::cout << "\t Dia (1 .. " << dias_mes[mes - 1] << ") -> ";
            std::cin >> dia;
        }
        while (dia < 1 || dia > dias_mes[mes - 1]);

        fecha1.anio = anio;
        fecha1.mes = mes;
        fecha1.dia = dia;

        menor = menor_edad(fecha1, MAYORIA_EDAD);
        if (menor)
        {
            mensaje("Lo siento! No se aceptan menores de edad.", "Por favor, vuelve a intentarlo.", false);
        }
    }
    while (menor);

    return fecha1;
}

// Menú para modificar los privilegios de publicación de cada dato del usuario.
void menu_publicar(bool publicar[])
{
    int opcion;

    do
    {
        std::string opciones[] =
        {
            "1. Nombres: " + (publicar[0] ? (std::string)"Publico" : (std::string)"Privado"),
            "2. Apellidos: " + (publicar[1] ? (std::string)"Publico" : (std::string)"Privado"),
            "3. Genero: " + (publicar[2] ? (std::string)"Publico" : (std::string)"Privado"),
            "4. Correo electronico: " + (publicar[3] ? (std::string)"Publico" : (std::string)"Privado"),
            "5. Fecha de nacimiento: " + (publicar[4] ? (std::string)"Publico" : (std::string)"Privado"),
            "0. Salir"
        };

        mostrar_menu("Sexto: Que quieres configurar como publico?", opciones, 6);
        std::cin >> opcion;

        if (opcion > 0 && opcion <= 5)
        {
            publicar[opcion - 1] = !(publicar[opcion - 1]);
        }
    }
    while(opcion != 0);
}

// Contabiliza los usuarios que son admistradores.
int cantidad_administradores()
{
    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);
    int administradores = 0;

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if (usuarios[i].administrador)
        {
            administradores++;
        }
    }

    return administradores;
}

// Modifica el perfil del usuario actual.
void modificar_perfil(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Contrasenia: ********",
            ("2. Nombres: " + usuario_actual.nombres),
            ("3. Apellidos: " + usuario_actual.apellidos),
            ("4. Genero: " + (usuario_actual.genero == 'f' ? (std::string)"Femenino" : (std::string)"Masculino")),
            ("5. Correo electronico: " + usuario_actual.email),
            ("6. Fecha de nacimiento: "
                + std::to_string(usuario_actual.fecha_nacimiento.dia) + "/"
                + std::to_string(usuario_actual.fecha_nacimiento.mes) + "/"
                + std::to_string(usuario_actual.fecha_nacimiento.anio)
            ),
            "7. Publicacion datos",
            "0. Guardar y regresar"
        };
        mostrar_menu((usuario_actual.alias + ", que desea modificar?"), opciones, 8);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 :
                {
                    usuario_actual.contrasenia = actualizar_contrasenia(usuario_actual.contrasenia);
                }
                break;
            case 2 :
                {
                    std::cout << ("\tNombres actuales: " + usuario_actual.nombres) << std::endl;
                    usuario_actual.nombres = leer_nombres();
                }
                break;
            case 3 :
                {
                    std::cout << ("\tApellidos actuales: " + usuario_actual.apellidos) << std::endl;
                    usuario_actual.apellidos = leer_apellidos();
                }
                break;
            case 4 :
                {
                    std::cout <<
                        ("\tGenero actual: " + (usuario_actual.genero == 'f' ? (std::string)"Femenino" : (std::string)"Masculino"))
                        << std::endl;
                    usuario_actual.genero = leer_genero();
                }
                break;
            case 5 :
                {
                    std::cout << ("\tCorreo electronico: " + usuario_actual.email) << std::endl;
                    usuario_actual.email = leer_email(true);
                }
                break;
            case 6 :
                {
                    std::cout << (
                            "\tFecha de nacimiento: "
                            + std::to_string(usuario_actual.fecha_nacimiento.dia) + "/"
                            + std::to_string(usuario_actual.fecha_nacimiento.mes) + "/"
                            + std::to_string(usuario_actual.fecha_nacimiento.anio)
                        ) << std::endl;
                    usuario_actual.fecha_nacimiento = leer_fecha();
                }
                break;
            case 7 :
                {
                    bool publicar[] =
                        {
                            usuario_actual.nombres_publico,
                            usuario_actual.apellidos_publico,
                            usuario_actual.genero_publico,
                            usuario_actual.email_publico,
                            usuario_actual.fecha_nacimiento_publico
                        };

                    menu_publicar(publicar);

                    usuario_actual.nombres_publico = publicar[0];
                    usuario_actual.apellidos_publico = publicar[1];
                    usuario_actual.genero_publico = publicar[2];
                    usuario_actual.email_publico = publicar[3];
                    usuario_actual.fecha_nacimiento_publico = publicar[4];
                }
                break;
        }
    }
    while (opcion != 0);

    actualizar_usuario(usuario_actual);
}

// Actualiza la contraseña.
std::string actualizar_contrasenia(std::string anterior_contrasenia)
{
    limpiar_pantalla();

    std::cout << "Digita tu contrasenia actual" << std::endl;
    std::string contrasenia = leer_contrasenia();

    if (contrasenia.compare(anterior_contrasenia) == 0)
    {
        std::cout << "Digita tu nueva contrasenia" << std::endl;
        std::string nueva_contrasenia = leer_contrasenia();
        mensaje("Contrasenia actualizada!", "", true);
        return nueva_contrasenia;
    }
    else
    {
        mensaje("Lo siento! la contrasenia no coincide", "", true);
        return anterior_contrasenia;
    }
}

// Inactivar el perfil del usuario.
void inactivar_perfil(usuario usuario_actual)
{
    if (usuario_actual.activo)
    {
        char opcion;
        do
        {
            mensaje("Esta seguro de inactivar este perfil?", "", false);
            std::cout << "\t Digita tu opcion (s/n) -> ";
            std::cin >> opcion;
            opcion = tolower(opcion);
        }
        while (opcion != 's' && opcion != 'n');

        if (opcion == 's')
        {
            usuario_actual.activo = false;
            actualizar_usuario(usuario_actual);
            mensaje("Operacion exitosa", "El perfil ahora esta inactivo!", true);
        }
    }
    else
    {
        mensaje("No se pudo aplicar la operacion", "El usuario ya se encontraba inactivo!", true);
    }
}

// Activar el perfil del usuario.
void activar_perfil(usuario usuario_actual)
{
    if (!usuario_actual.activo)
    {
        char opcion;
        do
        {
            mensaje("Esta seguro de activar este perfil?", "", false);
            std::cout << "\t Digita tu opcion (s/n) -> ";
            std::cin >> opcion;
            opcion = tolower(opcion);
        }
        while (opcion != 's' && opcion != 'n');

        if (opcion == 's')
        {
            usuario_actual.activo = true;
            actualizar_usuario(usuario_actual);
            mensaje("Operacion exitosa", "El perfil ahora esta activo!", true);
        }
    }
    else
    {
        mensaje("No se pudo aplicar la operacion", "El usuario ya se encontraba activo!", true);
    }
}

// Eliminar el perfil del usuario.
void eliminar_perfil(usuario usuario_actual)
{
    if (!usuario_actual.activo)
    {
        char opcion;
        do
        {
            mensaje("Esta seguro de eliminar este perfil?", "", false);
            std::cout << "\t Digita tu opcion (s/n) -> ";
            std::cin >> opcion;
            opcion = tolower(opcion);
        }
        while (opcion != 's' && opcion != 'n');

        if (opcion == 's')
        {
            eliminar_usuario_favoritas(usuario_actual.alias);
            eliminar_todos_amigos(usuario_actual.alias);
            eliminar_usuario(usuario_actual);
        }
    }
    else
    {
        mensaje("No se pudo eliminar el perfil", "El usuario no se encontraba inactivo!", true);
    }
}

// Eliminar datos del usuario.
void eliminar_usuario(usuario usuario_actual)
{
    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);
    bool encontro = false;

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if (usuarios[i].alias.compare(usuario_actual.alias) == 0)
        {
            encontro = true;
        }
        if (encontro)
        {
            usuarios[i] = usuarios[i + 1];
        }
    }

    actualizar_archivo_usuarios(usuarios, --cantidad_usuarios);
    mensaje("El usuario ha sido eliminado!", "Por seguridad, se cierra el sistema.", true);
    exit(0);
}

// Buscar amigos,
void buscar_amigos(usuario usuario_actual)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Buscar amigos por nombres",
            "2. Buscar amigos por apellidos",
            "0. Regresar"
        };
        mostrar_menu("Buscar amigos", opciones, 3);
        std::cin >> opcion;

        switch (opcion)
        {
            case 1 : buscar_amigos_nombres(usuario_actual); break;
            case 2 : buscar_amigos_apellidos(usuario_actual); break;
        }
    }
    while (opcion != 0);
}

// Buscar amigos por sus nombres.
void buscar_amigos_nombres(usuario usuario_actual)
{
    std::cout << "\tDigita el nombre de la persona a buscar." << std::endl;
    std::string nombre = leer_nombres();

    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);

    limpiar_pantalla();

    std::cout << centrar_mensaje("Listado de posibles amigos", ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if (
            (usuarios[i].alias.compare(usuario_actual.alias) != 0)
            && (usuarios[i].nombres_publico)
            && (usuarios[i].nombres.find(nombre) != std::string::npos)
        )
        {
            if (es_amigo(usuario_actual.alias, usuarios[i].alias) == 0)
            {
                mostrar_usuario(usuarios[i], usuario_actual.administrador, false);
            }
        }
    }

    pausar();
}

// Buscar amigos por sus apellidos.
void buscar_amigos_apellidos(usuario usuario_actual)
{
    std::cout << "\tDigita los apellidos de la persona a buscar." << std::endl;
    std::string apellido = leer_apellidos();

    usuario usuarios[MAX_REGISTROS];
    int cantidad_usuarios = leer_archivo_usuarios(usuarios);

    limpiar_pantalla();

    std::cout << centrar_mensaje("Listado de posibles amigos", ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    for (int i = 0; i < cantidad_usuarios; i++)
    {
        if (
            (usuarios[i].alias.compare(usuario_actual.alias) != 0)
            && (usuarios[i].apellidos_publico)
            && (usuarios[i].apellidos.find(apellido) != std::string::npos)
        )
        {
            if (es_amigo(usuario_actual.alias, usuarios[i].alias) == 0)
            {
                mostrar_usuario(usuarios[i], usuario_actual.administrador, false);
            }
        }
    }

    pausar();
}

// Verifica si dos usuarios son dos amigos (0: no, 1: si, 2: solicitud).
int es_amigo(std::string alias_anfitrion, std::string alias_invitado)
{
    amigo amigos[MAX_REGISTROS];
    int cantidad_amigos = leer_archivo_amigos(amigos);

    for (int i = 0; i < cantidad_amigos; i++)
    {
        if (
            ((amigos[i].alias_anfitrion.compare(alias_anfitrion) == 0)
            && (amigos[i].alias_invitado.compare(alias_invitado) == 0))
            ||
            ((amigos[i].alias_anfitrion.compare(alias_invitado) == 0)
            && (amigos[i].alias_invitado.compare(alias_anfitrion) == 0))
        )
        {
            return (amigos[i].solicitud ? 2 : 1);
        }
    }

    return 0;
}

// Hacer solicitudes de amistad.
void solicitud_amistad(usuario usuario_actual)
{
    limpiar_pantalla();

    std::cout << "\t Por favor digita el correo de la persona a quien vas a invitar." << std::endl;
    std::string email = leer_email(false);

    usuario invitado = obtener_usuario("email", email);

    if ((invitado.genero == '#') || (!invitado.activo))
    {
        mensaje("Lo siento! Usuario no encontrado.", "", true);
    }
    else
    {
        int amistad = es_amigo(usuario_actual.alias, invitado.alias);
        switch (amistad)
        {
            case 0: nueva_solicitud_amistad(usuario_actual.alias, invitado.alias); break;
            case 1: mensaje(("Lo siento! " + email), " ya figuraba en tu lista de amigos.", true); break;
            case 2: mensaje(("Lo siento! " + email), " ya figuraba en la lista de solicitudes de amistad.", true); break;
        }
    }
}

// Nueva solicitud de amistad.
void nueva_solicitud_amistad(std::string anfitrion, std::string invitado)
{
    amigo nuevo;
    nuevo.alias_anfitrion = anfitrion;
    nuevo.alias_invitado = invitado;
    nuevo.solicitud = true;

    agregar_amistad_archivo(nuevo);

    mensaje("Solicitud de amistad enviada!", "", true);
}

// Listar solicitudes pendientes de amistad.
void listar_solicitudes_pendientes(usuario usuario_actual, bool aceptar)
{
    int opcion = 0;

    do
    {
        amigo solicitudes[MAX_REGISTROS];
        int cantidad_solicitudes = leer_archivo_amigos(solicitudes);

        limpiar_pantalla();

        std::cout << centrar_mensaje("Listado de solicitudes pendientes de amistad", ANCHO_LISTADO, ' ') << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

        int contador = 0;
        int indices[MAX_REGISTROS];

        for (int i = 0; i < cantidad_solicitudes; i++)
        {
            if (
                (solicitudes[i].alias_invitado.compare(usuario_actual.alias) == 0)
                && (solicitudes[i].solicitud)
            )
            {
                indices[contador++] = i;
                usuario anfitrion = obtener_usuario("alias", solicitudes[i].alias_anfitrion);
                std::cout
                    << to_string(i + 1)
                    << " - "
                    << solicitudes[i].alias_anfitrion
                    << " ("
                    << anfitrion.email
                    << ")"
                    << std::endl;
            }
        }

        if (contador == 0)
        {
            std::cout << "Lo siento! No existen solicitudes pendientes." << std::endl;
            pausar();
            opcion = 0;
        }
        else if (aceptar)
        {
            std::cout << "Digita el numero de la solicitud de amistad para aceptarla (0-salir) -> ";
            std::cin >> opcion;

            bool encontro = false;
            for (int j = 0; j < contador; j++)
            {
                if (indices[j] == (opcion - 1))
                {
                    encontro = true;
                    break;
                }
            }

            if (encontro)
            {
                solicitudes[opcion - 1].solicitud = false;
                actualizar_archivo_amigos(solicitudes, cantidad_solicitudes);
                mensaje("Solicitud de amistad aceptada!", "", true);
            }
            else if (opcion != 0)
            {
                mensaje("Lo siento! Numero de solicitud equivocado", "", true);
            }
        }
        else {
            opcion = 0;
            pausar();
        }
    }
    while (opcion != 0);
}

// Listar los amigos del usuario actual.
void listar_amigos(usuario usuario_actual)
{
    limpiar_pantalla();

    amigo amigos[MAX_REGISTROS];
    int cantidad_amigos = leer_archivo_amigos(amigos);

    std::cout << centrar_mensaje("Listado de amigos", ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;
    std::cout << "Alias      |Nombres       |Apellidos     |G|email                |nacimiento|A|a" << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    for (int i = 0; i < cantidad_amigos; i++)
    {
        if (!amigos[i].solicitud)
        {
            string alias_amigo = "";

            if (amigos[i].alias_anfitrion.compare(usuario_actual.alias) == 0)
            {
                alias_amigo = amigos[i].alias_invitado;
            }
            else if (amigos[i].alias_invitado.compare(usuario_actual.alias) == 0)
            {
                alias_amigo = amigos[i].alias_anfitrion;
            }

            if (alias_amigo.length() > (unsigned)0)
            {
                usuario usuario1 = obtener_usuario("alias", alias_amigo);

                if (usuario_actual.administrador || usuario1.activo)
                {
                    mostrar_usuario(usuario1, usuario_actual.administrador, true);
                }
            }
        }
    }

    pausar();
}

// Lista los datos de un amigo y sus películas favoritas.
void listar_amigo_pelicula(usuario usuario_actual)
{
    limpiar_pantalla();

    std::cout << "\t Por favor digita la cuenta de correo electronico de tu amig@." << std::endl;
    std::string email = leer_email(false);

    usuario amigo = obtener_usuario("email", email);

    if ((amigo.genero != '#') && (es_amigo(usuario_actual.alias, amigo.alias)) && (amigo.activo))
    {
        mostrar_usuario(amigo, usuario_actual.administrador, false);

        std::cout << "Sus películas favoritas son: " << std::endl << std::endl;
        mostrar_peliculas_favoritas(amigo.alias);
        pausar();
    }
    else
    {
        mensaje(("Lo siento! La persona con correo " + email), "no figura en la lista de tus amigos.", true);
    }
}

// Detecta las películas favoritas en común con un amigo.
void peliculas_comun(usuario usuario_actual)
{
    limpiar_pantalla();

    std::cout << "\t Por favor digita la cuenta de correo electronico de tu amig@." << std::endl;
    std::string email = leer_email(false);

    usuario amigo = obtener_usuario("email", email);

    if ((amigo.genero != '#') && (es_amigo(usuario_actual.alias, amigo.alias) && (amigo.activo)))
    {
        std::cout << endl;
        mostrar_peliculas_favoritas(amigo.alias);

        std::cout << endl;
        mostrar_peliculas_favoritas(usuario_actual.alias);

        favorita favoritas[MAX_REGISTROS];
        int cantidad_favoritas = leer_archivo_favoritas(favoritas);

        int contador = 0;
        std::string peliculas[MAX_REGISTROS];

        for (int i = 0; i < cantidad_favoritas; i++)
        {
            if (favoritas[i].alias.compare(usuario_actual.alias) == 0)
            {
                for (int j = 0; j < cantidad_favoritas; j++)
                {
                    if (
                        (favoritas[j].alias.compare(amigo.alias) == 0)
                        && (favoritas[i].codigo == favoritas[j].codigo)
                    )
                    {
                        pelicula pelicula1 = obtener_pelicula("codigo", to_string(favoritas[i].codigo));
                        peliculas[contador++] = pelicula1.nombre;
                    }
                }
            }
        }

        if (contador > 0)
        {
            std::cout << std::endl << "Las peliculas en comun son: " << std::endl;

            for (int i = 0; i < contador; i++)
            {
                std::cout << peliculas[i] << std::endl;
            }
        }
        else
        {
            std::cout << "No hay peliculas en comun!" << endl;
        }

        pausar();
    }
    else
    {
        mensaje(("Lo siento! La persona con correo " + email), "no figura en la lista de tus amigos.", true);
    }
}

// Deshace una amistad.
void deshacer_amistad(usuario usuario_actual)
{
    limpiar_pantalla();

    std::cout << "\t Por favor digita la cuenta de correo electronico de la persona a quitar de la lista de amigos." << std::endl;
    std::string email = leer_email(false);

    usuario amigo = obtener_usuario("email", email);

    if ((amigo.genero != '#') && (es_amigo(usuario_actual.alias, amigo.alias)) && (amigo.activo))
    {
        elimina_amistad(usuario_actual.alias, amigo.alias);
        mensaje(("La persona con correo " + email), "fue eliminada de la lista de tus amigos.", true);
    }
    else
    {
        mensaje(("Lo siento! La persona con correo " + email), "no figuraba en la lista de tus amigos.", true);
    }
}

// Elimina la amistad entre dos usuarios.
void elimina_amistad(std::string alias1, std::string alias2)
{
    amigo amigos[MAX_REGISTROS];
    int cantidad_amigos = leer_archivo_amigos(amigos);

    bool encontro = false;

    for (int i = 0; i < cantidad_amigos; i++)
    {
        if (
            ((amigos[i].alias_anfitrion.compare(alias1) == 0)
            && (amigos[i].alias_invitado.compare(alias2) == 0))
            || ((amigos[i].alias_anfitrion.compare(alias2) == 0)
            && (amigos[i].alias_invitado.compare(alias1) == 0))
        )
        {
            encontro = true;
        }
        if (encontro)
        {
            amigos[i] = amigos[i + 1];
        }
    }

    actualizar_archivo_amigos(amigos, --cantidad_amigos);
}

// Eliminar un usuario de todas sus amistades.
void eliminar_todos_amigos(std::string alias)
{
    amigo amigos[MAX_REGISTROS];
    int cantidad_amigos = leer_archivo_amigos(amigos);

    for (int i = 0; i < cantidad_amigos; i++)
    {
        if (
            (amigos[i].alias_anfitrion.compare(alias) == 0)
            ||
            (amigos[i].alias_invitado.compare(alias) == 0)
        )
        {
            for (int j = i; j < cantidad_amigos - 1; j++)
            {
                amigos[i] = amigos[i + 1];
            }
            cantidad_amigos--;
            i--;
        }
    }

    actualizar_archivo_amigos(amigos, cantidad_amigos);
}

