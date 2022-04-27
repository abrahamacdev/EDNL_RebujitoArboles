#ifndef ARBOLBINARIO_ARBOLBINARIO_H
#define ARBOLBINARIO_ARBOLBINARIO_H

#include <iostream>
#include "cassert"
#include "algorithm"
using namespace std;

template <typename T>
class ArbolBinario {

    struct celda;

    public:
    typedef celda* nodo;            // Un nodo es un puntero a una celda
    static const nodo NODO_NULO;

    // Constructores
    ArbolBinario();                 // Cto

    // Operaciones de insercción
    void insertarRaiz(const T& e);
    void insertarHijo(const T& e);

    // Operaciones de consulta
    const T& elemento(nodo n) const;
    T& elemento(nodo n);
    bool arbolVacio();
    bool arbolVacio() const;
    nodo raiz() const;
    nodo nodo(const T& e) const;

    // Operaciones de eliminación
    void eliminarNodo(nodo n);
    void eliminarRaiz();

    // TODO Operaciones nuevas
    int profundidad(nodo n) const;
    int altura(nodo n) const;

    // Operadores
    ArbolBinario<T>& operator =(const ArbolBinario<T>& a);

    ~ArbolBinario();

    private:

        struct celda{
            T e;
            nodo padre, hijoIzq, hijoDer;
            celda(const T& ele, nodo p = NODO_NULO): e(ele), padre(p), hijoIzq(NODO_NULO), hijoDer(NODO_NULO) {}
        };

        nodo r;

        // Métodos auxiliares
        nodo copiar(nodo n);
        void destruirNodos(nodo& n);
        int calcularAltura(nodo n) const;
        void insertarHijo(nodo n, const T& e);
        T borrarMin(nodo n, bool esIzdo);
};

// Definimos el valor de la constante NODO_NULO
// (Es necesario el "typename Ar..." inicial porque es un tipo que hemos definido dentro de la clase)
template <typename T>
const typename ArbolBinario<T>::nodo ArbolBinario<T>::NODO_NULO(nullptr);

// TODO  --- Constructores ---
template <typename T>
inline ArbolBinario<T>::ArbolBinario(): r(NODO_NULO) {}
// -------------

// TODO  --- Operaciones de insercción ---
template <typename T>
inline void ArbolBinario<T>::insertarRaiz(const T& e){
    assert(r == NODO_NULO); // Árbol vacío
    r = new celda(e);
}

template <typename T>
void ArbolBinario<T>::insertarHijo(const T& e){
    assert(r != NODO_NULO);
    insertarHijo(r, e);
};

template <typename T>
void ArbolBinario<T>::insertarHijo(nodo n, const T& e){

    // e es mayor, seguimos buscando hacia abajo
    if (e > n->e){

        if (n->hijoIzq == NODO_NULO){
            n->hijoIzq = new nodo(e, n);
        }
        else if (n->hijoDer == NODO_NULO){
            n->hijoDer = new nodo(e, n);
        }

        // Logramos un cierto equilibrado
        else {

            // El hijoIzdo es < que el derecho => insertaremos en el hijo derecho
            if (n->hijoIzq->e < n->hijoDer->e){
                insertarHijo(n->hijoDer, e);
            }

            // Insertaremos en el hijo izdo
            else {
                insertarHijo(n->hijoIzq, e);
            }
        }
    }

    // e es menor, insertamos donde n
    else {

        nodo nuevo = new nodo(e, n->padre);     // Creamos el nodo nuevo que tiene como padre, el padre del nodo n
        n->padre = nuevo;                       // Actualizamos el padre de n;
        nuevo->hijoIzq = n;                     // El nodo n será ahora hijo izquierdo del nuevo nodo

        // Actualizamos la raíz
        if (n == r){
            r = n;
        }
    }
}

// -------------

// TODO  --- Operaciones de eliminación ---
template <typename T>
void ArbolBinario<T>::eliminarRaiz() {

    // árbol no vacío y raíz no puede tener hijos
    assert(!arbolVacio());
    assert(r->hijoIzq == NODO_NULO && r->hijoDer == NODO_NULO);

    delete r;
    r = NODO_NULO;
}

template <typename T>
void ArbolBinario<T>::eliminarNodo(nodo n) {

    assert(n != NODO_NULO);

    // n es raíz
    if (n == r){
        delete r;
        r = nullptr;
    }

    // n es un nodo del árbol
    else {

        // n Tiene ambos hijos
        if (n->hijoIzq != NODO_NULO && n->hijoDer != NODO_NULO){

            // Promocionamos el hijo derecho de n
            if (n->hijoIzq->e > n->hijoDer->e){
                n.e = borrarMin(n->hijoDer, false);        // Borramos el min de la derecha
            }

            // Promocionamos el hijo izquierdo de n
            else {
                n.e = borrarMin(n->hijoIzq, true);        // Borramos el min de la izquierda
            }
        }

        // n Sólo tiene hijo Izdo
        else if (n->hijoIzq != NODO_NULO){
            n.e = borrarMin(n->hijoIzq, true);            // Borramos el min de la izquierda
        }

        // n Sólo tiene hijo Dcho
        else if (n->hijoDer != NODO_NULO){
            n.e = borrarMin(n->hijoDer, false);            // Borramos el min de la derecha
        }

        // n No tiene hijos
        else {

            // n es hijo izdo
            if (n->padre->hijoIzq == n){
                n->padre->hijoIzq = nullptr;
            }

            // n es hijo dcho
            else {
                n->padre->hijoDer = nullptr;
            }
            delete n;
        }
    }
}

