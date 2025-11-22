#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>
//comentario

using namespace std;


struct contacto {
    string Nombre;
    int telefono;
    string email;
};

struct NodoArbol {
    contacto dato;       // Almacena la misma estructura 'contacto'
    NodoArbol* izquierda; // Puntero al subárbol izquierdo
    NodoArbol* derecha;  // Puntero al subárbol derecho
};
NodoArbol* arbolcontacto = NULL;


//creamos el nodo
NodoArbol* crearNodoArbol(contacto c) {
    NodoArbol* nuevoNodo = new NodoArbol;
    nuevoNodo -> dato = c;
    nuevoNodo -> izquierda = NULL;
    nuevoNodo -> derecha = NULL;
    return nuevoNodo;
}
//funcion para insertar en el arbol
void insertarArbol(NodoArbol* &arbol, contacto c) {
    //si arbol esta vacio, el nuevo nodo se convierte en la raiz
    if (arbol == NULL) {
        arbol = crearNodoArbol(c);
    }
    //Si el nombre del nuevo contacto es menor, va a la izquierda.
    else if (c.Nombre < arbol -> dato.Nombre) {
        insertarArbol(arbol -> izquierda, c);
    }
    //Si el nombre del nuevo contacto es mayor, va a la derecha.
    else {
        insertarArbol(arbol -> derecha, c);
    }
}
void mostrarNodos(NodoArbol* &arbol) {
    if (arbol != NULL) {
        //Recorrer Subárbol Izquierdo
        mostrarNodos(arbol -> izquierda);
        //mostramos el arbol
        cout << "Nombre: " << arbol -> dato.Nombre
        << ", telefono: " << arbol -> dato.telefono << endl;
        //recorremos el subarbol derecho
        mostrarNodos(arbol -> derecha);

    }
} //Holaaaaaa
void mostrarPreorden(NodoArbol* &arbol) {
    if (arbol != NULL) {
        //Mostramos la lista en preorden
        cout << "Nombre: " << arbol->dato.Nombre
             << " | Telefono: " << arbol->dato.telefono << endl;

        //Recorrer Subárbol Izquierdo
        mostrarPreorden(arbol->izquierda);

        // Recorrer Subárbol Derecho
        mostrarPreorden(arbol->derecha);
    }
}

vector<contacto> contactos_pricipales;
string NuevoContacto;

//  eliminar un contacto del VECTOR
void eliminarContacto(vector<contacto>& contactos, const string& nombreBuscado) {
    bool eliminado = false;
    // Recorremos el vector usando un índice
    for (size_t i = 0; i < contactos.size(); ++i) {
        // Comparamos el nombre. Nota: Si el usuario ingresó el nombre completo,
        // este método solo funciona si el nombre es exacto.
        if (contactos[i].Nombre == nombreBuscado) {

            // Eliminamos el elemento usando un iterador (contactos.begin() + i)
            contactos.erase(contactos.begin() + i);  //.erase sirve para eliminar
            cout << "Contacto '" << nombreBuscado << "' eliminado con exito.\n";
            eliminado = true;
            //  Restamos 1 al índice.
            // Esto es necesario porque el bucle 'for' hará un ++i después,
            // asegurando que la posición actual se revise de nuevo (por si hay nombres repetidos)
            // o para no saltar el siguiente elemento.
            i--;
        }
    }

    if (!eliminado) {
        cout << "No se encontro el contacto '" << nombreBuscado << "' para eliminar.\n";
    }
}

stack <contacto> pila;
void mostrarHistorial(stack<contacto>& pilaOriginal) {
    if (pilaOriginal.empty()) {
        cout << "\nEl historial (pila) esta vacio.\n";
        return;
    }
    stack<contacto> pilaAux = pilaOriginal;

    int contador = 1;
    cout << "\n--- HISTORIAL DE CONTACTOS (Ultimo agregado, primero en salir) ---\n";

    //destruimos la pila aux para poder mostrar el contenido
    while (!pilaAux.empty()) {
        //tomamos el dato superior de la pila
        contacto c = pilaAux.top();

        cout << contador++ << ". Nombre: " << c.Nombre
             << " | Telefono: " << c.telefono
             << " | Email: " << c.email << endl;
        //eliminamos el elemento y destruimos la pila aux
        pilaAux.pop();

    }
    cout << "--- Fin del Historial ---" << endl;
}



