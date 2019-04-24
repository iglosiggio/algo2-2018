#include <vector>

template <class T>
typename Conjunto<T>::Busqueda Conjunto<T>::buscar(
	const T& valor,
	Nodo* raiz
) const {
	Nodo* curr = NULL;
	Nodo* next = raiz;

	while(next) {
		if(next->valor == valor) {
			break;
		}

		curr = next;
		
		if(curr->valor > valor) {
			next = curr->der;
		} else {
			next = curr->izq;
		}
	}

	return { next, curr };
}

template <class T>
typename Conjunto<T>::Busqueda Conjunto<T>::maximoDesde(Nodo* raiz) const {
	Nodo* padre = NULL;
	Nodo* max = raiz;

	if(!max) return { NULL, NULL };

	while(max->izq) {
		padre = max;
		max = padre->izq;
	}

	return { max, padre };
}

template <class T>
typename Conjunto<T>::Busqueda Conjunto<T>::minimoDesde(Nodo* raiz) const {
	Nodo* padre = NULL;
	Nodo* min = raiz;

	if(!min) return { NULL, NULL };

	while(min->der) {
		padre = min;
		min = padre->der;
	}

	return { min, padre };
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::maximo(Nodo* nodo) const {
	Nodo* next = nodo;

	while(next) {
		nodo = next;
		next = nodo->izq;
	}

	return nodo;
}

template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::minimo(Nodo* nodo) const {
	Nodo* next = nodo;

	while(next) {
		nodo = next;
		next = nodo->der;
	}

	return nodo;
}

template <class T>
unsigned int Conjunto<T>::cardinal(const Nodo* nodo) const {
	if(nodo) {
		return 1 + cardinal(nodo->izq) + cardinal(nodo->der);
	} else {
		return 0;
	}
}

template <class T>
void Conjunto<T>::reventarDesde(Nodo* nodo) {
	if(nodo) {
		reventarDesde(nodo->izq);
		reventarDesde(nodo->der);
		delete nodo;
	}
}

template <class T>
Conjunto<T>::Conjunto() : _raiz(NULL) {}

template <class T>
Conjunto<T>::~Conjunto() { 
	reventarDesde(_raiz);
}

template <class T>
Conjunto<T>::Nodo::Nodo(const T& v) : valor(v), izq(NULL), der(NULL) {}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
	Nodo* curr = _raiz;

	while(curr) {
		if(curr->valor == clave) {
			return true;
		} else if(curr->valor > clave) {
			curr = curr->der;
		} else {
			curr = curr->izq;
		}
	}

	return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
	Nodo* next = _raiz;
	Nodo* curr = NULL;

	while(next) {
		curr = next;

		if(curr->valor == clave) {
			return;
		} else if(curr->valor > clave) {
			next = curr->der;
		} else {
			next = curr->izq;
		}
	}

	if(curr) {
		if(curr->valor > clave) {
			curr->der = new Nodo(clave);
		} else {
			curr->izq = new Nodo(clave);
		}
	} else {
		_raiz = new Nodo(clave);
	}
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
	Busqueda borrar = buscar(clave, _raiz);
	Nodo* nodo = borrar.resultado;
	Nodo* padre = borrar.padre;

	if(nodo && nodo->izq && nodo->der) {
		/* Si tiene dos hijos */
		Busqueda max = maximoDesde(nodo->der);
		nodo->valor = max.resultado->valor;
		/* Cómo es máximo tiene a lo sumo un hijo a la
		 * derecha */
		if(max.resultado->der) {
			Nodo* hijo = max.resultado->der;
			*max.resultado = *hijo;
			delete hijo;
		} else {
			delete max.resultado;

			if(max.padre) {
				max.padre->izq = NULL;
			} else {
				nodo->der = NULL;
			}
		}
	} else if(nodo) {
		/* Si tiene uno o ningún hijo */
		Nodo* hijo = NULL;

		if(nodo->izq) {
			hijo = nodo->izq;
		} else if(nodo->der) {
			hijo = nodo->der;
		}

		if(padre) {
			if(padre->valor > clave) {
				padre->der = hijo;
			} else {
				padre->izq = hijo;
			}
		} else {
			_raiz = hijo;
		}

		delete nodo;
	}
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
	return static_cast<const Conjunto<T>*>(this)->siguiente(clave);
}

/* Esta es una solución sucia y fea, pero creo que funciona */
template <class T>
const T& Conjunto<T>::siguiente(const T& clave) const {
	Nodo* ultimoPadreMayor = NULL;
	Nodo* curr = _raiz;

	while(curr) {
		if(curr->valor == clave) {
			break;
		} else if(curr->valor > clave) {
			ultimoPadreMayor = curr;
			curr = curr->der;
		} else {
			curr = curr->izq;
		}
	}

	if(curr && curr->izq) {
		return minimoDesde(curr->izq).resultado->valor;
	}
	
	if(ultimoPadreMayor) {
		return ultimoPadreMayor->valor;
	}

	return clave;
}

template <class T>
const T& Conjunto<T>::minimo() const {
	return minimo(_raiz)->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
	return maximo(_raiz)->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
	return cardinal(_raiz);
}

template <class T>
void Conjunto<T>::mostrar(std::ostream& out) const {
	if(!_raiz) {
		out << "{}" << endl;
		return;
	}

	T curr = minimo();
	T next = siguiente(curr);

	out << "{ " << curr << ' ';

	while(curr != next) {
		curr = next;
		next = siguiente(curr);
		out << curr << ' ';
	}
	
	out << '}' << endl;
}