template <typename T>
T ArbolBinario<T>::borrarMin(nodo n, bool esIzdo){

    T temp;

    // n es hoja
    if (n->hijoIzq == NODO_NULO && n->hijoDer == NODO_NULO){
        temp = n->e;
        n->padre = nullptr;

        if (esIzdo){
            n->padre->hijoIzq = nullptr;
        }
        else {
            n->padre->hijoDer = nullptr;
        }

        delete n;
    }

    // n tiene algun hijo
    else {

        // n tiene ambos hijos
        if (n->hijoIzq != NODO_NULO && n->hijoDer != NODO_NULO){

            // izdo > dcho => borramos por la derecha
            if (n->hijoIzq.e > n->hijoDer.e){
                temp = n.e;                                            // Guardamos el elemento de n para pasarselo al padre
                n.e = borrarMin(n->hijoDer, false);              // n tendrá el elemento borrado de su hijo
            }
            // dcho > izdo => borramos por la izquierda
            else {
                temp = n.e;
                n.e = borrarMin(n->hijoIzq, true);
            }
        }
        // n solo tiene hijo izdo
        else if (n->hijoIzq != NODO_NULO){
            temp = n.e;
            n.e = borrarMin(n->hijoIzq, true);
        }
        // n solo tiene hijo dcho
        else {
            temp = n.e;
            n.e = borrarMin(n->hijoDer, false);
        }
    }

    return temp;
}
// -------------

// TODO  --- Operaciones de consulta ---
template <typename T>
inline const T& ArbolBinario<T>::elemento(nodo n) const{

    // nodo n válido
    assert(n != NODO_NULO);

    return n->e;
}

template <typename T>
inline T& ArbolBinario<T>::elemento(nodo n) {

    // nodo n válido
    assert(n != NODO_NULO);

    return n->e;
}

template <typename T>
inline bool ArbolBinario<T>::arbolVacio() { return r == NODO_NULO;}

template <typename T>
inline bool ArbolBinario<T>::arbolVacio() const { return r == NODO_NULO; }

template <typename T>
inline typename ArbolBinario<T>::nodo ArbolBinario<T>::raiz() const { return r; }

template <typename T>
inline typename ArbolBinario<T>::nodo ArbolBinario<T>::padre(nodo n) const {

    assert(n != NODO_NULO);

    return n->padre;
}

template <typename T>
inline typename ArbolBinario<T>::nodo ArbolBinario<T>::hijoDer(nodo n) const {

    assert(n != NODO_NULO);

    return n->hijoDer;
}

template <typename T>
inline typename ArbolBinario<T>::nodo ArbolBinario<T>::hijoIzdo(nodo n) const {

    assert(n != NODO_NULO);

    return n->hijoIzq;
}
// -------------

// TODO --- Operadores ---
template <typename T>
ArbolBinario<T>& ArbolBinario<T>::operator=(const ArbolBinario<T> &a) {

    if(this != &a){

        // Destruimos todos los nodos de nuestro arbol
        this->~ArbolBinario();

        // Copiamos los nodos del otro arbol
        r = copiar(a.r);
    }
}
// -------------

template <typename T>
ArbolBinario<T>::~ArbolBinario<T>(){
    destruirNodos(r);
}


// TODO --- Métodos auxiliares ---
template <typename T>
void ArbolBinario<T>::destruirNodos(nodo &n) {

    if(n != NODO_NULO){
        if(n->hijoIzq != NODO_NULO) destruirNodos(n->hijoIzq);
        if(n->hijoDer != NODO_NULO) destruirNodos(n->hijoDer);
        delete n;
        n = NODO_NULO;
    }
}

template <typename T>
typename ArbolBinario<T>::nodo ArbolBinario<T>::copiar(nodo n) {

    nodo m = NODO_NULO;

    if(n != NODO_NULO){
        m = new celda(n->e, n->padre);          // Copiamos n
        m->hijoIzq = copiar(n->hijoIzq);        // Copiamos al hijo izquierdo
        m->hijoDer = copiar(n->hijoDer);        // Copiamos al hijo derecho
    }

    return m;
}
// -------------

// TODO --- Métodos nuevos ---
template<typename T>
int ArbolBinario<T>::profundidad(ArbolBinario::nodo n) const{

    if (n == NODO_NULO) return -1;

    typename ArbolBinario<T>::nodo actual = n;

    int i = 0;
    while (actual != r){
        i++;
        actual = actual->padre;
    }

    return i;
}

template <typename T>
int ArbolBinario<T>::calcularAltura(nodo n) const{
    if(n == NODO_NULO) return 0;
    else return 1 + std::max(calcularAltura(hijoIzdo(n)),
                             calcularAltura(hijoDer(n)));
}

template <typename T>
int ArbolBinario<T>::altura(ArbolBinario<T>::nodo n) const{
    if (n == ArbolBinario<T>::NODO_NULO) return 0;
    return max(calcularAltura(hijoIzdo(n)),
               calcularAltura(hijoDer(n)));
}
// -------------

#endif //ARBOLBINARIO_ARBOLBINARIO_H
