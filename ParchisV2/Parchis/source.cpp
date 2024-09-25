#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

//CONSTANTES GLOBALES

const int NUM_CASILLAS = 68;

const int NUM_JUGADORES = 4;

const int NUM_FICHAS = 4;

//TIPOS

typedef enum { Amarillo, Azul, Rojo, Verde, Gris, Ninguno } tColor;

typedef int tFichas[NUM_FICHAS];

typedef tFichas tJugadores[NUM_JUGADORES];

//VARIABLES GLOBALES

tJugadores jugador;

tJugadores posTab;

tColor colorJugador[4];

int numJugador[4], turno = 0, d;

bool victoria[4];

//FUNCIONES

string colorACadena(tColor color);

char letra(tColor color);

int colorAJugador(tColor color);

void setColor(tColor color);

bool esSeguro(int casilla);

int dado();

int dadoManual();

void selColor(int num);

void iniciar();

int salidaJugador(tColor color);

int zanataJugador(tColor color);

void turnos(int num);

void mostrarPuedeMover();

bool puedeMover(int num);

void mover();

void mostrar();

void recuento();

void carrilPrincipal();


int main() {

    cout << "Bienvenido a la segunda version del parchis\n";

    numJugador[0] = 0;
    numJugador[1] = 0;
    numJugador[2] = 0;
    numJugador[3] = 0;

    selColor(0);
    selColor(1);
    selColor(2);
    selColor(3);

    iniciar();

    while (victoria[0] == false || victoria[1] == false || victoria[2] == false || victoria[3] == false) {

        turnos(turno);

        if (turno == 3) {
            turno = -1;
        }
        turno++;
    }
    return 0;
}
//FUNCIONES
string colorACadena(tColor color) {//FUNCION PARA DAR COLOR DEL JUGADOR

    string strColor;

    switch (color) {
    case Amarillo:
        strColor = "Amarillo";
        break;
    case Azul:
        strColor = "Azul";
        break;
    case Rojo:
        strColor = "Rojo";
        break;
    case Verde:
        strColor = "Verde";
        break;
    }
    return strColor;
}
char letra(tColor color) {//FUNCION PARA CARACTER DEL JUGADOR

    char letColor;

    switch (color) {
    case Amarillo:
        letColor = 'M';
        break;
    case Azul:
        letColor = 'A';
        break;
    case Rojo:
        letColor = 'R';
        break;
    case Verde:
        letColor = 'V';
        break;
    }
    return letColor;
}
int colorAJugador(tColor color) {//DEVUELVE INT DEL JUGADOR

    int numJug;

    switch (color) {
    case Amarillo:
        numJug = 0;
        break;
    case Azul:
        numJug = 1;
        break;
    case Rojo:
        numJug = 2;
        break;
    case Verde:
        numJug = 3;
        break;
    }

    return numJug;
}
void setColor(tColor color) {//ESTABLECE EL COLOR DEL JUGADOR EN LA CONSOLA
    switch (color) {
    case Amarillo:
        cout << "\x1b[33;107m";
        break;
    case Azul:
        cout << "\x1b[34;107m";
        break;
    case Rojo:
        cout << "\x1b[31;107m";
        break;
    case Verde:
        cout << "\x1b[32;107m";
        break;
    case Gris:
        cout << "\x1b[90;107m";
        break;
    case Ninguno:
        cout << "\x1b[2J\x1b[H";
        break;
    }
}
bool esSeguro(int casilla) {//FUNCION PARA DETERMINAR SI LA CASILLA ES SEGURA

    bool esSegura = false;

    if (casilla % 17 == 0 || casilla % 17 == 5 || casilla % 17 == 12) {
        esSegura = true;
    }
    else {
        esSegura = false;
    }

    return esSegura;
}
int dado() {//FUNCION DADO RANDOM
    int tirada;
    tirada = (rand() % 6) + 1;
    return tirada;
}
int dadoManual() {//FUNCION DADO CONTROLADO
    int tirada;
    cout << "Introduzca valor del dado: ";
    cin >> tirada;
    return tirada;
}
void selColor(int num) {//FUNCION PARA DETERMINAR EL COLOR DE CADA JUGADOR
    int color;

    //Seleccionamos los colores de cada jugador
    cout << "Elija el color del jugador " << num + 1 << " [Amarillo=1 Azul=2 Rojo=3 Verde=4]: ";
    cin >> color;

    while (color < 1 || color>4 || color == numJugador[0] || color == numJugador[1] || color == numJugador[2]) {
        cout << "Color incorrecto \nElija el color del jugador " << num + 1 << " [Amarillo=1 Azul=2 Rojo=3 Verde=4]: ";
        cin >> color;
    }

    numJugador[num] = color;
    colorJugador[num] = tColor(color - 1);
    cout << "El jugador " << num + 1 << " es el color: " << colorACadena(colorJugador[num]) << endl << endl;
}
void iniciar() {//FUNCION PARA RESETEAR TODOS LOS VALORES

    //Reseteamos los valores de las fichas
    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 4; x++) {
            jugador[i][x] = -1;
        }
    }

    turno = (rand() % 4);
    setColor(Gris);

}
int salidaJugador(tColor color) {//DETERMINA LA SALIDA DE UNA FICHA

    int salida;

    switch (color) {
    case Amarillo:
        salida = 5;
        break;
    case Azul:
        salida = 22;
        break;
    case Rojo:
        salida = 39;
        break;
    case Verde:
        salida = 56;
        break;
    }

    return salida;
}
int zanataJugador(tColor color) {

    int zanata;

    switch (color) {
    case Amarillo:
        zanata = 0;
        break;
    case Azul:
        zanata = 17;
        break;
    case Rojo:
        zanata = 34;
        break;
    case Verde:
        zanata = 51;
        break;
    }
    return zanata;
}
void turnos(int num) {

    tColor color;

    setColor(Ninguno);
    mostrar();
    setColor(colorJugador[num]);
    color = colorJugador[num];
    cout << "Es el turno del jugador " << colorACadena(color) << endl;

    system("pause");

    d = dado();

    cout << "El jugador ha sacado un " << d << endl << endl;

    cout << "Opciones...\n";
    mostrarPuedeMover();
    mover();
    system("pause");

}
void mostrarPuedeMover() {

    for (int i = 0; i < 4; i++) {
        if (jugador[turno][i] == -1) {
            if (d == 5) {
                cout << "La ficha " << i + 1 << " puede salir de casa\n";
            }
            else {
                cout << "La ficha " << i + 1 << " no puede salir de casa\n";
            }
        }
        else {
            cout << "la ficha " << i + 1 << " puede moverse de la casilla " << jugador[turno][i] << " a " << jugador[turno][i] + d << endl;
        }

    }
}
bool puedeMover(int num) {
    bool puede = false;
    if (jugador[turno][num] == -1) {
        if (d == 5) {
            puede = true;
        }
        else {
            puede = false;
        }
    }
    else {
        puede = true;
    }
    return puede;
}
void mover() {

    bool puede = false;
    int i;

    while (puede == false) {


        if (puedeMover(0) == false && puedeMover(1) == false && puedeMover(2) == false && puedeMover(3) == false) {
            cout << "\nNo se puede mover ninguna ficha, por lo que se pasa de turno\n\n";
            puede = true;
        }
        else {

            cout << "\nEscoja una de las opciones: ";
            cin >> i;

            if (puedeMover(i - 1) == false) {

                cout << "\nNo se puede mover esa ficha\n";
            }
            else if (jugador[turno][i - 1] == -1) {
                jugador[turno][i - 1] = 0;
                puede = true;
                cout << "\nLa ficha " << i << " a salido de casa\n";
            }
            else {
                jugador[turno][i - 1] += d;
                puede = true;
            }

        }
    }


}
void recuento() {

    for (int x = 0; x < 4; x++) {
        if (colorJugador[x] == Amarillo) {
            for (int j = 0; j < 4; j++) {
                posTab[x][j] = jugador[x][j] + 5;

            }

        }
        else if (colorJugador[x] == Azul) {
            for (int j = 0; j < 4; j++) {
                posTab[x][j] = jugador[x][j] + 22;

            }
        }
        else if (colorJugador[x] == Rojo) {
            for (int j = 0; j < 4; j++) {
                posTab[x][j] = jugador[x][j] + 39;

            }
        }
        else if (colorJugador[x] == Verde) {
            for (int j = 0; j < 4; j++) {
                posTab[x][j] = jugador[x][j] + 56;

            }
        }

    }

}
void carrilPrincipal() {

    recuento();
    for (int i = 0; i < NUM_CASILLAS; i++) {
        for (int j = 0; j < 4; j++) {
            for (int x = 0; x < 4; x++) {
                if (jugador[j][x] != -1) {
                    if (posTab[j][x] == i) {
                        setColor(tColor(j));
                        cout << x + 1;
                        setColor(Gris);
                    }
                    else {
                        cout << ' ';
                    }
                }

            }
        }
    }
    cout << endl;

}
void mostrar() {
    tColor colorjug;

    setColor(Gris);
    // Filas con la numeración de las casillas...
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << i / 10;
    cout << endl;
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << i % 10;
    cout << endl;

    // Borde superior...
    for (int i = 0; i < NUM_CASILLAS; i++)
        cout << '>';
    cout << endl << endl;

    //carrilSecundario();

    // "Mediana"
    for (int i = 0; i < NUM_CASILLAS; i++)
        if (esSeguro(i))
            cout << 'o';
        else
            cout << '-';
    cout << endl;

    carrilPrincipal();

    // Borde inferior...
    for (int i = 0; i < NUM_CASILLAS; i++) {


        if (i == zanataJugador(Amarillo) || i == zanataJugador(Azul) || i == zanataJugador(Rojo) || i == zanataJugador(Verde)) {
            for (int x = 0; x < 4; x++) {
                colorjug = tColor(x);
                if (i == zanataJugador(colorjug)) {
                    setColor(colorjug);
                    cout << "V";
                    setColor(Gris);
                }
            }
        }
        else if (i == salidaJugador(Amarillo) || i == salidaJugador(Azul) || i == salidaJugador(Rojo) || i == salidaJugador(Verde)) {
            for (int x = 0; x < 4; x++) {
                colorjug = tColor(x);
                if (i == salidaJugador(colorjug)) {
                    setColor(colorjug);
                    cout << "^";
                    setColor(Gris);
                }
            }
        }
        else {
            cout << '>';
        }
    }
    cout << endl;
}
