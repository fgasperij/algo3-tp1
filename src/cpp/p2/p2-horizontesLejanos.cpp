// g++ p2-horizontesLejanos.cpp -o p2
// ./p2 < horizontes1.txt
#include <iostream>
#include <assert.h>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

struct Edificio {
    int left;
    int right;
    int h;
};

enum tipos_de_eventos {EMPIEZA, TERMINA};
struct Evento {
   Evento() : edificio(0) {};
   Evento(tipos_de_eventos t, int x, int h, int edificio) : tipo(t), x(x), h(h), edificio(edificio) {};

   bool empieza() const { return tipo == EMPIEZA; };

   int edificio;
   tipos_de_eventos tipo;
   int x;
   int h;
};

struct Punto {
    Punto(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

vector<Punto> calcularContorno(const vector<Evento> &eventos);
vector<Evento> generarEventos(const vector<Edificio> &edificios);
bool comparar_eventos_por_x(const Evento &a, const Evento &b);

int main(int argc, const char *argv[])
{
    int cantidadDeEdificios;
    while(true) {
        cin >> cantidadDeEdificios;
        if (cantidadDeEdificios == 0) return 0;

        vector<Edificio> edificios(cantidadDeEdificios);
        for (int i = 0; i < cantidadDeEdificios; i++) {
            edificios[i] = Edificio();
            cin >> edificios[i].left >> edificios[i].h >> edificios[i].right;

            assert(edificios[i].left >= 0);
            assert(edificios[i].h >= 0);
            assert(edificios[i].right >= 0);
            assert(edificios[i].left < edificios[i].right);
        }

        // cada edificio va a tener un evento de empezar y uno de terminar
        vector<Evento> eventos = generarEventos(edificios);
        // los eventos son ordenados por su coordenada x de forma ascendente
        // desempata por el tipo de evento, EMPIEZA gana
        sort(eventos.begin(), eventos.end(), &comparar_eventos_por_x);

        vector<Punto> contorno = calcularContorno(eventos);

        for (int i = 0; i < contorno.size(); i++) {
            cout << contorno[i].x << " " << contorno[i].y;
            if (i < (contorno.size()-1)) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

vector<Punto> calcularContorno(const vector<Evento> &eventos)
{
    // alturas de edificios abiertos
    multiset<int> abiertos;
    multiset<int>::iterator itAbiertos;
    Evento eventoActual;
    int alturaContornoActual = 0;
    vector<Punto> contorno;

    for (int i = 0; i < eventos.size(); i++) {
        eventoActual = eventos[i];
        if (eventoActual.empieza()) {
            abiertos.insert(eventoActual.h);
            if (eventoActual.h > alturaContornoActual) {
                contorno.push_back(Punto(eventoActual.x, eventoActual.h));
                alturaContornoActual = eventoActual.h;
            }
        } else {
            // lo busco primero porque sólo quiero eliminar una aparición
            // y puede que haya más de un edificio abierto con la misma
            // altura
            itAbiertos = abiertos.find(eventoActual.h); 
            abiertos.erase(itAbiertos);
            if (eventoActual.h == alturaContornoActual) {
                int tempAltura = alturaContornoActual;
                alturaContornoActual = (abiertos.empty() ? 0 : *abiertos.rbegin());
                if (tempAltura != alturaContornoActual)
                    contorno.push_back(Punto(eventoActual.x, alturaContornoActual));
            }
        }
    }
    
    return contorno; 
} 

vector<Evento> generarEventos(const vector<Edificio> &edificios)
{
    int cantidadDeEdificios = edificios.size();
    vector<Evento> eventos(cantidadDeEdificios*2);
    for (int i = 0; i < cantidadDeEdificios; i++) {
        eventos[i*2] = Evento (EMPIEZA, edificios[i].left, edificios[i].h, i);
        eventos[i*2+1] = Evento (TERMINA, edificios[i].right, edificios[i].h, i);
    }
    
    return eventos;
}

bool comparar_eventos_por_x(const Evento &a, const Evento &b)
{
    // si tienen el mismo x desempata el tipo
    // los que empiezan tienen prioridad para ya tenerlos en el set
    // de abiertos
    if (a.x == b.x)
        return (a.empieza() ? true : false);
    
    return a.x < b.x;
}
