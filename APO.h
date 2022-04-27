//
// Created by abrah on 26/04/2022.
//

#ifndef PRACTICA4EDNL_APO_H
#define PRACTICA4EDNL_APO_H

#include <cassert>

using namespace std;

template <typename T>
class Apo {

public:
    explicit Apo(size_t maxNodos); // constructor
    void insertar(const T& e);
    void suprimir();
    const T& cima() const;
    bool vacio() const;
    Apo(const Apo<T>& A); // ctor. de copia
    Apo<T>& operator =(const Apo<T>& A); // asignación de apo
    ~Apo(); // destructor

private:
    typedef size_t nodo; // índice del vector

    // entre 0 y maxNodos-1
    T* nodos; // vector de nodos
    size_t maxNodos; // tamaño del vector
    size_t numNodos; // último nodo del árbol
    nodo padre(nodo i) const { return (i-1)/2; }
    nodo hIzq(nodo i) const { return 2*i+1; }
    nodo hDer(nodo i) const { return 2*i+2; }
    void flotar(nodo i);
    void hundir(nodo i);
};

#endif //PRACTICA4EDNL_APO_H
