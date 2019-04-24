#include <limits>

template <typename T>
string_map<T>::string_map() : raiz(nullptr), _size(0) {}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() {
	*this = aCopiar;
}

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
	if(raiz) delete raiz;

	if(d.raiz) raiz = copiarNodo(d.raiz);
	else raiz = nullptr;

	_size = d._size;

	return *this;
}

template <typename T>
string_map<T>::~string_map() { if(raiz) delete raiz; }

template <typename T>
T& string_map<T>::operator[](const string& clave) {
	string busqueda = clave;
	Nodo** nodo = &raiz;

	while(*nodo && busqueda != "") {
		nodo = &(*nodo)->siguientes[busqueda[0]];
		busqueda = busqueda.substr(1);
	}

	if(!*nodo) *nodo = new Nodo();

	while(busqueda != "") {
		nodo = &(*nodo)->siguientes[busqueda[0]];
		*nodo = new Nodo();
		busqueda = busqueda.substr(1);
	}

	T** definicion = &(*nodo)->definicion;

	if(!*definicion) {
		*definicion = new T();
		_size++;
	}

	return **definicion;
}

template <typename T>
int string_map<T>::count(const string& clave) const {
	const Nodo* nodo = nodoAt(clave);

	return nodo && nodo->definicion ? 1 : 0;
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
	return nodoAt(clave)->definicion;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
	return nodoAt(clave)->definicion;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
	Nodo* nodo = nodoAt(clave);

	if(nodo && nodo->definicion) {
		delete nodo->definicion;
		nodo->definicion = nullptr;
		_size--;
	}
	/* FIXME: ¿Borrar el nodo si no tiene hijos? */
}

template <typename T>
int string_map<T>::size() const {
	return _size;
}

template <typename T>
bool string_map<T>::empty() const {
	return _size == 0;
}

template<typename T>
string_map<T>::Nodo::Nodo() :
	definicion(nullptr),
	siguientes(std::numeric_limits<unsigned char>::max(), nullptr) {}

template<typename T>
string_map<T>::Nodo::~Nodo() {
	for(auto n : siguientes) if(n) delete n;
	if(definicion) delete definicion;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::nodoAt(const string& clave) const {
	string busqueda = clave;
	Nodo* nodo = raiz;

	while(busqueda != "" && nodo) {
		nodo = nodo->siguientes[busqueda[0]];
		busqueda = busqueda.substr(1);
	}

	return nodo;
}

template <typename T>
typename string_map<T>::Nodo* string_map<T>::copiarNodo(const Nodo* nodo) {
	Nodo* copiado = new Nodo();

	if(nodo->definicion) copiado->definicion = new T(*nodo->definicion);

	for(int i = 0; i < nodo->siguientes.size(); i++) {
		Nodo* aCopiar = nodo->siguientes[i];
		if(aCopiar) copiado->siguientes[i] = copiarNodo(aCopiar);
	}

	return copiado;
}
