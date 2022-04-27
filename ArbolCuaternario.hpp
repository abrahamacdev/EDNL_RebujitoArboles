#ifndef ARBOLCUATERNARIO_ARBOLCUATERNARIO_H
#define ARBOLCUATERNARIO_ARBOLCUATERNARIO_H

#include <iostream>
#include "cassert"
#include "algorithm"
using namespace std;

template <typename T>
class ArbolBinarioMenores {

    struct celda;

    public:
    typedef celda* nodo;            // Un nodo es un puntero a una celda
    static const nodo NODO_NULO;

    // Constructores
    ArbolBinarioMenores();                 // Cto

    // Operaciones de insercción
    void insertarRaiz(const T& e);
    void insertarHijos(nodo padre, const T& h1, const T& h2, const T& h3, const T& h4);

    // Operaciones de consulta
    const T& elemento(nodo n) const;
    T& elemento(nodo n);
    bool arbolVacio();
    bool arbolVacio() const;
    nodo raiz() const;
    nodo padre(nodo n) const;
    nodo hijo1(nodo n) const;
    nodo hijo2(nodo n) const;
    nodo hijo3(nodo n) const;
    nodo hijo4(nodo n) const;

    // Operaciones de eliminación
    void eliminarHijoIzdo(nodo n);
    void eliminarHijoDer(nodo n);
    void eliminarRaiz();

    // TODO Operaciones nuevas
    int profundidad(nodo n) const;
    int altura(nodo n) const;

    // Operadores
    ArbolBinarioMenores<T>& operator =(const ArbolBinarioMenores<T>& a);

    ~ArbolBinarioMenores();

    private:

        struct celda{
            T e;
            nodo padre, h1, h2, h3, h4;
            celda(const T& ele, nodo p = NODO_NULO, nodo h1, nodo h2, nodo h3, nodo h4):
                e(ele), padre(p), h1(NODO_NULO), h2(NODO_NULO), h3(NODO_NULO), h4(NODO_NULO) {}
        };

        nodo r;

        // Métodos auxiliares
        nodo copiar(nodo n);
        void destruirNodos(nodo& n);
};

// Definimos el valor de la constante NODO_NULO
// (Es necesario el "typename Ar..." inicial porque es un tipo que hemos definido dentro de la clase)
template <typename T>
const typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::NODO_NULO(nullptr);

// TODO  --- Constructores ---
template <typename T>
inline ArbolBinarioMenores<T>::ArbolBinarioMenores(): r(NODO_NULO) {}
// -------------

// TODO  --- Operaciones de insercción ---
template <typename T>
inline void ArbolBinarioMenores<T>::insertarRaiz(const T& e){
    assert(r == NODO_NULO); // Árbol vacío
    r = new celda(e);
}

// -------------

// TODO  --- Operaciones de eliminación ---
template <typename T>
void ArbolBinarioMenores<T>::eliminarRaiz() {

    // árbol no vacío y raíz no puede tener hijos
    assert(!arbolVacio());
    assert(r->hijoIzq == NODO_NULO && r->hijoDer == NODO_NULO);

    delete r;
    r = NODO_NULO;
}

template <typename T>
void ArbolBinarioMenores<T>::eliminarHijoIzdo(nodo n) {

    // n es nodo válido y su hijo izquierdo es hoja
    assert(n != NODO_NULO);
    assert(n->hijoIzq->hijoIzq == NODO_NULO && n->hijoIzq->hijo2 == NODO_NULO);

    delete n->hijoIzq;
    n->hijoIzq = NODO_NULO;
}

template <typename T>
void ArbolBinarioMenores<T>::eliminarHijoDer(nodo n) {

    // n es nodo válido y su hijo derecho es hoja
    assert(n != NODO_NULO);
    assert(n->hijoDer->hijoIzq == NODO_NULO && n->hijoDer->hijo2 == NODO_NULO);

    delete n->hijoDer;
    n->hijoDer = NODO_NULO;
}
// -------------

// TODO  --- Operaciones de consulta ---
template <typename T>
inline const T& ArbolBinarioMenores<T>::elemento(nodo n) const{

    // nodo n válido
    assert(n != NODO_NULO);

    return n->e;
}

template <typename T>
inline T& ArbolBinarioMenores<T>::elemento(nodo n) {

    // nodo n válido
    assert(n != NODO_NULO);

    return n->e;
}

template <typename T>
inline bool ArbolBinarioMenores<T>::arbolVacio() { return r == NODO_NULO;}

template <typename T>
inline bool ArbolBinarioMenores<T>::arbolVacio() const { return r == NODO_NULO; }

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::raiz() const { return r; }

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::padre(nodo n) const {

    assert(n != NODO_NULO);

    return n->padre;
}

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::hijo1(nodo n) const {

    assert(n != NODO_NULO);

    return n->h1;
}

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::hijo2(nodo n) const {

    assert(n != NODO_NULO);

    return n->h2;
}

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::hijo3(nodo n) const {

    assert(n != NODO_NULO);

    return n->h3;
}

template <typename T>
inline typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::hijo4(nodo n) const {

    assert(n != NODO_NULO);

    return n->h4;
}
// -------------

// TODO --- Operadores ---
template <typename T>
ArbolBinarioMenores<T>& ArbolBinarioMenores<T>::operator=(const ArbolBinarioMenores<T> &a) {

    if(this != &a){

        // Destruimos todos los nodos de nuestro arbol
        this->ArbolBinarioMenores();

        // Copiamos los nodos del otro arbol
        r = copiar(a.r);
    }
}
// -------------

template <typename T>
ArbolBinarioMenores<T>::~ArbolBinarioMenores<T>(){
    destruirNodos(r);
}


// TODO --- Métodos auxiliares ---
template <typename T>
void ArbolBinarioMenores<T>::destruirNodos(nodo &n) {

    if(n != NODO_NULO){
        if(n->hijoIzq != NODO_NULO) destruirNodos(n->hijoIzq);
        if(n->hijoDer != NODO_NULO) destruirNodos(n->hijoDer);
        delete n;
        n = NODO_NULO;
    }
}

template <typename T>
typename ArbolBinarioMenores<T>::nodo ArbolBinarioMenores<T>::copiar(nodo n) {

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
int ArbolBinarioMenores<T>::profundidad(ArbolBinarioMenores::nodo n) const{

    if (n == NODO_NULO) return -1;

    typename ArbolBinarioMenores<T>::nodo actual = n;

    int i = 0;
    while (actual != r){
        i++;
        actual = actual->padre;
    }

    return i;
}

template <typename T>
int ArbolBinarioMenores<T>::calcularAltura(nodo n) const{
    if(n == NODO_NULO) return 0;
    else return 1 + std::max(calcularAltura(hijo1(n)),
                             calcularAltura(hijo2(n)));
}

template <typename T>
int ArbolBinarioMenores<T>::altura(ArbolBinarioMenores<T>::nodo n) const{
    if (n == ArbolBinarioMenores<T>::NODO_NULO) return 0;
    return max(calcularAltura(hijo1(n)),
               calcularAltura(hijo2(n)));
}
// -------------

#endif //ARBOLCUATERNARIO_ARBOLCUATERNARIO_H
