// g++ -std=c++0x prueba_time.cpp -o prueba_time
#include <set>
#include <vector>
#include <assert.h>
#include <iostream>
#include <chrono>
#include <math.h> 
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
    int contador = 1;
    int sumaTiempos = 0;
    int tiempoParcial = 0;
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
        for(int j = 0; j < 10; j++){
            auto start_time = chrono::high_resolution_clock::now();//TIEMPO
            // cada edificio va a tener un evento de empezar y uno de terminar
            vector<Evento> eventos = generarEventos(edificios);
            // los eventos son ordenados por su coordenada x de forma ascendente
            // desempata por el tipo de evento, EMPIEZA gana
            sort(eventos.begin(), eventos.end(), &comparar_eventos_por_x);

            vector<Punto> contorno = calcularContorno(eventos);
            auto end_time = chrono::high_resolution_clock::now();//TIEMPO
            tiempoParcial = tiempoParcial + chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count();//TIEMPO
        }
  		
        tiempoParcial = tiempoParcial / 10; //divido la corrida de la misma instancia
        int sumaTiempos = sumaTiempos + tiempoParcial;
  		if(contador == 10){
            sumaTiempos = sumaTiempos / 10;
            sumaTiempos = sumaTiempos / log(cantidadDeEdificios);
            cout << cantidadDeEdificios << " " << sumaTiempos / 10;
            cout << endl;
            contador=1;
            tiempoParcial = 0;
            sumaTiempos = 0;
        }
        contador++;

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
    if (a.x == b.x) {
        if (a.empieza() != b.empieza()) // distinto tipo => gana el de apertura
          return a.empieza();

        if (a.empieza()) { // son los dos de apertura
          return a.h > b.h;
        } else {           // son los dos de cierre
          return a.h < b.h;
        }
    }
    
    return a.x < b.x;
}
