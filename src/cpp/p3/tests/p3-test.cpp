// Dado un archivo de entrada con X instancias para cada Y cantidad de productos (Y <= 100), devuelvo por SALIDA ESTANDAR, en cada linea, lo siguiente:
// Y <espacio> promedio{ los minimo{ tiempos en ejecutar la instancia i-ésima para Y productos } de todas las instancias de Y productos}
// Es decir, cada instancia se ejecutará una cierta cantidad de veces y se tomará el mínimo para mejorar la precisión, y luego se promediaran estos valores para las instancias de cada cantidad de productos.
// g++ -std=c++0x p3-test.cpp -o p3-test
#include <climits>
#include <iostream>
#include <vector>
#include <set>
#include <chrono>

using namespace std;

const int MAX_CANTIDAD_PRODUCTOS = 100;
const int FOR_MINIMO = 2;
const bool PODA_AGREGAR_CAMION = true;
const bool PODA_RESTO_PRODUCTOS = true;

int peligrosidades[MAX_CANTIDAD_PRODUCTOS][MAX_CANTIDAD_PRODUCTOS];

struct Camion {
    Camion() : productos(set<int>()), peligrosidad(0) {};
    Camion(int producto) : peligrosidad(0) {
        productos = set<int>();
        productos.insert(producto);
    };

    set<int> productos;
    int peligrosidad;
};

void bt(int producto, vector<Camion> &camiones, vector<Camion> &mejorTemp, int umbral, int n);
bool agregarNoSuperaUmbral(int producto, const Camion &camion, int umbral);
void sacarProducto(int producto, Camion &camion, int peligrosidadPrevia);
int agregarProducto(int producto, Camion &camion);
void mostrarCamiones(const vector<Camion> &camiones);

int main(int argc, const char *argv[])
{   
    int sumaTiemposPorCantProductos[MAX_CANTIDAD_PRODUCTOS + 1] = { }; // Pongo cada tiempo en su casilla correspondiente, ie tiempo para i productos en suma[i]
    int cantidadInstanciasPorCantProductos[MAX_CANTIDAD_PRODUCTOS + 1] = { }; // Idem para la cantidad de instancias, esto lo uso para promediar
    int n, umbralDePeligrosidad;
    while(true) {
        cin >> n;
        if (n == 0) break;
        cin >> umbralDePeligrosidad;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
               if (i == j) peligrosidades[i][i] = 0;
               if (i < j) cin >> peligrosidades[i][j];  
               if (i > j) peligrosidades[i][j] = peligrosidades[j][i];
            }
        }
        
        chrono::microseconds minTiempo(INT_MAX);
        for (int i = 0; i < FOR_MINIMO; i++) {
            // Acá considero que arranca el algoritmo
            auto start_time = chrono::high_resolution_clock::now();
            vector<Camion> camiones;
            camiones.push_back(Camion(0));
            vector<Camion> solucion;
            for (int i = 0; i < n; i++) {
               solucion.push_back(Camion(i)); 
            }
            bt(1, camiones, solucion, umbralDePeligrosidad, n);
            // Acá terminó
            auto end_time = chrono::high_resolution_clock::now();
            chrono::microseconds temp = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
            if (temp < minTiempo)
                minTiempo = temp;
        }
        sumaTiemposPorCantProductos[n] += minTiempo.count();
        cantidadInstanciasPorCantProductos[n]++;
        //cout << n << " " << sumaTiemposPorCantProductos[n] << " " << cantidadInstanciasPorCantProductos[n] << endl;
    }
    
    for (int i = 2; i <= MAX_CANTIDAD_PRODUCTOS; i++) {
        int instancias = cantidadInstanciasPorCantProductos[i];
        //cout << instancias << endl;
        if (instancias == 0) {
            continue;
        } else {
            cout << i << " " << sumaTiemposPorCantProductos[i] / instancias << endl;
        }
    }
    return 0;
}

void bt(int producto, vector<Camion> &camiones, vector<Camion> &mejorTemp,
    int umbral, int n)
{
    if (producto == n && camiones.size() < mejorTemp.size()) {
        mejorTemp = camiones;
        return;
    }
    if (producto == n) return;
    for (int j = 0; j < camiones.size(); j++) {
        if (agregarNoSuperaUmbral(producto, camiones[j], umbral)) {
            int peligrosidadPrevia = agregarProducto(producto, camiones[j]);
            if (PODA_RESTO_PRODUCTOS) { /////////////////////////////////////////////////// PODA DE RESTO DE LOS PRODUCTOS
                if (camiones.size() == mejorTemp.size() - 1) {
                    //cout << "PODA PRODUCTOS" << endl;
                    for (int i = producto + 1; i < n; i++) {
                        bool entraEnAlguno = false;
                        for (int c = 0; c < camiones.size(); c++) {
                            if (agregarNoSuperaUmbral(i, camiones[c], umbral)) {
                                entraEnAlguno = true;
                                break;
                            }
                        }
                        if (!entraEnAlguno) {
                            sacarProducto(producto, camiones[j], peligrosidadPrevia);
                            continue;
                        }
                    }
                }
            }
            bt(producto + 1, camiones, mejorTemp, umbral, n);
            sacarProducto(producto, camiones[j], peligrosidadPrevia);
        }
    }
    if (PODA_AGREGAR_CAMION) { //////////////////////////////////////////////////////////// PODA DE AGREGAR CAMION
        if (camiones.size() == mejorTemp.size() - 1) {
            //cout << "PODA CAMIONES" << endl;
            return;
        }
    }
    camiones.push_back(Camion(producto));
    bt(producto+1, camiones, mejorTemp, umbral, n);
    camiones.pop_back();

    return;
}

bool agregarNoSuperaUmbral(int producto, const Camion &camion, int umbral)
{
    int acumPeligrosidad = camion.peligrosidad;
    set<int>::iterator it;
    for (it = camion.productos.begin(); it != camion.productos.end(); it++) {
        acumPeligrosidad += peligrosidades[producto][*it];
        if (acumPeligrosidad > umbral) return false;
    }
    
    return true;
}

void sacarProducto(int producto, Camion &camion, int peligrosidadPrevia)
{
    camion.productos.erase(producto);
    camion.peligrosidad = peligrosidadPrevia;
}

int agregarProducto(int producto, Camion &camion)
{
    int peligrosidadPrevia = camion.peligrosidad;
    set<int>::iterator it;
    for (it = camion.productos.begin(); it != camion.productos.end(); it++) {
        camion.peligrosidad += peligrosidades[producto][*it];
    }
    camion.productos.insert(producto);
    
    return peligrosidadPrevia;
}

// Imprime el contenido de los camiones y la peligrosidad total del mismo
// El formato es: 
//      Camion i: p0 p1 ... pn (peligrosidad)
void mostrarCamiones(const vector<Camion> &camiones)
{
    cout << "Combinación nueva" << endl;
    for (int i = 0; i < camiones.size(); i++) {
        cout << "CAMION " << i << ": ";
        set<int>::iterator it;
        for (it = camiones[i].productos.begin(); it != camiones[i].productos.end(); it++) {
            cout << *it << " ";
        }
        cout << "(" << camiones[i].peligrosidad << ")";
        cout << endl << endl;
    }
}
