#ifndef __PARTE_H
#define __PARTE_H

#include <set>

typedef int Id;
typedef int Legajo;

/* AtomicoNA significa que sabemos que una parte es atómica pero desconocemos
 * su estado (por ejemplo se registró su conjunto de hijos cómo nulo) */
enum Estado { NA, Bueno, Defectuoso, Compuesto, AtomicoNA };

/* Lar partes no llevan Id porque eso es algo que maneja el sistema a escala
 * global */
struct Parte {
	std::set<Id> hijos;
	Estado estado;
	bool bloqueada;
	/* Invariante de representación:
	 * - Si el estado es NA, Bueno, Defectuoso o AtomicoNA entonces el
	 *   conjunto de hijos es vacío.
	 * - Si el estado es Compuesto entonces el conjunto de hijos no es
	 *   vacío */
};

#endif
