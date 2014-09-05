#include <iostream>
#include <vector>
#include <set>

using namespace std;

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

int peligrosidades[1024][1024];

int main(int argc, const char *argv[])
{
    int n, umbralDePeligrosidad;
    int i = 1;
    while(true) {
        cin >> n;
        if (n == 0) return 0;
        cout << "Instancia " << i << endl;
        i++;
        cin >> umbralDePeligrosidad;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
               if (i == j) peligrosidades[i][i] = 0;
               if (i < j) cin >> peligrosidades[i][j];  
               if (i > j) peligrosidades[i][j] = peligrosidades[j][i];
            }
        }

        vector<Camion> camiones;
        camiones.push_back(Camion(0));
        vector<Camion> solucion;
        for (int i = 0; i < n; i++) {
           solucion.push_back(Camion(i)); 
        }
        bt(1, camiones, solucion, umbralDePeligrosidad, n);
        
        int elementosCamiones[n];
        set<int>::iterator it;
        for(int i = 0; i < solucion.size(); i++) {
            for (it = solucion[i].productos.begin(); it != solucion[i].productos.end(); it++) {
                elementosCamiones[*it] = i;
            }
        }

        cout << solucion.size() << " ";
        for (int i = 0; i < n; i++) {
            cout << elementosCamiones[i];
            if (i < (n-1)) cout << " ";
        }
        cout << endl;
        
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
            bt(producto+1, camiones, mejorTemp, umbral, n);
            sacarProducto(producto, camiones[j], peligrosidadPrevia);
        }
    }
    if (camiones.size() < (mejorTemp.size()-1)) {
        camiones.push_back(Camion(producto));
        bt(producto+1, camiones, mejorTemp, umbral, n);
        camiones.pop_back();
    }

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
