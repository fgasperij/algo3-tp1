// Problema 3 - Biohazard

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct Producto {
    unsigned int id;                // ID del producto
    vector<int> peligrosidades;     // Peligrosidad con todos los productos con mayor ID que this
    int camion;                     // En qué camión está (-1 = ninguno)
    
    Producto(int id, vector<int> peligrosidades) : id(id), peligrosidades(peligrosidades), camion(-1) {
    }
    //Producto(const Producto& otro) : id(otro.id), peligrosidades(otro.peligrosidades), camion(0) {
    //}
    
    // Este método devuelve la peligrosidad con otro producto con mayor id que this.
    int peligrosidadCon(const Producto &otroProducto) {
        assert(otroProducto.id > id);
        return peligrosidades[otroProducto.id - id - 1];
    }
    
    void printProducto() {
        cout << "ID del producto: " << id << endl;
        for (unsigned int i = 0; i < peligrosidades.size(); i++) {
            cout << "Peligrosidad con el producto " << id + i + 1 << ": " << peligrosidades[i] << endl;
        }
        cout << "Camion en el que se encuentra: "; if(camion == -1) cout << "ninguno"; else cout << camion; cout << endl;
    }
};

int biohazardCamion(int camion, vector<Producto> &productos) {
    int res = 0;
    for (unsigned int i = 0; i < productos.size(); i++) {
        if (productos[i].camion == camion) {
            for (unsigned int j = i + 1; j < productos.size(); j++) {
                if (productos[j].camion == camion) {
                    res += productos[i].peligrosidadCon(productos[j]);
                }
            }
        }
    }
    return res;
}

void meterProductoPorIdEnCamion(unsigned int id, int camion, vector<Producto> &productos, 
                                    int &cantidadCamiones, int maximaPeligrosidad, bool &termine) {
    //cout << cantidadCamiones << " ";
    //for (vector<Producto>::iterator it = productos.begin(); it != productos.end(); it++) {
        //cout << it->camion << " ";
    //}
    //cout << endl;
    if (termine) {
        return;
    }
    productos[id].camion = camion;
    
    //cout << "Intento poner el producto " << id << " en el camion " << camion << endl;
    // Si meter el producto sobrepasa la peligrosidad permitida, lo saco.
    if (biohazardCamion(camion, productos) > maximaPeligrosidad) {
        productos[id].camion = -1;
        return;
    } else { // Si no, sigo intentando con los demás
        if (id == productos.size() - 1) {
            termine = true;
            return;
        }
        for (int k = 0; k < cantidadCamiones; k++) {
            for ( unsigned int i = id + 1; i < productos.size(); i++) {
                productos[i].camion = -1;
            }
            meterProductoPorIdEnCamion(id + 1, k, productos, cantidadCamiones, maximaPeligrosidad, termine);
            if (termine) break;
        }
    }
}

int main(int argc, char* argv[]) {
    while (true) {
        vector<Producto> productos;
        int cantidadProductos = 0;
        int maximaPeligrosidad = 0;
        int cantidadCamiones = 0;
        bool termine = false;
        
        cin >> cantidadProductos;
        if (cantidadProductos == 0) break;
        cin >> maximaPeligrosidad;
        
        for (int i = 0; i < cantidadProductos; i++) {
            int idProducto = i;
            vector<int> peligrosidades;
            for (int j = 0; j < cantidadProductos - idProducto - 1; j++) {
                int tempP;
                cin >> tempP;
                peligrosidades.push_back(tempP);
            }
            productos.push_back(Producto(idProducto, peligrosidades));
        }
        
        //for ( unsigned int i = 0; i < productos.size(); i++) {
            //productos[i].printProducto();
        //}
        
        // Trato de meter los productos en los camiones
        // La idea es poner productos en un camión hasta que no pueda seguir, luego se intenta con el próximo camión y así hasta
        // que no queden camiones. La cantidad de camiones es fija, si quedan productos sin poner, tengo que agregar un camion y
        // empezar de nuevo.
        while ( !termine && cantidadCamiones <= cantidadProductos) {
            cantidadCamiones++;
            //cout << "Intentando con " << cantidadCamiones << " camiones . . ." << endl;
            for ( unsigned int i = 0; i < productos.size(); i++) {
                productos[i].camion = -1;
            }
            //for ( unsigned int i = 0; i < productos.size(); i++) {
                //cout << productos[i].camion << " ";
            //}
            //cout << endl;
            meterProductoPorIdEnCamion(0, 0, productos, cantidadCamiones, maximaPeligrosidad, termine);
        }

        cout << cantidadCamiones << " ";
        for (vector<Producto>::iterator it = productos.begin(); it != productos.end(); it++) {
            cout << it->camion << " ";
        }
        cout << endl;
    }
    
    return 0;
}
