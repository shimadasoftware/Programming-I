/**
    GNU GCC 8.1 C++17
    triqui.cpp
    Purpose: Juego de triqui.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include <time.h>
#include "triqui.h"
#include "consola.h"
#include "amigos.h"

using namespace std;

// Verificación previa al jugar triqui.
void jugar_triqui(usuario usuario_actual)
{
    limpiar_pantalla();
    mensaje("Bienvenid@ a triqui!", "Dile a tu amig@ que digite su correo y contrasenia.", true);

    usuario contrincante = ingreso_contrincante();

    if (contrincante.genero != '#')
    {
        if (es_amigo(usuario_actual.alias, contrincante.alias))
        {
            char opcion;
            do
            {
                triqui(usuario_actual.alias, contrincante.alias);
                std::cout << "Desea otra partida (s/n) -> ";
                cin >> opcion;
            }
            while (tolower(opcion) == 's');
        }
        else
        {
            mensaje("Lo siento!", (usuario_actual.alias + "no esta en tu lista de amigos."), true);
        }
    }
    else
    {
        mensaje("Ingreso no autorizado!", "La combinacion de correo y contrasena no es correcta.", true);
    }
}

// Ingreso del contricante para jugar triqui.
usuario ingreso_contrincante()
{
    mensaje("Tu eres el contrincante!", "Por favor, ingresa tu correo electronico.", false);
    std::string email = leer_email(false);

    mensaje("Contrincante:", "Por favor, ingresa tu contrasena.", false);
    std::string contrasenia = leer_contrasenia();

    usuario contrincante = obtener_usuario("email", email);

    if ((contrincante.genero != '#') && (contrincante.contrasenia.compare(contrasenia) != 0))
    {
        contrincante.genero = '#';
    }

    return contrincante;
}

// Jugar al triqui.
void triqui(std::string jugador, std::string contrincante)
{
    int tablero[3][3];

    std::string tablero_mostrar[19];
    inicializar_tablero_triqui(tablero, tablero_mostrar);

    srand (time(NULL));
    bool turno = rand() % 2 == 0;

    int coordenada[3];
    int resultado = 0;

    do
    {
        mostrar_tablero_triqui(tablero_mostrar);
        lee_posicion_triqui(turno, jugador, contrincante, tablero, coordenada);
        actualiza_tablero(tablero, tablero_mostrar, coordenada, turno);
        resultado = fin_juego_triqui(tablero);
        turno = !turno;
    }
    while (resultado == 0);

    finalizar_triqui(resultado, jugador, contrincante);
}

// Inicializar el tablero de triqui.
void inicializar_tablero_triqui(int tablero[][3], std::string tablero_mostrar[])
{
    for (int f = 0; f < 3; f++)
    {
        for (int c = 0; c < 3; c++)
        {
            tablero[f][c] = 0;
        }
    }

    for (int i = 0; i < 19; i++)
    {
        tablero_mostrar[i] = tablero_pantalla[i];
    }
}

// Mostrar el tablero de triqui.
void mostrar_tablero_triqui(std::string tablero[])
{
    limpiar_pantalla();

    for (int i = 0; i < 19; i++) {
        std::cout << tablero[i] << endl;
    }
}

// Mostrar las posiciones disponibles para jugar.
std::string mostrar_disponibles(int tablero[][3])
{
    std::string cadena = "( ";

    for (int f = 0; f < 3; f++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (tablero[f][c] == 0)
            {
                cadena += to_string(f * 3 + c + 1) + " ";
            }
        }
    }

    cadena += ")";

    return cadena;
}

// Lee una posición del tablero del triqui.
void lee_posicion_triqui(bool turno, std::string jugador, std::string contrincante, int tablero[][3], int coordenada[])
{
    int fila;
    int columna;
    int posicion;

    do
    {
        std::cout << "Es el turno de " << (turno ? jugador: contrincante) << ":" << std::endl;
        std::cout << "Digita la posicion a jugar " << mostrar_disponibles(tablero) << " -> ";
        std::cin >> posicion;

        fila = (int)((posicion - 1) / 3);
        columna = posicion - fila * 3 - 1;

        if (tablero[fila][columna] != 0)
        {
            std::cout << "Por favor digita una posicion valida!" << std::endl;
        }
    }
    while (tablero[fila][columna] != 0);

    coordenada[0] = fila;
    coordenada[1] = columna;
    coordenada[2] = posicion;
}

// Actualiza el tablero que hay que mostrar en pantalla.
void actualiza_tablero(int tablero[][3], std::string tablero_mostrar[], int coordenada[], bool turno)
{
    int fila_inicial = coordenada[0] * 6 + 1;
    int columna_inicial = coordenada[1] * 12 + 3;

    for (int f = 0; f < 5; f++)
    {
        for (int c = 0; c < (int)cruz[0].length(); c++)
        {
            if (turno)
            {
                tablero_mostrar[fila_inicial + f].at(columna_inicial + c) = cruz[f][c];
            }
            else
            {
                tablero_mostrar[fila_inicial + f].at(columna_inicial + c) = bola[f][c];
            }
        }
    }

    tablero[coordenada[0]][coordenada[1]] = turno ? 1 : 2;
}

// Determina el fin de juego del triqui.
int fin_juego_triqui(int tablero[][3])
{
    bool celda_libre = false;

    for (int f = 0; f < 3; f++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (tablero[f][c] == 0)
            {
                celda_libre = true;
            }
            else if (analiza_triqui(tablero, f, c))
            {
                return tablero[f][c];
            }
        }
    }

    if (celda_libre)
    {
        return 0;
    }
    else
    {
        return 3;
    }
}

// Analiza la jugada de triqui.
bool analiza_triqui(int tablero[][3], int fila, int columna)
{
    if ((tablero[fila][0] != 0) && (tablero[fila][0] == tablero[fila][1]) && (tablero[fila][0] == tablero[fila][2]))
    {
        return true;
    }
    else if ((tablero[0][columna] != 0) && (tablero[0][columna] == tablero[1][columna]) && (tablero[0][columna] == tablero[2][columna]))
    {
        return true;
    }
    else if ((tablero[0][0] != 0) && (tablero[0][0] == tablero[1][1]) && (tablero[0][0] == tablero[2][2]))
    {
        return true;
    }
    else if ((tablero[0][2] != 0) && (tablero[0][2] == tablero[1][1]) && (tablero[0][2] == tablero[2][0]))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Finaliza el juego triqui.
void finalizar_triqui(int resultado, std::string jugador, std::string contrincante)
{
    registra_estadistica(jugador, contrincante, "triqui", resultado);
    pausar();
}

// Agrega el registro de estadística al archivo.
void registra_estadistica(std::string alias_jugador, std::string alias_contrincante, std::string juego, int resultado)
{
    estadistica estadistica_jugador;
    estadistica estadistica_contrincante;

    estadistica_jugador.alias = alias_jugador;
    estadistica_jugador.juego = juego;
    estadistica_jugador.resultado = resultado;

    estadistica_contrincante.alias = alias_contrincante;
    estadistica_contrincante.juego = juego;

    if (resultado == 1)
    {
        estadistica_contrincante.resultado = 2;
        std::cout << alias_jugador << " es el ganador!!!" << std::endl;
    }
    else if (resultado == 2)
    {
        estadistica_contrincante.resultado = 1;
        std::cout << alias_contrincante << " es el ganador!!!" << std::endl;
    }
    else
    {
        estadistica_contrincante.resultado = resultado;
        std::cout << "Juego empatado!!!" << std::endl;
    }

    agregar_estadistica_archivo(estadistica_jugador);
    agregar_estadistica_archivo(estadistica_contrincante);
}


// Muestra la estadística del juego triqui.
void estadistica_triqui(usuario usuario_actual)
{
    estadistica estadisticas[MAX_REGISTROS];
    int cantidad_estadisticas = leer_archivo_estadisticas(estadisticas);

    int ganados = 0;
    int perdidos = 0;
    int empatados = 0;

    for (int i = 0; i < cantidad_estadisticas; i++)
    {
        if (estadisticas[i].alias.compare(usuario_actual.alias) == 0)
        {
            switch (estadisticas[i].resultado)
            {
                case 1 : ganados++; break;
                case 2 : perdidos++; break;
                case 3 : empatados++; break;
            }
        }
    }

    limpiar_pantalla();

    mensaje(("Estadisticas Juego Triqui de " + usuario_actual.alias), "", false);
    std::cout << std::endl;
    std::cout << "\tJuegos Ganados  : " << ganados << std::endl;
    std::cout << "\tJuegos Peridos  : " << perdidos << std::endl;
    std::cout << "\tJuegos Empatados: " << empatados << std::endl;
    std::cout << std::endl;

    pausar();
}

