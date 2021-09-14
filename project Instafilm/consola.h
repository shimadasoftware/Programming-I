/**
    GNU GCC 8.1 C++17
    consola.h
    Purpose: Utilidades del manejo de salida de la aplicación por consola.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>

using namespace std;

// Ancho (en caracteres) de las ventanas a mostrar en la aplicación.
const int ANCHO_VENTANA = 60;

// Ancho (en caracteres) de los listados a mostrar en la aplicación.
const int ANCHO_LISTADO = 80;


/**
    Limpia la pantalla.
*/
void limpiar_pantalla();

/**
    Pausa una pantalla mientras que no se presione una tecla.
*/
void pausar();

/**
    Muestra un menú de opciones.

    @param titulo Título del menú.
    @param opciones Arreglo de las opciones del menú.
    @param cantidad_opciones Cantidad de opciones del menú.
*/
void mostrar_menu(std::string titulo, std::string opciones[], int cantidad_opciones);

/**
    Muestra mensajes en pantalla.

    @param mensaje1 Primer mensaje a mostrar.
    @param mensaje2 Segundo mensaje a mostrar.
    @param tamanio Tamaño de la ventana del mensaje (true-grande, false-reducido).
*/
void mensaje(std::string mensaje1, std::string mensaje2, bool tamanio);

/**
    Repetir n-veces un caracter en una línea de la pantalla.

    @param veces Cantidad de veces a repetir el caracter.
    @param caracter El carácter a mostrar.

    @return Cadena con el caracter repetido n-veces.
*/
std::string repetir_caracter(int veces, char caracter);

/**
    Repetir un texto en hasta un ancho de caracteres.

    @param ancho Ancho máximo en caracteres de la cadena resultante.
    @param texto Texto a repetir.

    @return Cadena repetida.
*/
std::string repetir_cadena(int ancho, std::string texto);

/**
    Mostrar el encabezado de la aplicación.
*/
void mostrar_encabezado();

/**
    Centrar un mensaje hasta un ancho de caracteres dentro de un relleno de caracteres.

    @param texto Texto a centrar.
    @param ancho Ancho máximo de la cadena resultante.
    @param relleno Caracter de relleno a lado y lado del texto centrado.

    @return Cadena de caracteres centrada.
*/
std::string centrar_mensaje(std::string texto, int ancho, char relleno);

#endif // CONSOLA_H
