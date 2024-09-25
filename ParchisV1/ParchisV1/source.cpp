#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

//TCOLOR
typedef enum { rojo, amarillo, verde, azul } tColor;

//VARIABLES GLOBALES
const int numCasillas = 68;
int pos1 = -1, pos2 = -1, posTab1, posTab2;
tColor jug1, jug2;
//DECLARAR FUNCIONES
string colorACadena(tColor color);
char letra(tColor color);
bool casSegura(int pos);
void carrilPrincipal();
void fichaCasa();
int dado();
int dadoManual();
void comer(tColor jug);
void genTablero();

//FUNCION PRINCIPAL
int main() {

    int sel1, sel2, d, cambioTurnos = 0, triple = 0;
    bool vict1 = false, vict2 = false, turno = false;

    //Selección de color
    cout << "Elija el color del jugador 1 [Rojo=1 Amarillo=2 Verde=3 Azul=4]: ";
    cin >> sel1;

    while (sel1 < 1 || sel1>4) {
        cout << "Color incorrecto \nElija el color del jugador 1 [Rojo=1 Amarillo=2 Verde=3 Azul=4]: ";
        cin >> sel1;
    }

    jug1 = tColor(sel1);
    cout << "El jugador 1 es el color: " << colorACadena(jug1) << endl;
    cout << "Elija el color del jugador 2 [Rojo=1 Amarillo=2 Verde=3 Azul=4]: ";
    cin >> sel2;

    while (sel2 < 1 || sel2>4 || sel2 == sel1) {
        cout << "Color incorrecto \nElija el color del jugador 2 [Rojo=1 Amarillo=2 Verde=3 Azul=4]: ";
        cin >> sel2;
    }

    jug2 = tColor(sel2);
    cout << "El jugador 2 es el color: " << colorACadena(jug2) << endl;

    system("pause");

    //Empieza la generacion del tablero
    genTablero();

    //Turnos
    while (!vict1 && !vict2) {

        cambioTurnos++;

        if (cambioTurnos % 2 == 1) {
            turno = true;
        }
        else {
            turno = false;
        }

        d = 0;
        if (turno == true) {

            cout << "Es el turno del jugador 1:\n";
            triple = 0;
            do {
                triple++;
                if (triple < 4) {
                    if (d == 6) {
                        cout << "El jugador 1 ha sacado un 6 y...   TIRO EXTRA!\n";
                    }
                    system("pause");

                    d = dado();

                    if (pos1 == -1) {
                        if (d == 5) {
                            cout << "El jugador 1 ha sacado un 5 y sale de casa\n";
                            pos1 = 0;
                            if (jug1 == rojo) {
                                posTab1 = pos1 + 5;
                            }
                            else if (jug1 == amarillo) {
                                posTab1 = pos1 + 22;
                            }
                            else if (jug1 == verde) {
                                posTab1 = pos1 + 39;
                            }
                            else if (jug1 == azul) {
                                posTab1 = pos1 + 56;
                            }
                            if (posTab1 == posTab2) {
                                pos2 = -1;
                            }
                        }
                        else {
                            cout << "El jugador 1 ha sacado un " << d << " y no ha conseguido salir de la casa\n";
                        }
                    }
                    else {
                        cout << "El jugador ha sacado un " << d << endl;
                        if (pos1 + d < 63) {
                            pos1 += d;
                        }
                        else if (pos1 + d > 63) {
                            cout << "Se ha pasado de la zanata\n";
                        }
                        else if (pos1 + d == 63) {
                            cout << "Ha ganado el jugador 1\n";
                            return 0;
                        }
                    }
                    if (letra(jug1) == 'R') {
                        posTab1 = pos1 + 5;
                    }
                    else if (letra(jug1) == 'M') {
                        posTab1 = pos1 + 22;
                    }
                    else if (letra(jug1) == 'V') {
                        posTab1 = pos1 + 39;
                    }
                    else if (letra(jug1) == 'A') {
                        posTab1 = pos1 + 56;
                    }
                    if (posTab1 == posTab2) {
                        if (casSegura(posTab1) == false) {
                            cout << "El jugador 1 a comido al jugador 2\n";
                            pos1 += 20;
                            pos2 = -1;
                        }
                    }
                    genTablero();

                }
                else if (triple == 4) {
                    cout << "El jugador ha sacado 3 seis seguidos y se va a casa";
                    pos1 = -1;
                    d = 0;
                    genTablero();
                }
            } while (d == 6);

        }
        d = 0;
        if (turno == false) {

            cout << "Es el turno del jugador 2:\n";

            triple = 0;
            do {
                triple++;
                if (triple < 4) {
                    if (d == 6) {
                        cout << "El jugador 2 ha sacado un 6 y...   TIRO EXTRA!\n";
                    }
                    system("pause");

                    d = dado();

                    if (pos2 == -1) {
                        if (d == 5) {
                            cout << "El jugador 2 ha sacado un 5 y sale de casa\n";
                            pos2 = 0;
                            if (letra(jug2) == 'R') {
                                posTab2 = pos2 + 5;
                            }
                            else if (letra(jug2) == 'M') {
                                posTab2 = pos2 + 22;
                            }
                            else if (letra(jug2) == 'V') {
                                posTab2 = pos2 + 39;
                            }
                            else if (letra(jug2) == 'A') {
                                posTab2 = pos2 + 56;
                            }
                            if (posTab1 == posTab2) {
                                pos1 = -1;
                            }
                        }
                        else {
                            cout << "El jugador 2 ha sacado un " << d << " y no ha conseguido salir de la casa\n";
                        }
                    }
                    else {
                        cout << "El jugador ha sacado un " << d << endl;
                        if (pos2 + d < 63) {
                            pos2 += d;
                        }
                        else if (pos2 + d > 63) {
                            cout << "Se ha pasado de la zanata\n";
                        }
                        else if (pos2 + d == 63) {
                            cout << "Ha ganado el jugador 2\n";
                            return 0;
                        }
                    }
                    if (letra(jug2) == 'R') {
                        posTab2 = pos2 + 5;
                    }
                    else if (letra(jug2) == 'M') {
                        posTab2 = pos2 + 22;
                    }
                    else if (letra(jug1) == 'V') {
                        posTab2 = pos2 + 39;
                    }
                    else if (letra(jug2) == 'A') {
                        posTab2 = pos2 + 56;
                    }
                    if (posTab1 == posTab2) {
                        if (casSegura(posTab1) == false) {
                            cout << "El jugador 2 ha comido al jugador 1\n";
                            pos2 += 20;
                            pos1 = -1;
                        }
                    }
                    genTablero();
                }
                else if (triple == 4) {
                    cout << "El jugador ha sacado 3 seis seguidos y se va a casa";
                    pos2 = -1;
                    d = 0;
                    genTablero();
                }
            } while (d == 6);



        }
    }

    return 0;
}
//FUNCIONES-------------------------------------------------------------------
string colorACadena(tColor color) {//FUNCION PARA DAR COLOR DEL JUGADOR
    string strColor;
    switch (color) {
    case rojo:
        strColor = "Rojo";
        break;
    case amarillo:
        strColor = "Amarillo";
        break;
    case verde:
        strColor = "Verde";
        break;
    case azul:
        strColor = "Azul";
        break;

    }
    return strColor;


}
char letra(tColor color) {//FUNCION PARA CARACTER DEL JUGADOR
    char letColor;
    switch (color) {
    case rojo:
        letColor = 'R';
        break;
    case amarillo:
        letColor = 'M';
        break;
    case verde:
        letColor = 'V';
        break;
    case azul:
        letColor = 'A';
        break;
    }
    return letColor;
}
bool casSegura(int pos) {//FUNCION PARA DETERMINAR SI LA CASILLA ES SEGURA
    bool casilla = false;
    if (pos % 17 == 0 || pos % 17 == 5 || pos % 17 == 12) {
        casilla = true;
    }
    else {
        casilla = false;
    }
    return casilla;

}
void carrilPrincipal() {//FUNCION PARA EL CARRIL PRINCIPAL DEL PARCHIS

    if (letra(jug1) == 'R') {
        posTab1 = pos1 + 5;
    }
    else if (letra(jug1) == 'M') {
        posTab1 = pos1 + 22;
    }
    else if (letra(jug1) == 'V') {
        posTab1 = pos1 + 39;
    }
    else if (letra(jug1) == 'A') {
        posTab1 = pos1 + 56;
    }


    if (letra(jug2) == 'R') {
        posTab2 = pos2 + 5;
    }
    else if (letra(jug2) == 'M') {
        posTab2 = pos2 + 22;
    }
    else if (letra(jug2) == 'V') {
        posTab2 = pos2 + 39;
    }
    else if (letra(jug2) == 'A') {
        posTab2 = pos2 + 56;
    }



    if (posTab1 >= 68) {
        posTab1 -= 68;
    }
    if (posTab2 >= 68) {
        posTab2 -= 68;
    }

    for (int x = 0; x < numCasillas; x++) {
        if (x == posTab1 && posTab1 == posTab2) {
            if (casSegura(posTab1) == true) {
                cout << "a";
            }
        }
        else if (x == posTab1) {
            if (pos1 != -1) {
                cout << letra(jug1);
            }
            else {
                cout << " ";
            }
        }
        else if (x == posTab2) {
            if (pos2 != -1) {
                cout << letra(jug2);
            }
            else {
                cout << " ";
            }
        }
        else {
            cout << " ";
        }
    }
}
void fichaCasa() {//FUNCION FICHA EN CASA
    int posInc1, posInc2, poss1, poss2;
    tColor jugg1, jugg2;

    if (jug1 < jug2) {
        jugg1 = jug1;
        poss1 = pos1;
        jugg2 = jug2;
        poss2 = pos2;
    }
    else {
        jugg1 = jug2;
        poss1 = pos2;
        jugg2 = jug1;
        poss2 = pos1;
    }
    if (letra(jugg1) == 'R') {
        posInc1 = 5;
    }
    else if (letra(jugg1) == 'M') {
        posInc1 = 22;
    }
    else if (letra(jugg1) == 'V') {
        posInc1 = 39;
    }
    else {
        posInc1 = 56;
    }
    for (int x = 0; x < posInc1; x++) {
        cout << " ";
    }
    if (poss1 == -1) {
        cout << letra(jugg1);
    }
    else {
        cout << " ";
    }
    if (letra(jugg2) == 'M') {
        posInc2 = 21 - posInc1;
    }
    else if (letra(jugg2) == 'V') {
        posInc2 = 38 - posInc1;
    }
    else {
        posInc2 = 55 - posInc1;
    }
    for (int x = 0; x < posInc2; x++) {
        cout << " ";
    }
    if (poss2 == -1) {
        cout << letra(jugg2);
    }
    else {
        cout << " ";
    }
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
void comer(tColor jug) {

    if (posTab1 == posTab2) {
        if (casSegura(posTab1) == false) {
            if (jug == jug1) {
                pos2 -= 1;
                pos1 += 20;
                cout << "\nEl jugador 1 ha comido a la ficha del jugador 2\n";
            }
            else if (jug == jug2) {
                pos1 -= 1;
                pos2 += 20;
            }
        }
    }

}
void genTablero() {//FUNCION PARA GENERAR TABLERO
    int pos = 0;
    cout << "\n\t";
    for (pos = 0; pos < numCasillas; pos++) {

        cout << pos / 10;

    }
    cout << "\n\t";
    for (pos = 0; pos < numCasillas; pos++) {

        cout << pos % 10;

    }
    cout << "\n\t";
    for (pos = 0; pos < numCasillas; pos++) {

        if (casSegura(pos) == true) {
            cout << 'o';
        }
        else {
            cout << '-';
        }
    }
    cout << "\nCALLE   ";
    carrilPrincipal();
    cout << "\n\t";//Camino de las fichas

    for (pos = 0; pos < numCasillas; pos++) {

        if (casSegura(pos) == true) {
            cout << 'o';
        }
        else {
            cout << '-';
        }
    }
    cout << "\nCASA    ";
    fichaCasa();
    cout << endl;
}
