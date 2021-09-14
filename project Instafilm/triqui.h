/**
    GNU GCC 8.1 C++17
    triqui.h
    Purpose: Juego de triqui.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#ifndef TRIQUI_H
#define TRIQUI_H

#include "datos.h"

const std::string cruz[] =
{
    {"XX    XX"},
    {" XX  XX "},
    {"  XXXX  "},
    {" XX  XX "},
    {"XX    XX"}
};

const std::string bola[] =
{
    {"  OOOO  "},
    {" OO  OO "},
    {"OO    OO"},
    {" OO  OO "},
    {"  OOOO  "}
};

const std::string tablero_pantalla[] =
{
    {"::::::::::::::::::::::::::::::::::::::"},
    {"::    11    ::  222222  ::  333333  ::"},
    {"::    11    ::      22  ::      33  ::"},
    {"::    11    ::  222222  ::    3333  ::"},
    {"::    11    ::  22      ::      33  ::"},
    {"::    11    ::  222222  ::  333333  ::"},
    {"::::::::::::::::::::::::::::::::::::::"},
    {"::  44  44  ::  555555  ::  666666  ::"},
    {"::  44  44  ::  55      ::  66      ::"},
    {"::  4444444 ::  555555  ::  666666  ::"},
    {"::      44  ::      55  ::  66  66  ::"},
    {"::      44  ::  555555  ::  666666  ::"},
    {"::::::::::::::::::::::::::::::::::::::"},
    {"::  7777777 ::  888888  ::  999999  ::"},
    {"::       77 ::  88  88  ::  99  99  ::"},
    {"::     7777 ::  888888  ::  999999  ::"},
    {"::       77 ::  88  88  ::      99  ::"},
    {"::       77 ::  888888  ::      99  ::"},
    {"::::::::::::::::::::::::::::::::::::::"}
};

/**
    Verificación previa al jugar triqui.

    @param usuario_actual Usuario actual que va a jugar.
*/
void jugar_triqui(usuario usuario_actual);

/**
    Ingreso del contricante para jugar triqui.

    @return Contrincante.
*/
usuario ingreso_contrincante();

/**
    Jugar al triqui.

    @param jugador Jugador quien invita.
    @param contrincante Contrincante.
*/
void triqui(std::string jugador, std::string contrincante);

/**
    Inicializar el tablero de triqui.

    @param tablero Tablero del triqui.
*/
void inicializar_tablero_triqui(int tablero[][3], std::string tablero_mostrar[]);

/**
    Mostrar el tablero de triqui.

    @param tablero Tablero a mostrar del triqui.
*/
void mostrar_tablero_triqui(std::string tablero[]);

/**
    Mostrar las posiciones disponibles para jugar.

    @param tablero Tablero de triqui.
    @return Cadena de texto con las posiciones disponibles.
*/
std::string mostrar_disponibles(int tablero[][3]);

/**
    Lee una posición del tablero del triqui.

    @param turno Turno del juego (jugador vs contrincante).
    @param jugador Alias del jugador.
    @param contrincante Alias del contrincante.
    @param tablero Tablero del juego de triqui.
    @param coordenada Fila, columna y posición leídas.
*/
void lee_posicion_triqui(bool turno, std::string jugador, std::string contrincante, int tablero[][3], int coordenada[]);

/**
    Actualiza el tablero que hay que mostrar en pantalla.

    @param tablero Tablero con las jugadas.
    @param tablero_mostrar Tablero a mostrar en pantalla.
    @param coordenada Fila, columna y posición a actualizar.
    @param turno Turno de juego.
*/
void actualiza_tablero(int tablero[][3], std::string tablero_mostrar[], int coordenada[], bool turno);

/**
    Determina el fin de juego del triqui.

    @param tablero Tablero del juego triqui.
    @return 0, no hay triqui, 1 - triqui jugador, 2 - triqui contrincante, 3 - empate.
*/
int fin_juego_triqui(int tablero[][3]);

/**
    Analiza la jugada de triqui.

    @param tablero Tablero.
    @param fila Fila.
    @param columna Columna.
    @return True Se detectó triqui.
*/
bool analiza_triqui(int tablero[][3], int fila, int columna);

/**
    Finaliza el juego triqui.

    @param resultado Resultado del juego.
    @param jugador Alias del jugador.
    @param contrincante Alias del contrincante.
*/
void finalizar_triqui(int resultado, std::string jugador, std::string contrincante);

/**
    Agrega el registro de estadística al archivo.

    @param alias_jugador Alias del jugador.
    @param alias_contrincante Alias del contrincante.
    @param juego Nombre del juego.
    @param resultado Resultado del juego para el jugador.
*/
void registra_estadistica(std::string alias_jugador, std::string alias_contrincante, std::string juego, int resultado);

/**
    Muestra la estadística del juego triqui.

    @param usuario_actual Usuario actual.
*/
void estadistica_triqui(usuario usuario_actual);

#endif // TRIQUI_H
