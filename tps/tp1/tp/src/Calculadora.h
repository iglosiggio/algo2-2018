#ifndef __CALCULADORA_H_
#define __CALCULADORA_H_

#include <map>

#include "Programa.h"
#include "Utiles.h"

class Calculadora {
public:
	Calculadora(Programa programa);

	void asignarVariable(Id idVariable, int valor);

	void ejecutar(Id idRutina);

	int valorVariable(Id idVariable) const;
private:
	Programa programa;
	std::map<Id, int> variables;
};

#endif /*__CALCULADORA_H_*/
