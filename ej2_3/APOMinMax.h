//
// Created by abrah on 26/04/2022.
//

#ifndef PRACTICA4EDNL_APOMINMAX_H
#define PRACTICA4EDNL_APOMINMAX_H

#include <cassert>
#include "math.h"

using namespace std;

template <typename T>
class APOMinMax {

public:
    explicit APOMinMax(size_t maxNodos); // constructor
    void insertar(const T& e);
    //void suprimir();
    const T& cima() const;
    bool vacio() const;
    APOMinMax(const APOMinMax<T>& A); // ctor. de copia
    APOMinMax<T>& operator =(const APOMinMax<T>& A); // asignación de apo
    ~APOMinMax(); // destructor

private:
    typedef size_t nodo; // índice del vector

    // entre 0 y maxNodos-1
    T* nodos; // vector de nodos
    size_t maxNodos; // tamaño del vector
    size_t numNodos; // último nodo del árbol
    nodo padre(nodo i) const { return (i-1)/2; }
    nodo hIzq(nodo i) const { return 2*i+1; }
    nodo hDer(nodo i) const { return 2*i+2; }
    size_t profundidad(nodo i) const { return log2(i+1); };
    void flotar(nodo i);
    //void hundir(nodo i);
};

#endif //PRACTICA4EDNL_APOMINMAX_H
