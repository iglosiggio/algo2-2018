#include "Lista.h"

template <typename T>
Lista<T>::Lista() {
	primero = NULL;
	ultimo = NULL;
}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
	// Inicializa una lista vacía y luego utiliza operator= para no
	// duplicar el código de la copia de una lista.
	*this = l;
}

template <typename T>
Lista<T>::~Lista() {
	while(primero) eliminar(0);
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
	while(primero) eliminar(0);

	Lista<T>::Nodo* i;

	for(i = aCopiar.primero;
	    i;
	    i = i->siguiente) agregarAtras(i->valor);

	return *this;
}

template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
	if(primero)
		primero = primero->anterior = new Lista<T>::Nodo{primero, NULL, elem};
	else
		primero = ultimo = new Lista<T>::Nodo{NULL, NULL, elem};
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
	if(primero)
		ultimo = ultimo->siguiente = new Lista<T>::Nodo{NULL, ultimo, elem};
	else
		primero = ultimo = new Lista<T>::Nodo{NULL, NULL, elem};
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
	Lista<T>::Nodo* n = iesimoNodo(i);

	if(n == primero)
		primero = n->siguiente;
	else
		n->anterior->siguiente = n->siguiente;

	if(n == ultimo)
		ultimo = n->anterior;
	else
		n->siguiente->anterior = n->anterior;

	delete n;
}

template <typename T>
int Lista<T>::longitud() const {
	int l;
	Lista<T>::Nodo* i;

	for(i = primero, l = 0;
	    i;
	    i = i->siguiente, l++);

	return l;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
	return iesimoNodo(i)->valor;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
	return iesimoNodo(i)->valor;
}

template <typename T>
typename Lista<T>::Nodo* Lista<T>::iesimoNodo(Nat i) const {
	Lista<T>::Nodo* rval;

	for(rval = primero;
	    rval && i;
	    rval = rval->siguiente, i--);

	return rval;
}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
	o << "Contenidos de la lista:" << endl;

	Lista<T>::Nodo* i;

	for(i = primero;
	    i;
	    i = i->siguiente) o << '\t' << i->valor;

	o << endl;
}