queue<contacto> cola_Contactos_pendientes;
//funcion para poner en cola los contactos
void ColaContactosPendientes() {
        contacto nuevoContacto;

    cout << "Ingrese Datos del contacto en cola" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el nombre:\n";
    getline(cin, nuevoContacto.Nombre);   //getline para nombre con espacios



    cout << "Ingrese el numero de telefono:\n" << endl;
    cin >> nuevoContacto.telefono;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese egmail:" << endl;
    getline(cin, nuevoContacto.email);    //getline para datos con espacios

    //agreagmos el contacto a la cola
    cola_Contactos_pendientes.push(nuevoContacto);

    // y lo mostramos
    cout << "Contacto" " "<< nuevoContacto.Nombre
    <<" ""agregado a la cola correctamente";

}
//la funcion de transferir contacto al arreglo principal
void TransferirContacto() {
    // verificamos que la lista este vacia
    if (cola_Contactos_pendientes.empty()) {
        cout << "la lista esta vacia.." << endl;
        return;
    }
    int contador = 0;
    cout << "Iniciando transferencia de contactos" << endl;

    while (!cola_Contactos_pendientes.empty())  //repetimos mientras la cola no este vacia
    {
        contacto c = cola_Contactos_pendientes.front();   //se tendria el valor de el contacto del frente de la cola

        contactos_pricipales.push_back(c);   //agregamos el contacto al arreglo principal

        cola_Contactos_pendientes.pop();   //estamos eliminando el contacto de la cola

        contador++;   //el contador se incrementa en cada transferencia
    }
    cout << "Transferencia completada, se agrego" << contador
       << "al arreglo principal." << endl;
}

//funcion Buscar por nombre
void buscarSecuencialPorNombre(const vector<contacto>& contactos, const string& NombreBuscado) {
    bool encontrado = false;
    cout << "\n--- Resultado de Busqueda para \"" << NombreBuscado << "\" ---";

    //Recorremos todo el vector
    for (const contacto& c : contactos ) {
        if (c.Nombre == NombreBuscado) {
            cout << "Nombre encontrado:\n";
            cout << "Nombre: " << c.Nombre
                        << " | Teléfono: " << c.telefono
                        << " | Email: " << c.email << endl;
            encontrado = true;

        }
    }
    if (!encontrado) {
        cout << "No se encontro ningun contacto con ese nombre \"" << NombreBuscado << endl;
    }

}

void buscarbinariaTelefono(const vector<contacto>& contactos, const int telefonoBuscar) {
    int izquierda = 0;
    int derecha = contactos.size() -1;
    bool encontrado = false;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (contactos[medio].telefono == telefonoBuscar) {
            cout << "Contacto encontrado:  (Busqueda Binaria)\n";
            cout << "Telefono: " << contactos[medio].telefono
                         << " | Nombre: " << contactos[medio].Nombre
                         << " | Email: " << contactos[medio].email << endl;
            encontrado = true;
            break;
        }

        else if (contactos[medio].telefono < telefonoBuscar) {
        izquierda = medio + 1;
        }
        else {
            derecha = medio - 1;
        }


    }
    if (!encontrado) {
        cout << "No se encontro ningun contacto con ese numero de telefono\"" << telefonoBuscar << endl;

    }
}

// ordenamiento por insercion
void ordenarNumeroTelefonico(vector<contacto>& contactos) {
    int n = contactos.size();

    //  i va desde el segundo elemento (índice 1) hasta el final
    for (int i = 1; i < n; i++) {

        // El 'key' es la estructura completa a insertar
        contacto key_contacto = contactos[i];         //el valor a insertar en la parte ordenada
        int keytelefono = key_contacto.telefono;
        int j = i - 1;

        // Desplaza los elementos mayores hacia la derecha
        while (j >= 0 && contactos[j].telefono >  keytelefono) {
            contactos[j + 1] = contactos[j];            // Mueve la estructura completa
            j--;

        }
        // Inserta la estructura completa en su posición
        contactos[j + 1 ] = key_contacto;
    }


}
// ordenamiento burbuja
void ordenarPorNombre(vector<contacto>& contactos) {
    int n = contactos.size();
    bool intercambiado;   // aca hacemos una variable booleana

    for (int i = 0; i < n - 1; i++) {
        intercambiado = false;
        for (int j = 0; j < n - i - 1; j++) {

            // Comparamos solo el campo 'nombre'
            if (contactos[j].Nombre > contactos[j+1].Nombre) {
                // Intercambiamos la estructura completa
                swap(contactos[j], contactos[j+1]);
                intercambiado = true;
            }
        }
        if (intercambiado == false)
            break;
    }
}

