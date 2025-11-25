#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <limits>
#include <tuple>

using namespace std;


struct contacto {
    string Nombre;
    int telefono;
    string email;
};

struct NodoArbol {
    contacto dato; // Almacena la misma estructura 'contacto'
    NodoArbol* izquierda; // Puntero al subárbol izquierdo
    NodoArbol* derecha; // Puntero al subárbol derecho
};


// Vector principal para almacenar contactos
vector<contacto> contactos_pricipales;
// Árbol de Búsqueda Binaria para contactos
NodoArbol* arbolcontacto = NULL;
// Pila para historial de contactos 
stack <contacto> pila;
// Cola para contactos pendientes 
queue<contacto> cola_Contactos_pendientes;



NodoArbol* crearNodoArbol(contacto c) {
    NodoArbol* nuevoNodo = new NodoArbol;
    nuevoNodo->dato = c;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

void insertarArbol(NodoArbol*& arbol, contacto c) {
    if (arbol == NULL) {
        arbol = crearNodoArbol(c);
    }
    // Comparación basada en el campo 'Nombre' para ABB
    else if (c.Nombre < arbol->dato.Nombre) {
        insertarArbol(arbol->izquierda, c);
    }
    // Si el nombre es mayor o igual, va a la derecha.
    else {
        insertarArbol(arbol->derecha, c);
    }
}

// Recorrido Inorden 
void mostrarNodos(NodoArbol* arbol) {

    if (arbol != NULL) {
        mostrarNodos(arbol->izquierda);
        cout << "Nombre: " << arbol->dato.Nombre
            << ", Telefono: " << arbol->dato.telefono << ", Email: " << arbol->dato.email << endl;
        mostrarNodos(arbol->derecha);
    }
}

// Recorrido Preorden (Muestra primero el nodo raíz)
void mostrarPreorden(NodoArbol* arbol) {
    //Mostramos la lista en preorden
    if (arbol != NULL) {
        cout << "Nombre: " << arbol->dato.Nombre
            << "  Telefono: " << arbol->dato.telefono << endl;
        mostrarPreorden(arbol->izquierda);//Recorrer Subárbol Izquierdo
        mostrarPreorden(arbol->derecha);        // Recorrer Subárbol Derecho
    }
}


//  eliminar un contacto del VECTOR
void eliminarContacto(vector<contacto>& contactos, const string& nombreBuscado) {
    bool eliminado = false;
    // Recorremos el vector usando un índice
    for (size_t i = 0; i < contactos.size(); ) {
        // Comparamos el nombre. Nota: Si el usuario ingresó el nombre completo,
 // este método solo funciona si el nombre es exacto.
        if (contactos[i].Nombre == nombreBuscado) {
            contactos.erase(contactos.begin() + i);
            cout << "Contacto '" << nombreBuscado << "' eliminado con exito.\n";
            eliminado = true;
            // No se incrementa 'i' porque el siguiente elemento ahora está en la posición 'i'
        }
        else {
            i++; // Solo incrementa si no se elimina
        }
    }

    if (!eliminado) {
        cout << "No se encontro el contacto '" << nombreBuscado << "' para eliminar.\n";
    }
}




void mostrarHistorial(stack<contacto> pilaOriginal) {
    if (pilaOriginal.empty()) {
        cout << "\nEl historial  esta vacio.\n";
        return;
    }


    int contador = 1;
    cout << "\n--- HISTORIAL DE CONTACTOS  ---\n";
    //destruimos la pila aux para poder mostrar el contenido
    while (!pilaOriginal.empty()) {
        //tomamos el dato superior de la pila
        contacto c = pilaOriginal.top();

        cout << contador++ << ". Nombre: " << c.Nombre
            << " | Telefono: " << c.telefono
            << " | Email: " << c.email << endl;

        pilaOriginal.pop();
    }
    cout << "--- Fin del Historial ---" << endl;
}


//funcion para poner en cola los contactos
void ColaContactosPendientes() {
    contacto nuevoContacto;

    cout << "\n--- Ingrese Datos del contacto en cola ---\n";
    // Limpiar el buffer antes de leer cadenas con espacios
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese el nombre:\n";
    getline(cin, nuevoContacto.Nombre);

    // Bucle para manejar errores de entrada si el usuario ingresa algo que no es un entero
    do {
        cout << "Ingrese el numero de telefono:\n";
        if (!(cin >> nuevoContacto.telefono)) {
            cout << "Error: Por favor, ingrese un numero de telefono valido.\n";
            cin.clear(); // Limpiar la bandera de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            nuevoContacto.telefono = -1; // Valor centinela para repetir el bucle
        }
    } while (nuevoContacto.telefono == -1);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese email:\n"; // Corregido: 'egmail' a 'email'
    getline(cin, nuevoContacto.email);

    cola_Contactos_pendientes.push(nuevoContacto);

    cout << "\nContacto " << nuevoContacto.Nombre
        << " agregado a la cola correctamente.\n";
}
//la funcion de transferir contacto al arreglo principal
void TransferirContacto() {
    // verificamos que la lista este vacia
    if (cola_Contactos_pendientes.empty()) {
        cout << "La cola de contactos pendientes esta vacia." << endl;
        return;
    }
    int contador = 0;
    cout << "Iniciando transferencia de contactos..." << endl;

    while (!cola_Contactos_pendientes.empty())
    {
        contacto c = cola_Contactos_pendientes.front();

        contactos_pricipales.push_back(c);
        pila.push(c); // Agregamos a la pila (historial) al transferir
        insertarArbol(arbolcontacto, c); // Agregamos al árbol al transferir

        cola_Contactos_pendientes.pop();
        contador++;
    }
    cout << "Transferencia completada. Se agregaron " << contador
        << " contactos al arreglo principal, historial y arbol." << endl;
}

// --- FUNCIONES DE BÚSQUEDA ---

void buscarSecuencialPorNombre(const vector<contacto>& contactos, const string& NombreBuscado) {
    bool encontrado = false;
    cout << "\n--- Resultado de Busqueda para \"" << NombreBuscado << "\" ---\n";

    for (const contacto& c : contactos) {

        // para buscar coincidencias parciales si lo deseas, 
        // pero se mantiene la comparación exacta original.
        if (c.Nombre == NombreBuscado) {
            cout << "Nombre: " << c.Nombre
                << " | Teléfono: " << c.telefono
                << " | Email: " << c.email << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontro ningun contacto con el nombre \"" << NombreBuscado << endl;
    }
}

void buscarbinariaTelefono(const vector<contacto>& contactos, const int telefonoBuscar) {
    int izquierda = 0;
    int derecha = contactos.size() - 1;
    bool encontrado = false;

    // Nota: La búsqueda binaria SOLO funcionará correctamente si 
    // el vector 'contactos' ya está **ordenado por el campo 'telefono'**.
    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (contactos[medio].telefono == telefonoBuscar) {
            cout << "Contacto encontrado: \n";
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
        cout << "No se encontro ningun contacto con el numero de telefono " << telefonoBuscar << endl;
    }
}

// FUNCIONES DE ORDENAMIENTO 


// Ordenamiento por Inserción 
void ordenarNumeroTelefonico(vector<contacto>& contactos) {
    int n = contactos.size();
    //  i va desde el segundo elemento (índice 1) hasta el final
    for (int i = 1; i < n; i++) {

        // El 'key' es la estructura completa a insertar
        contacto key_contacto = contactos[i]; //el valor a insertar en la parte ordenada
        int keytelefono = key_contacto.telefono;
        int j = i - 1;
        // Desplaza los elementos mayores hacia la derecha
        while (j >= 0 && contactos[j].telefono > keytelefono) {
            contactos[j + 1] = contactos[j]; // Mueve la estructura completa
            j--;
        }
        contactos[j + 1] = key_contacto; // Inserta la estructura completa en su posición
    }
    cout << "Contactos ordenados por número telefónico.\n";
}

// Ordenamiento Burbuja 
void ordenarPorNombre(vector<contacto>& contactos) {
    int n = contactos.size();
    bool intercambiado;

    for (int i = 0; i < n - 1; i++) {
        intercambiado = false;
        for (int j = 0; j < n - i - 1; j++) {
            // Comparamos solo el campo 'nombre'
            if (contactos[j].Nombre > contactos[j + 1].Nombre) {
                // Intercambiamos la estructura completa
                swap(contactos[j], contactos[j + 1]);
                intercambiado = true;
            }
        }
        if (intercambiado == false)
            break;
    }
    cout << "Contactos ordenados por nombre .\n";
}

// --- FUNCIÓN PRINCIPAL ---

void agregarContacto() {
    contacto nuevo_contacto;
    int numeroTelefonico;
    string nombre, email;

    cout << "\n--- Agregar Nuevo Contacto ---\n";
    // Limpiamos el buffer antes de leer el nombre que puede contener espacios
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Ingrese su nombre completo:\n";
    getline(cin, nombre);

    // Bucle para manejar errores de entrada para el número
    do {
        cout << "Ingrese su Numero de telefono: \n";
        if (!(cin >> numeroTelefonico)) {
            cout << "Error: Por favor, ingrese un numero de telefono valido.\n";
            cin.clear(); // Limpiar la bandera de error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar la entrada incorrecta
            numeroTelefonico = -1; // Valor centinela
        }
    } while (numeroTelefonico == -1);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese su Email:" << endl;
    getline(cin, email);

    nuevo_contacto.Nombre = nombre;
    nuevo_contacto.telefono = numeroTelefonico;
    nuevo_contacto.email = email;

    contactos_pricipales.push_back(nuevo_contacto);
    pila.push(nuevo_contacto);
    insertarArbol(arbolcontacto, nuevo_contacto);

    cout << "\n Contacto " << nombre << " agregado con éxito al vector, pila y árbol." << endl;
}

void listarContactos() {
    if (contactos_pricipales.empty()) {
        cout << "\nEl vector de contactos principal está vacío.\n";
        return;
    }

    int opcionOrdenamiento;
    cout << "\n--- Listar Contactos ---\n";
    cout << "1. Por Nombre \n";
    cout << "2. Por Numero Telefonico \n";
    cout << "Seleccione una opcion de ordenamiento: ";

    // Bucle para manejar la entrada de la opción de ordenamiento
    while (!(cin >> opcionOrdenamiento) || (opcionOrdenamiento != 1 && opcionOrdenamiento != 2)) {
        cout << "Opcion no valida. Seleccione 1 o 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (opcionOrdenamiento == 1) {
        ordenarPorNombre(contactos_pricipales);
        cout << "\n--- Lista de Contactos Ordenada por Nombre ---\n";
        for (const contacto& c : contactos_pricipales) {
            cout << "Nombre: " << c.Nombre
                << " | Telefono: " << c.telefono
                << " | Email: " << c.email << endl;
        }
    }
    else if (opcionOrdenamiento == 2) {
        ordenarNumeroTelefonico(contactos_pricipales);
        cout << "\n--- Lista de Contactos Ordenada por Numero Telefonico ---\n";
        for (const contacto& c : contactos_pricipales) {
            cout << "Telefono: " << c.telefono
                << " | Nombre: " << c.Nombre
                << " | Email: " << c.email << endl;
        }
    }
    cout << "------------------------------------------\n";
}

void buscarContacto() {
    if (contactos_pricipales.empty()) {
        cout << "\nEl vector de contactos principal está vacío. No hay nada que buscar.\n";
        return;
    }

    int BusquedaOrdenada;
    cout << "\n--- Busqueda de Contacto ---\n";
    cout << "1. Por Nombre \n";
    cout << "2. Por Telefono \n";
    cout << "Seleccione una opcion de busqueda: ";

    // Bucle para manejar la entrada de la opción de búsqueda
    while (!(cin >> BusquedaOrdenada) || (BusquedaOrdenada != 1 && BusquedaOrdenada != 2)) {
        cout << "Opcion no valida. Seleccione 1 o 2: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar buffer para getline

    if (BusquedaOrdenada == 1) {
        string NombreBus;
        cout << "Ingrese el nombre a buscar:\n";
        getline(cin, NombreBus);
        buscarSecuencialPorNombre(contactos_pricipales, NombreBus);
    }
    else if (BusquedaOrdenada == 2) {
        int NumeroBus;
        cout << "Ingrese el Numero que desea buscar:\n";

        // Bucle para manejar la entrada del número
        while (!(cin >> NumeroBus)) {
            cout << "Error: Por favor, ingrese un numero de telefono valido: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Se ordena por teléfono antes de la búsqueda binaria
        ordenarNumeroTelefonico(contactos_pricipales);
        buscarbinariaTelefono(contactos_pricipales, NumeroBus);
    }
}

void eliminarMenu() {
    if (contactos_pricipales.empty()) {
        cout << "\nEl vector de contactos principal está vacío. No hay nada que eliminar.\n";
        return;
    }
    string Contactoeliminacion;
    cout << "\n--- Eliminar Contacto ---\n";
    cout << "Ingrese el nombre completo del contacto que desea eliminar:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, Contactoeliminacion);
    eliminarContacto(contactos_pricipales, Contactoeliminacion);
}
int main() {
    int opcion;

    do {
        // Limpiamos la pantalla (solo si el sistema lo soporta)
        // system("cls");
    
        cout << "\n\n--- MENU PRINCIPAL DE GESTION DE CONTACTOS ---\n";
        cout << "1: Agregar contacto \n";
        cout << "2: Listar contactos \n";
        cout << "3: Buscar contacto \n";
        cout << "4: Eliminar contacto \n";
        cout << "5: Agregar a Cola \n";
        cout << "6: Transferir de Cola a Principal \n";
        cout << "7: Mostrar Historial \n";
        cout << "8: Mostrar Arbol de Contactos \n";
        cout << "9: Salir\n";
        cout << "Seleccione una opcion: ";

        // Manejo de errores de entrada para la opción del menú
        if (!(cin >> opcion)) {
            cout << "\n Opcion Invalida. Por favor, ingrese un numero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = 0; // Para repetir el bucle
            continue;
        }

        //system("cls"); // Opcional, para limpiar la pantalla después de la selección

        switch (opcion) {
        case 1:
            agregarContacto();
            break;
        case 2:
            listarContactos();
            break;
        case 3:
            buscarContacto();
            break;
        case 4:
            eliminarMenu();
            break;
        case 5:
            ColaContactosPendientes();
            if (!cola_Contactos_pendientes.empty()) {
                cout << "El contacto pendiente al frente es: "
                    << cola_Contactos_pendientes.front().Nombre << endl;
            }
            break;
        case 6:
            TransferirContacto();
            break;
        case 7:
            mostrarHistorial(pila);
            break;
        case 8: {
            int opcionRecorrido;
            cout << "\n-- Mostrar Arbol de Contactos --\n";
            if (arbolcontacto == NULL) {
                cout << "El arbol esta vacio. Agregue un contacto primero.\n";
            }
            else {
                cout << "1. Inorden \n";
                cout << "2. Preorden \n";
                cout << "Opcion: ";
                if (cin >> opcionRecorrido) {
                    if (opcionRecorrido == 1) {
                        cout << "\n--- Contactos en orden Inorden ---\n";
                        mostrarNodos(arbolcontacto);
                    }
                    else if (opcionRecorrido == 2) {
                        cout << "\n--- Contactos en orden Preorden ---\n";
                        mostrarPreorden(arbolcontacto);
                    }
                    else {
                        cout << "Opcion de recorrido no valida.\n";
                    }
                }
                else {
                    cout << " Entrada invalida.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            break;
        }
        case 9:
            cout << "\nCerrando programa. ¡Hasta luego! \n";
            break;
        default:
            cout << "\n Opcion Invalida. Por favor, intente de nuevo.\n";
        }

        if (opcion != 9) {
            cout << "\nPresione ENTER para continuar...";
            // Aseguramos que el buffer esté limpio para cin.get()
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (opcion != 9);

    return 0;
}
