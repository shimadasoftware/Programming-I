/**
    GNU GCC 8.1 C++17
    peliculas.h
    Purpose: Módulo de películas de la aplicación InstaFilm.

    @author Juana Valentina Mendoza Santamaría (juana.mendoz4@gmail.com)
    @version 1.0 10/10/2018
*/

#include <iostream>
#include "peliculas.h"
#include "consola.h"

using namespace std;

// Lee los datos de una película y los almacena en el archivo de películas.
void crear_pelicula(usuario usuario_actual)
{
    if (usuario_actual.administrador)
    {
        mensaje("Nueva Pelicula", "Por favor digite los datos de la pelicula", false);

        std::string nombre = lee_nombre_pelicula();
        std::string genero = lee_genero_pelicula("");
        std::string descripcion = lee_descripcion_pelicula();
        int codigo = nuevo_codigo_pelicula();

        pelicula nueva_pelicula;
        nueva_pelicula.codigo = codigo;
        nueva_pelicula.nombre = nombre;
        nueva_pelicula.genero = genero;
        nueva_pelicula.descripcion = descripcion;

        agregar_pelicula_archivo(nueva_pelicula);
    }
    else
    {
        mensaje("Lo siento! No se puede crear la pelicula", "No tienes los suficientes privilegios.", true);
    }
}

// Lee el nombre de la pelicula.
std::string lee_nombre_pelicula()
{
    std::string nombre = "";
    do
    {
        std::cout << "\t Nombre de la pelicula -> ";
        getline(std::cin, nombre);
    }
    while (nombre.length() <= 0);

    return nombre;
}

// Lee el genero de la película.
std::string lee_genero_pelicula(std::string titulo)
{
    std::string opciones[] =
    {
        " 1. Accion     2. Ciencia ficcion  3. Comedia   4. Drama",
        " 5. Fantasia   6. Melodrama        7. Musical   8. Romance",
        " 9. Suspenso  10. Documental      11. Terror   12. Belico",
        "13. Animacion 14. Infantil        15. Epico    16. Thriller",
        "17. Western   18. Pornografico    19. Erotico  20. Otro"
    };
    int opcion;

    do
    {
        mostrar_menu(("Genero de la pelicula: " + titulo), opciones, 5);
        std::cin >> opcion;
    }
    while (opcion < 1 || opcion > 20);

    return generos_peliculas[opcion - 1];
}

// Lee la descripción de la película.
std::string lee_descripcion_pelicula()
{
    std::string descripcion = "";
    do
    {
        std::cout << "\t Descripcion de la pelicula -> ";
        getline(std::cin, descripcion);
    }
    while (descripcion.length() <= 0);

    return descripcion;
}