int main() {
    int numeroTelefonico;
    string email;
    string nombre;
    string buscarContacto = NuevoContacto;
    string Contactoeliminacion;
    int opcion;
    int opcionOrdenamiento;
    int BusquedaOrdenada;
    do {
        cout << "1:Agregar contacto\n";
        cout << "2:Listar contactos\n";
        cout << "3:Buscar contacto\n";
        cout << "4:Eliminar contacto\n";
        cout << "5:Agregrar a cola\n";
        cout << "6:Transferir a el arreglo principal\n";
        cout << "7:Mostrar historial\n";
        cout << "8:Mostrar Arbol\n";
        cout << "9:Salir\n";
        cout << "Seleccione una opcion:\n";
        cin >> opcion;

        //limpiamos el buffer de entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opcion == 1) {
            cout << "Ingrese su nombre completo:\n" << endl;
            getline(cin, nombre);  //nombres con espacios
            cout << "Ingrese su Numero de telefono: " << endl;
            cin >> numeroTelefonico;
            //limpiamos despuesder de leer el numero de telefono
             cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ingrese su Email:" << endl;
            getline(cin, email);  //para email con espacios

            contacto nuevo_contacto;
            nuevo_contacto.Nombre = nombre;
            nuevo_contacto.telefono = numeroTelefonico;
            nuevo_contacto.email = email;
            cout << "Se agrego con exito el contacto" << endl;

            contactos_pricipales.push_back(nuevo_contacto);
            pila.push(nuevo_contacto); // agrega a la pila los datos ingresados
            insertarArbol(arbolcontacto, nuevo_contacto);  //agregar el arbol para que tenga los datos ingresas
        }

        else if (opcion == 2) {
            cout << "Opcion ordenamiento:\n"; // Agrego saltos de línea para mejor lectura
            cout << "1.Por Nombre\n";
            cout << "2.Por numero telefonico\n";
            cout << "Seleccione una opcion de ordenamiento: ";
            cin >> opcionOrdenamiento;

            if (opcionOrdenamiento == 1) {
                ordenarPorNombre(contactos_pricipales);

                cout << "La lista de contactos ordenada por nombre es:\n";
                // Usamos 'contacto' (o una referencia 'contacto&') para iterar
                for (const contacto& c : contactos_pricipales) {
                    cout << "Nombre: " << c.Nombre
                         << " | Teléfono: " << c.telefono
                         << " | Email: " << c.email << endl;

                }
            } //cerramos opcion 1

            else if (opcionOrdenamiento == 2) {
                ordenarNumeroTelefonico(contactos_pricipales);
                cout << "La lista de contactos por numero telefonico es:\n";
                // Usamos 'contacto' (o una referencia 'contacto&') para iterar
                for (const contacto& c : contactos_pricipales) {
                    cout << "Telefono: " << c.telefono
                         << " | Nombre: " << c.Nombre
                         << " | Email: " << c.email << endl;
                }
            }//cerramos opcion 2
        }
        else if (opcion == 3) {
            cout << "Busqueda Ordenada:\n"; // Agrego saltos de línea para mejor lectura
            cout << "1.Por Nombre\n";
            cout << "2.Por Telefono\n";
            cout << "Seleccione una opcion de busqueda: ";
            cin >> BusquedaOrdenada;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (BusquedaOrdenada == 1) {
                string NombreBus;
                cout << "Ingrese el nombre a buscar:\n";
                cin >> NombreBus;
                buscarSecuencialPorNombre(contactos_pricipales, NombreBus);
            }
            else if (BusquedaOrdenada == 2) {
                int NumeroBus;
                cout << "Ingrese el Numero que desea buscar:\n";
                cin >> NumeroBus;

                ordenarNumeroTelefonico(contactos_pricipales);
                buscarbinariaTelefono(contactos_pricipales, NumeroBus);
            }
        }//cerramos opcio 3
        else if (opcion == 4) {
            cout << "Ingrese el nombre que desea eliminar:" << endl;
            getline(cin, Contactoeliminacion);
            //Llamamos a la función de eliminación del contacto
            eliminarContacto(contactos_pricipales, Contactoeliminacion);
        }//cerramos opcion 4
        else if (opcion == 5) {
            ColaContactosPendientes();
            //Muestra el contacto que está al frente de la cola
            if (!cola_Contactos_pendientes.empty()) {
                cout <<" " "El contacto pendiente es:"
                << cola_Contactos_pendientes.front().Nombre << endl;
            }
        }//cerramos opcion 5
        else if (opcion == 6) {
            TransferirContacto();
        }
        else if (opcion == 7) {
            mostrarHistorial(pila);
        }
        else if (opcion == 8) {
            int opcionRecorrido;
            cout << "--Mostrar arbol de contactos--" << endl;
            if (arbolcontacto == NULL) {
                cout << "El arbol esta vacio, Agregue una contacto primero" << endl;
            }else {
                cout << "Seleccione el tipo de recorrido:\n";
                cout << "1. Inorden (Lista alfabetica)\n";
                cout << "2. Preorden (Muestra la estructura)\n";
                cout << "Opcion: ";
                cin >> opcionRecorrido;
            }
            if (opcionRecorrido == 1) {
                cout << "--Contactos en orden inorden--" << endl;
                mostrarNodos(arbolcontacto);
            }else if (opcionRecorrido == 2) {
                cout << "--Contactos en orden preorden--" << endl;
                mostrarPreorden(arbolcontacto);
            }else {
                cout << "Opcion de reccorido no valida" << endl;
            }
        }

        else if (opcion == 9) {
            cout << "Cerrando programa, Bye";
        }
    }while (opcion != 9);
}
