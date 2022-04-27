//
// Created by abrah on 13/04/2022.
//

#include "Agen.h"

template <typename T>
bool esTernario(const Agen<T>& A, typename Agen<T>::nodo n){

    typename Agen<T>::nodo temp = A.hijoIzqdo(n);
    int i = 0;
    while (temp != Agen<T>::NODO_NULO){

        // Evitamos seguir buscando
        if(!esTernario(A, temp)) return false;

        // Pasamos al hermano derecho
        i++;
        temp = A.hermDrcho(temp);
    }

    // Es ternario
    if(i == 0 || i == 3) return true;

    // Por defecto
    else return false;
}

template <typename T>
bool esTernario(const Agen<T>& A){

    assert(!A.arbolVacio());

    return esTernario(A, A.raiz());
}