// Muestra los datos de una película en formato de columnas o detalle.
void listar_peliculas(bool tabular)
{
    pelicula peliculas[MAX_REGISTROS];
    int cantidad_peliculas = leer_archivo_peliculas(peliculas);

    limpiar_pantalla();

    std::cout << centrar_mensaje("Listado de peliculas", ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    if (tabular)
    {
        std::cout << "Cod|Nombre                        |Genero         |Descripcion" << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;
    }

    for (int i = 0; i < cantidad_peliculas; i++)
    {
        mostrar_pelicula(peliculas[i], tabular);
    }
}

//Muestra los datos de una película en formato de columnas o en detalle.
void mostrar_pelicula(pelicula pelicula1, bool tabular)
{
    if (pelicula1.nombre.length() <= (unsigned)0)
    {
        return;
    }
    if (tabular)
    {
        std::cout << centrar_mensaje(std::to_string(pelicula1.codigo), 3, ' ') << "|";
        std::cout << centrar_mensaje(pelicula1.nombre, 30, ' ') << "|";
        std::cout << centrar_mensaje(pelicula1.genero, 15, ' ') << "|";
        std::cout << centrar_mensaje(pelicula1.descripcion, 29, ' ');
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Código      : " << std::to_string(pelicula1.codigo) << std::endl;
        std::cout << "Nombre      : " << pelicula1.nombre << std::endl;
        std::cout << "Género      : " << pelicula1.genero << std::endl;
        std::cout << "Descripción : " << pelicula1.descripcion << std::endl;
        std::cout << std::endl;
    }
}

// Modifica los datos de una película.
void modificar_pelicula(usuario usuario_actual)
{
    if (usuario_actual.administrador)
    {
        listar_peliculas(true);
        cout << endl << " Digita el código de la película a modificar (0 para ninguna) -> ";
        int codigo;
        cin >> codigo;

        pelicula peliculas[MAX_REGISTROS];
        int cantidad_peliculas = leer_archivo_peliculas(peliculas);
        bool encontro = false;

        for (int i = 0; i < cantidad_peliculas; i++)
        {
            if (peliculas[i].codigo == codigo)
            {
                encontro = true;
                peliculas[i] = actualizar_pelicula(peliculas[i]);
            }
        }
        if (encontro)
        {
            actualizar_archivo_peliculas(peliculas, cantidad_peliculas);
        }
        else if (codigo != 0)
        {
            mensaje(("Lo siento! La pelicula con codigo " + std::to_string(codigo)), "no fue encontrada.", true);
        }
    }
    else
    {
        mensaje("Lo siento! No se puede modificar peliculas", "No tienes los suficientes privilegios.", true);
    }
}

// Obtiene los datos de un usuario buscándolo por un campo determinado.
pelicula obtener_pelicula(std::string campo, std::string valor)
{
    pelicula peliculas[MAX_REGISTROS];
    int cantidad_peliculas = leer_archivo_peliculas(peliculas);

    for (int i = 0; i < cantidad_peliculas; i++)
    {
        if ((campo.compare("codigo") == 0) && (peliculas[i].codigo == atoi(valor.c_str())))
        {
            return peliculas[i];
        }
        else if ((campo.compare("nombre") == 0) && (peliculas[i].nombre.compare(valor) == 0))
        {
            return peliculas[i];
        }
        else if ((campo.compare("genero") == 0) && (peliculas[i].genero.compare(valor) == 0))
        {
            return peliculas[i];
        }
        else if ((campo.compare("descripcion") == 0) && (peliculas[i].descripcion.compare(valor) == 0))
        {
            return peliculas[i];
        }
    }

    pelicula pelicula1;
    pelicula1.nombre = "";
    return pelicula1;
}

// Actualiza los datos de una película.
pelicula actualizar_pelicula(pelicula pelicula1)
{
    int opcion;
    do
    {
        std::string opciones[] =
        {
            "1. Modificar el nombre",
            "2. Modificar el genero",
            "3. Modificar la descripcion",
            "0. Guardar y regresar menu Gestion Peliculas"
        };
        mostrar_menu(("Modificar pelicula " + pelicula1.nombre), opciones, 4);
        std::cin >> opcion;

        limpiar_pantalla();

        switch (opcion)
        {
            case 1 :
                {
                    std::cout << ("El actual nombre de la película es: " + pelicula1.nombre) << endl;
                    pelicula1.nombre = lee_nombre_pelicula();
                }
                break;
            case 2 :
                {
                    std::cout << ("El actual género de la película es: " + pelicula1.genero) << endl;
                    pelicula1.genero = lee_genero_pelicula(pelicula1.genero);
                }
                break;
            case 3 :
                {
                    std::cout << ("La actual descripción de la película es: " + pelicula1.descripcion) << endl;
                    pelicula1.descripcion = lee_descripcion_pelicula();
                }
                break;
        }
    }
    while (opcion != 0);

    return pelicula1;
}

// Modifica los datos de una película.
void eliminar_pelicula(usuario usuario_actual)
{
    if (usuario_actual.administrador)
    {
        listar_peliculas(true);

        cout << endl << " Digita el codigo de la película a eliminar (0 para ninguna) -> ";
        int codigo;
        cin >> codigo;

        if (borra_pelicula(codigo))
        {
            eliminar_pelicula_favoritas(codigo);
            mensaje("La pelicula fue borrada.", "", true);
        }
        else if (codigo != 0)
        {
            mensaje(("Lo siento! La pelicula con codigo " + std::to_string(codigo)), "no fue encontrada.", true);
        }
    }
    else
    {
        mensaje("Lo siento! No se puede eliminar peliculas", "No tienes los suficientes privilegios.", true);
    }
}

// Elimina una película según su código.
bool borra_pelicula(int codigo_pelicula)
{
    pelicula peliculas[MAX_REGISTROS];
    int cantidad_peliculas = leer_archivo_peliculas(peliculas);

    bool encontro = false;

    for (int i = 0; i < cantidad_peliculas; i++)
    {
        if (peliculas[i].codigo == codigo_pelicula)
        {
            encontro = true;
        }
        if (encontro)
        {
            peliculas[i] = peliculas[i + 1];
        }
    }

    if (encontro)
    {
        actualizar_archivo_peliculas(peliculas, --cantidad_peliculas);
        return true;
    }
    else
    {
        return false;
    }
}

// Elimina una película de la lista de favoritas.
void eliminar_pelicula_favoritas(int codigo_pelicula)
{
    eliminar_conjunto_favoritas("codigo", to_string(codigo_pelicula));
}

// Elimina un usuario de la lista de favoritas.
void eliminar_usuario_favoritas(std::string alias)
{
    eliminar_conjunto_favoritas("alias", alias);
}

// Elimina un usuario de la lista de favoritas.
void eliminar_conjunto_favoritas(std::string campo, std::string valor)
{
    favorita favoritas[MAX_REGISTROS];
    int cantidad_favoritas = leer_archivo_favoritas(favoritas);

    for (int i = 0; i < cantidad_favoritas; i++)
    {
        if (
            ((campo.compare("alias") == 0) && (favoritas[i].alias.compare(valor) == 0))
            ||
            ((campo.compare("codigo") == 0) && (favoritas[i].codigo == atoi(valor.c_str())))
        )
        {
            for (int j = i; j < cantidad_favoritas - 1; j++)
            {
                favoritas[j] = favoritas[j + 1];
            }
            cantidad_favoritas--;
            i--;
        }
    }

    actualizar_archivo_favoritas(favoritas, cantidad_favoritas);
}

// Marcar una película como favorita.
void me_gusta(usuario usuario_actual)
{
    pelicula peliculas[MAX_REGISTROS];
    int cantidad_peliculas = leer_archivo_peliculas(peliculas);

    int opcion;

    do
    {
        limpiar_pantalla();

        std::cout << centrar_mensaje("Listado de peliculas", ANCHO_LISTADO, ' ') << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

        std::cout << "Cod|Nombre                        |Genero         |Descripcion" << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

        int contador = 0;
        int codigos[MAX_REGISTROS];

        for (int i = 0; i < cantidad_peliculas; i++)
        {
            if (!es_favorita(usuario_actual.alias, peliculas[i].codigo))
            {
                mostrar_pelicula(peliculas[i], true);
                codigos[contador++] = peliculas[i].codigo;
            }
        }

        std::cout << "Digita el codigo de la pelicula que te gusta (0 para volver) -> ";
        cin >> opcion;

        bool encontro = false;
        for (int i = 0; i < contador; i++)
        {
            if (opcion == codigos[i])
            {
                encontro = true;
                break;
            }
        }

        if (encontro)
        {
            favorita nueva_favorita;
            nueva_favorita.alias = usuario_actual.alias;
            nueva_favorita.codigo = opcion;
            agregar_favorita_archivo(nueva_favorita);
            mensaje("Pelicula marcada como favorita", "", true);
        }
        else if (opcion != 0)
        {
            mensaje("Codigo erroneo!", "Por favor, vuelve a digitarlo.", true);
        }
    }
    while (opcion != 0);
}

// Quitar una película de su listado de favoritas.
void no_me_gusta(usuario usuario_actual)
{

    int opcion;

    do
    {
        limpiar_pantalla();

        std::cout << centrar_mensaje("Listado de tus peliculas favoritas", ANCHO_LISTADO, ' ') << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

        std::cout << "Cod|Nombre                        |Genero         |Descripcion" << std::endl;
        std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

        favorita favoritas[MAX_REGISTROS];
        int cantidad_favoritas = leer_archivo_favoritas(favoritas);

        int contador = 0;
        int codigos[MAX_REGISTROS];

        for (int i = 0; i < cantidad_favoritas; i++)
        {
            if (favoritas[i].alias.compare(usuario_actual.alias) == 0)
            {
                pelicula pelicula_favorita;
                pelicula_favorita = obtener_pelicula("codigo", to_string(favoritas[i].codigo));
                mostrar_pelicula(pelicula_favorita, true);
                codigos[contador++] = favoritas[i].codigo;
            }
        }

        std::cout << "Digita el codigo de la pelicula que ya NO te gusta (0 para volver) -> ";
        cin >> opcion;

        bool encontro = false;
        for (int i = 0; i < contador; i++)
        {
            if (opcion == codigos[i])
            {
                encontro = true;
                break;
            }
        }

        if (encontro)
        {
            elimina_favorita(usuario_actual.alias, opcion);
            mensaje("Pelicula eliminada como favorita", "", true);
        }
        else if (opcion != 0)
        {
            mensaje("Codigo erroneo!", "Por favor, vuelve a digitarlo.", true);
        }
    }
    while (opcion != 0);
}

// Verifica si la película es favorita de una persona (true: si, false: no).
bool es_favorita(std::string alias, int codigo)
{
    favorita favoritas[MAX_REGISTROS];
    int cantidad_favoritas = leer_archivo_favoritas(favoritas);

    for (int i = 0; i < cantidad_favoritas; i++)
    {
        if (
            (favoritas[i].alias.compare(alias) == 0)
            && (favoritas[i].codigo == codigo)
        )
        {
            return true;
        }
    }

    return false;
}

// Elimina una película de la lista de favoritos.
void elimina_favorita(std::string alias, int codigo)
{
    favorita favoritas[MAX_REGISTROS];
    int cantidad_favoritas = leer_archivo_favoritas(favoritas);
    bool encontro = false;

    for (int i = 0; i < cantidad_favoritas; i++)
    {
        if ((favoritas[i].alias.compare(alias) == 0) && (favoritas[i].codigo == codigo))
        {
            encontro = true;
        }
        if (encontro)
        {
            favoritas[i] = favoritas[i + 1];
        }
    }
    if (encontro)
    {
        actualizar_archivo_favoritas(favoritas, --cantidad_favoritas);
    }
}

// Muestra las películas favoritas de un usuario.
void mostrar_peliculas_favoritas(std::string alias)
{
    std::cout << centrar_mensaje(("Listado de peliculas favoritas de " + alias), ANCHO_LISTADO, ' ') << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;
    std::cout << "Cod|Nombre                        |Genero         |Descripcion" << std::endl;
    std::cout << centrar_mensaje("-", ANCHO_LISTADO, '-') << std::endl;

    favorita favoritas[MAX_REGISTROS];
    int cantidad_favoritas = leer_archivo_favoritas(favoritas);

    for (int i = 0; i < cantidad_favoritas; i++)
    {
        if (favoritas[i].alias.compare(alias) == 0)
        {
            pelicula pelicula_favorita = obtener_pelicula("codigo", to_string(favoritas[i].codigo));
            mostrar_pelicula(pelicula_favorita, true);
        }
    }
}

