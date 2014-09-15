// Este programa va a crear una cantidad X de instancias aleatorias de N productos, para N = {1,...,algunValor} y las va a devolver por SALIDA ESTANDAR (consola). El umbral va a ser fijo. Vale que para toda peligrosidad, 0 <= peligrosidad <= UMBRAL + 1.
// Hay que usar ./randomGen > textFile para guardar a disco.
// g++ -O3 randomGen.cpp -o randomGen

#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;

const int CANT_INSTANCIAS = 5;
const int LIM_PRODUCTOS = 15;
const int UMBRAL = 100;

int main(int argc, const char* argv[]) {
    srand(time(NULL) + getpid()); // Seedeo
    for (int totalProductos = 2; totalProductos <= LIM_PRODUCTOS; totalProductos++) {
        for (int instancia = 1; instancia <= CANT_INSTANCIAS; instancia++) {
            cout << totalProductos << " " << UMBRAL << endl;
            for (int producto = 1; producto <= totalProductos - 1; producto++) {
                for (int peligrosidad = 1; peligrosidad <= totalProductos - producto; peligrosidad++) {
                    cout << rand() % (UMBRAL + 2) << " "; // Esto genera un entero random entre 0 y UMBRAL + 1.
                }
                cout << endl;
            }
        }
    }
    cout << "0" << endl;
}

