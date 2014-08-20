// g++ p1-puenteSobreLavaCaliente.cpp -o p1
// ./p1 < cat puente1.txt  
#include <vector>
#include <assert.h>
#include <iostream>

using namespace std;

#define IMPOSIBLE -1 

vector<int> cruzarPuente(int puente[], int cantidadDeTablones, int largoSalto);
int calcularProximoTablon(int puente[], int cantidadDeTablones, int actual, int largoSalto);

int main(int argc, const char *argv[])
{
    int cantidadDeTablones, largoSalto;
    vector<int> saltos;
    while (true) {
        cin >> cantidadDeTablones;
        if (cantidadDeTablones == 0) return 0;
        cin >> largoSalto;
        assert(largoSalto>0);
        // puente[0]                             -> tierra, abajo del puente
        // puente[i] 1<= i <= cantidadDeTablones -> tablon_i del puente
        // puente[cantidadDeTablones]            -> tierra, del otro lado del puente
        int puente[cantidadDeTablones+2];
        for (int i = 1; i <= cantidadDeTablones; i++) {
            cin >> puente[i];
            assert(puente[i]==1 || puente[i]==0);
        }    

        saltos = cruzarPuente(puente, cantidadDeTablones, largoSalto);

        // cruzarPuente devuelve el vector saltos vacío si no puede
        // cruzarse con el largoSalto recibido 
        if (saltos.size() == 0) { 
            cout << "no" << endl;
        } else {
            int cantSaltos = saltos.size();
            cout << cantSaltos << " ";
            for (int i = 0; i < cantSaltos; i++) {
                cout << saltos[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}

vector<int> cruzarPuente(int puente[], int cantidadDeTablones, int largoSalto)
{
    int actual = 0, proximo = 0;
    vector<int> saltos;
    while (actual <= cantidadDeTablones) {
        proximo = calcularProximoTablon(puente, cantidadDeTablones, actual, largoSalto);

        if (proximo == IMPOSIBLE) return vector<int>();

        saltos.push_back(proximo);

        if (proximo > cantidadDeTablones) return saltos;

        actual = proximo;
    }
}

/* Dado un puente y un tablon devuelve cual es el salto más largo que se puede
 * realizar desde ese tablón. Si no puede realizarse ningún salto devuelve
 * IMPOSIBLE(-1)
 * */
int calcularProximoTablon(int puente[], int cantidadDeTablones, int actual, int largoSalto)
{
    while (largoSalto > 0) {
       if (actual + largoSalto > cantidadDeTablones) 
           return cantidadDeTablones+1;
       
       if (puente[actual+largoSalto] == 0)
           return actual+largoSalto;
           
       largoSalto--;
    }

    return IMPOSIBLE;
}

