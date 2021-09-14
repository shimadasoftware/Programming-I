/**
    GNU GCC 8.1 C++17
    consola.cpp
    Purpose: Utilidades del manejo de salida de la aplicación por consola.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <string>
#include <consola.h>

// Limpia la pantalla.
void limpiar_pantalla()
{
    system("cls");                  // Windows
    //system("clear");              // Linux
}

// Pausa una pantalla mientras que no se presione una tecla.
void pausar()
{
    system("pause");                // Windows
    //std::string comando = "read -n1 -r -p \"Presione cualquier tecla para continuar...\" key";
    //system(comando.c_str());      // Linux
}

// Muestra un menú de opciones.
void mostrar_menu(std::string titulo, std::string opciones[], int cantidad_opciones)
{
    mostrar_encabezado();

    std::cout << "\t|" << repetir_caracter(ANCHO_VENTANA, ' ') << "|" << std::endl;
    std::cout << "\t|" << centrar_mensaje(titulo, ANCHO_VENTANA, ' ') << "|" << std::endl;
    std::cout << "\t|" << repetir_caracter(ANCHO_VENTANA, ' ') << "|" << std::endl;

    for (int i = 0; i < cantidad_opciones; i++)
    {
        if (opciones[i].length() > (unsigned)ANCHO_VENTANA)
        {
            std::cout << "\t| " << opciones[i].substr(0, ANCHO_VENTANA) << "|" << std::endl;
        }
        else
        {
            std::cout << "\t| " << opciones[i] << repetir_caracter(ANCHO_VENTANA - opciones[i].length() - 1, ' ') << "|" << std::endl;
        }
    }

    std::cout << "\t|" << repetir_caracter(ANCHO_VENTANA, ' ') << "|" << std::endl;
    std::cout << "\t+" << repetir_caracter(ANCHO_VENTANA, '-') << "+" << std::endl;
    std::cout << "\t Digita tu opcion -> ";
}

// Muestra mensajes en pantalla.
void mensaje(std::string mensaje1, std::string mensaje2, bool tamanio)
{
    limpiar_pantalla();

    std::cout << "\t" << centrar_mensaje("''~``", ANCHO_VENTANA + 2, ' ') << std::endl;
    std::cout << "\t" << centrar_mensaje("( o o )", ANCHO_VENTANA + 2, ' ') << std::endl;
    std::cout << "\t+" << centrar_mensaje(".oooO--(_)--Oooo.", ANCHO_VENTANA, '-') << "+" << std::endl;
    std::cout << "\t|" << repetir_caracter(ANCHO_VENTANA, ' ') << "|" << std::endl;
    std::cout << "\t|" << centrar_mensaje(mensaje1, ANCHO_VENTANA, ' ') << "|" << std::endl;
    std::cout << "\t|" << centrar_mensaje(mensaje2, ANCHO_VENTANA, ' ') << "|" << std::endl;

    if (tamanio)
    {
        std::cout << "\t|" << centrar_mensaje(".oooO        ", ANCHO_VENTANA, ' ') << "|" << std::endl;
        std::cout << "\t|" << centrar_mensaje("(   )   Oooo.", ANCHO_VENTANA, ' ') << "|" << std::endl;
        std::cout << "\t+" << centrar_mensaje("-\\ (----(   )", ANCHO_VENTANA, '-') << "+" << std::endl;
        std::cout << "\t" << centrar_mensaje(" \\_)    ) /", ANCHO_VENTANA + 2, ' ') << std::endl;
        std::cout << "\t" << centrar_mensaje("       (_/", ANCHO_VENTANA + 2, ' ') << std::endl;
        pausar();
    }
}

// Repetir n-veces un caracter en una línea de la pantalla.
std::string repetir_caracter(int veces, char caracter)
{
    std::string cadena(veces, caracter);
    return cadena;
}

// Repetir un texto en hasta un ancho de caracteres.
std::string repetir_cadena(int ancho, std::string texto)
{
    std::string cadena = "";

    while ((cadena.length() + texto.length()) <= (unsigned)ancho)
    {
        cadena += texto;
    }

    int i = 0;
    while (cadena.length() < (unsigned)ancho)
    {
        cadena += texto.at(i++);
    }

    return cadena;
}

// Mostrar el encabezado de la aplicación.
void mostrar_encabezado()
{
    limpiar_pantalla();
    std::cout << "\t"  << repetir_cadena(ANCHO_VENTANA + 2, " []")                      << std::endl;
    std::cout << "\t+" << repetir_caracter(ANCHO_VENTANA, '-')                   << "+" << std::endl;
    std::cout << "\t|" << centrar_mensaje("InstaFilm", ANCHO_VENTANA, ' ')       << "|" << std::endl;
    std::cout << "\t+" << centrar_mensaje("------------>>>", ANCHO_VENTANA, '-') << "+" << std::endl;
    std::cout << "\t"  << repetir_cadena(ANCHO_VENTANA + 2, " []")                      << std::endl;
}

// Centrar un mensaje hasta un ancho de caracteres dentro de un relleno de caracteres.
std::string centrar_mensaje(std::string texto, int ancho, char relleno)
{
    std::string cadena;
    if (texto.length() <= (unsigned)ancho)
    {
        int inicio = ancho / 2 - texto.length() / 2;
        int fin = ancho - inicio - texto.length();
        cadena = repetir_caracter(inicio, relleno) + texto + repetir_caracter(fin, relleno);
    }
    else
    {
        cadena = texto.substr(0, ancho);
    }
    return cadena;
}

