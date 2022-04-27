//
// Created by abrah on 16/03/2022.
//

#ifndef PRACTICA2EDNL_AGEN_H
#define PRACTICA2EDNL_AGEN_H

#include "cassert"

template <typename T>
class Agen {

    struct celda;

    public:

        typedef celda* nodo;
        static const nodo NODO_NULO;

        Agen();
        Agen(const Agen<T>& a);             // ctor. de copia

        void insertarRaiz(const T& e);
        void insertarHijoIzqdo(nodo n, const T& e);
        void insertarHermDrcho(nodo n, const T& e);
        void eliminarHijoIzqdo(nodo n);
        void eliminarHermDrcho(nodo n);
        void eliminarRaiz();
        bool arbolVacio() const;
        const T& elemento(nodo n) const;    // acceso a elto, lectura
        T& elemento(nodo n);                // acceso a elto, lectura/escritura
        nodo raiz() const;
        nodo padre(nodo n) const;
        nodo hijoIzqdo(nodo n) const;
        nodo hermDrcho(nodo n) const;

        Agen<T>& operator =(const Agen<T>& a); // asignación de árboles
        ~Agen();


private:
        struct celda {
            T elto;
            nodo hIzdo, herDer, padre;
            celda(const T& e, nodo pad = NODO_NULO, nodo hermanoDer = NODO_NULO, nodo hijoIzdo = NODO_NULO): elto(e), hIzdo(hijoIzdo), herDer(hermanoDer), padre(pad){};
        };

        nodo r;

        void destruirNodos(nodo& n);
        nodo copiar(nodo n);
};

// Definición del valor de NODO_NULO
template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(nullptr);


template<typename T>
inline Agen<T>::Agen(): r(NODO_NULO) {}

template<typename T>
Agen<T>::Agen(const Agen<T> &a) {
    r = copiar(a.raiz());
}

template<typename T>
void Agen<T>::insertarRaiz(const T &e) {
    assert(r == NODO_NULO);
    r = new celda(e);
}

template<typename T>
void Agen<T>::insertarHijoIzqdo(Agen::nodo n, const T &e) {
    assert(n != NODO_NULO);
    n->hIzdo = new celda(e, n, n->hIzdo);
}

template<typename T>
void Agen<T>::insertarHermDrcho(Agen::nodo n, const T &e) {
    assert(n != NODO_NULO);         // Nodo válido
    assert(n != r);                 // Nodo no es raíz
    n->herDer = new celda(e, n->padre, n->herDer);
}

template<typename T>
void Agen<T>::eliminarHijoIzqdo(Agen::nodo n) {
    assert(n != NODO_NULO);                 // Nodo válido

    // Cogemos el hijo izquierdo del nodo
    nodo tempHijoIzdo = n->hIzdo;

    assert(tempHijoIzdo !=  NODO_NULO);         // Tiene hijo iquierdo
    assert(tempHijoIzdo->hIzdo == NODO_NULO);    // Nodo izquierdo sea hoja


    n->hIzdo = tempHijoIzdo->herDer;
    delete tempHijoIzdo;
}

template <typename T>
void Agen<T>::eliminarHermDrcho(Agen::nodo n) {

    assert(n !=NODO_NULO);      // Nodo válido

    nodo tempHermDer = n->herDer;

    assert(tempHermDer != NODO_NULO);            // Tiene hermano derecho
    assert(tempHermDer->hIzdo == NODO_NULO);    // Hermano derecho sea hoja

    n->herDer = tempHermDer->herDer;            // Nuevo hermano derecho = herm derecho de herm derecho
    delete tempHermDer;
}

template<typename T>
void Agen<T>::eliminarRaiz() {

    assert(r != NODO_NULO);             // Árbol no vacío
    assert(r->hIzdo == NODO_NULO);      // La raíz es hoja

    delete r;
    r = NODO_NULO;
}

template<typename T>
inline bool Agen<T>::arbolVacio() const {
    return r == NODO_NULO;
}

template<typename T>
inline const T &Agen<T>::elemento(Agen::nodo n) const {
    assert(r != NODO_NULO);
    return n->elto;
}

template<typename T>
inline T &Agen<T>::elemento(Agen::nodo n) {
    assert(r != NODO_NULO);
    return n->elto;
}

template<typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const {return r;}

template<typename T>
inline typename Agen<T>::nodo Agen<T>::padre(Agen::nodo n) const {
    assert(n != NODO_NULO);     // Nodo válido
    return n->padre;
}

template<typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen::nodo n) const {
    assert(n != NODO_NULO);
    return n->hIzdo;
}

template<typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(Agen::nodo n) const {
    assert(n != NODO_NULO);
    return n->herDer;
}

template<typename T>
Agen<T> &Agen<T>::operator=(const Agen<T> &a) {

    // Evitamos autoasignación
    if(this != &a){
        this->~Agen();      // Vaciamos el árbol
        r = copiar(a.r);    // Copiamos el árbol
    }

    return *this;
}

template<typename T>
Agen<T>::~Agen() {

    // Eliminamos los nodos del árbol
    destruirNodos(r);
}

template<typename T>
void Agen<T>::destruirNodos(Agen::nodo &n) {

    // El nodo no es nulo
    if(n != NODO_NULO){

        // n tiene hijos
        if(n->hIzdo != NODO_NULO){

            nodo tempHerDer = n->hIzdo->herDer;

            while (tempHerDer != NODO_NULO){

                // Guardamos el hermano derecho
                n->hIzdo->herDer = tempHerDer->herDer;

                // Lo eliminamos
                destruirNodos(tempHerDer);

                // Lo actualizamos
                tempHerDer = n->hIzdo->herDer;
            }

            // Destruimos al hijo izquierdo
            destruirNodos(n->hIzdo);
        }

        // Destruimos n;
        delete n;
        n = NODO_NULO;
    }
}

template<typename T>
typename Agen<T>::nodo Agen<T>::copiar(Agen::nodo n) {

    nodo m = NODO_NULO;

    // n es un elemento válido
    if(n != NODO_NULO){

        m = new celda(n->elto);

        // n tiene descendientes
        if(n->hIzdo != NODO_NULO){
            m->hIzdo = copiar(n->hIzdo);
            m->hIzdo->padre = m;

            // Copiamos el resto de hijos
            nodo hijo = m->hIzdo;                   // A quien le añadiremos hermano derecho
            nodo tempHerDer = n->hIzdo->herDer;     // El hermano derecho propiamente dicho
            while (tempHerDer != NODO_NULO){

                // Copiamos el hermano derecho
                hijo->herDer = copiar(tempHerDer);

                // Nos "desplazamos" un hermano a la derecha
                hijo = hijo->herDer;
                tempHerDer = tempHerDer->herDer;
            }
        }
    }

    return m;
}


#endif //PRACTICA2EDNL_AGEN_H
