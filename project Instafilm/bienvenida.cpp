/**
    GNU GCC 8.1 C++17
    bienvenida.cpp
    Purpose: Bienvenida de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include "bienvenida.h"
#include "consola.h"
#include "ingreso.h"
#include "registro.h"

using namespace std;

// Mostrar menú de bienvenida de la aplicación (ingreso y registro).
void menu_bienvenida()
{
    int opcion;

    do
    {
        string opciones[] =
        {
            "1. Ingresar a InstaFilm (usuarios ya registrados)",
            "2. Registrarse (usuarios nuevos, en solo 6 pasos)",
            "0. Salir"
        };
        mostrar_menu("Bienvenid@", opciones, 3);
        cin >> opcion;

        switch (opcion)
        {
            case 1 : ingreso(); break;
            case 2 : registro(); break;
        }
    }
    while(opcion != 0);
}

