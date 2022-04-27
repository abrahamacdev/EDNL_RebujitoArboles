//
// Created by abrah on 26/04/2022.
//

#include "APOMinMax.h"
#include "math.h"

// APOMinMax vacío.
template <typename T>
inline APOMinMax<T>::APOMinMax(size_t maxNodos) : nodos(new T[maxNodos]), maxNodos(maxNodos), numNodos(0){}

template <typename T>
inline const T& APOMinMax<T>::cima() const
{
    assert(numNodos > 0); // APOMinMax no vacío.
    return nodos[0];
}
template <typename T>
inline bool APOMinMax<T>::vacio() const
{
    return (numNodos == 0);
}

template <typename T>
inline APOMinMax<T>::~APOMinMax()
{
    delete[] nodos;
}

template <typename T>
APOMinMax<T>::APOMinMax(const APOMinMax<T>& A) : nodos(new T[A.maxNodos]), maxNodos(A.maxNodos), numNodos(A.numNodos){
    // Copiar el vector.
    for (nodo n = 0; n < numNodos; n++)
        nodos[n] = A.nodos[n];
}

template <typename T>
APOMinMax<T>& APOMinMax<T>::operator =(const APOMinMax<T>& A){
    if (this != &A) // Evitar autoasignación.
    { // Destruir el vector y crear uno nuevo si es necesario.
        if (maxNodos != A.maxNodos)
        {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        numNodos = A.numNodos;
// Copiar el vector
        for (nodo n = 0; n < numNodos; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}

template<typename T>
void APOMinMax<T>::insertar(const T &e) {

    // Comprobamos que podamos insertar mas nodos
    assert(numNodos < maxNodos);

    // Lo insertamos al final del vector
    nodos[numNodos] = e;
    numNodos++;

    // Sí sólo tenemos la raíz es tontería flotar
    if(numNodos > 1){
        flotar(numNodos-1);
    }
}

template<typename T>
void APOMinMax<T>::flotar(APOMinMax::nodo i) {

    T& e = nodos[i];                                // Elemento inicial del nodo[i]
    bool nivelPar = profundidad(i) % 2 == 0;       // Comprobamos si está en un nivel par o impar

    if(nivelPar){

        // Comprobamos si somos menores que nuestro abuelo (nivel par => menos que nosotros)
        if(i > 0 && e < nodos[padre(padre(i))]){
            while (i > 0 && e < nodos[padre(padre(i))]){

                nodos[i] = nodos[padre(padre(i))];
                i = padre(padre(i));
            }
        }

        else {

            // Comprobamos que no seamos mayores que nuestro padre (nivel impar => mayor que nosotros)
            if(i > 2 && e > nodos[padre(i)]){

                // Cambiamos el elemento de nuestro padre con el nuestro
                nodos[padre(i)] = nodos[i];
                i = padre(i);

                // Comprobamos si somos mayores que nuestro abuelo
                while (i > 2 && e > nodos[padre(padre(i))]){

                    nodos[i] = nodos[padre(padre(i))];
                    i = padre(padre(i));
                }
            }
        }
    }

    // Estamos en nivel impar
    else {

        // Comprobamos si somos mayores que nuestro abuelo (nivel impar => mayor que nosotros)
        if(i > 2 && e > nodos[padre(padre(i))]){
            while (i > 2 && e > nodos[padre(padre(i))]){

                nodos[i] = nodos[padre(padre(i))];
                i = padre(padre(i));
            }
        }

        else {

            // Comprobamos si somos menores que nuestro padre (nivel par => menor que nosotros)
            if(i > 0 && e < nodos[padre(i)]){

                nodos[padre(i)] = nodos[i];
                i = padre(i);

                // Comprobamos si somos menores que nuestro abuelo
                while (i > 0 && e < nodos[padre(padre(i))]){

                    nodos[i] = nodos[padre(padre(i))];
                    i = padre(padre(i));
                }
            }
        }
    }


    // Insertamos el valor en el nodo que le corresponda
    nodos[i] = e;
}

/*template<typename T>
void APOMinMax<T>::suprimir() {

    // Árbol no vacío
    assert(numNodos > 0);

    // Quedan elementos después de borrar
    if(--numNodos > 0){
        nodos[0] = nodos[numNodos];       // Traemos el último elemento del árbol a la raíz

        if(numNodos > 1){
            hundir(0);                       // Hundimos el elemento de la raíz al nivel que le corresponda
        }
    }
}*/

/*template<typename T>
void APOMinMax<T>::hundir(APOMinMax::nodo i) {

    T& e = nodos[i];
    bool continuar = true;

    // Comprobamos que i no salga del alcance del bucle y que su hijo izquierdo esté también en rango
    while (hIzq(i) < numNodos && continuar){

        nodo eMin = hIzq(i);

        // Como también tiene hijo derecho, compararemos cual es el menor de ambos para traerlo a nuestra posicion
        if(hDer(i) < numNodos && nodos[hDer(i)] < nodos[hIzq(i)]){
            eMin = hDer(i);
        }

        // Subimos el mayor - nodos[eMin] <= e
        if(e > nodos[eMin] ){
            nodos[i] = nodos[eMin];
            i = eMin;
        }
        else {
            continuar = false;      // e <= nodosMin[eMin]
        }
    }

    nodos[i] = e;
}*/