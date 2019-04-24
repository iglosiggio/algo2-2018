#ifndef __TRANSACCION_H
#define __TRANSACCION_H

#include <set>
#include <map>

#include "Sistema.h"
#include "Parte.h"

/* Dado que el enunciado no nos fuerza a registrar información sobre las partes
 * las acciones de comprar y registrar hijos no reciben información sobre cómo
 * son las partes registradas */

/* Notas: La existencia en el sistema es exsteParte(Id)
 *        Ser parte suelta es pertenecer al set devuelto por partesSueltas() */
class Transaccion {
	/* TODO: documentar cómo se modifica lastId*/
public:
	/***************
	 * Generadores *
	 ***************/

	/* Parámetros:
	 *       Id parte: el id de la parte
	 *       int hijos: la cantidad de hijos
	 * 
	 * Pre:  existe una parte en el sistema con ese id
	 *       la parte con ese id tiene estado NA
	 *       hijos >= 0
	 * 
	 * Post: la parte con ese id tiene estado Compuesto si hijos > 0
	 *       la parte con ese id tiene estado AtomicoNA si hijos = 0
	 *       el set retornado es el set de hijos de la parte
	 *       se le solicita un id al sistema por cada hijo */
	const std::set<Id>& registrarHijos(Id, int);

	/* Parámetros:
	 *       Id parte: el id de la parte
	 *       Estado nuevo: el nuevo estado
	 *
	 * Pre:  existe una parte en el sistema con ese id
	 *       la parte con ese id tiene estado NA, Bueno, Defectuoso o
	 *       AtomicoNA
	 *       el nuevo estado es Bueno o Defectuoso
	 *
	 * Post: la parte con ese id tiene el nuevo estado */
	void registrarEstado(Id, Estado);

	/* Parámetros:
	 *       Id parte: el id de la parte
	 *
	 * Pre:  existe una parte en el sistema con ese id
	 *       la parte con ese id tiene estado Compuesto
	 *       la parte con ese id pertenece a partesSueltas
	 *
	 * Post: no existe una parte en el sistema con ese id
	 *       quienes eran hijos de esta parte ahora son partes sueltas
	 *       (se quita de sueltas si estaba, se agrega  desarmadas y se
	 *       elimina del mapa) */
	void registrarDesarme(Id);

	/****************
	 * Observadores *
	 ****************/

	/* Pre:  true
	 *
	 * Post: devuelve el set de partes sueltas
	 *
	 * Forma de implementarlo:
	 * (sistema->partesSueltas() - sueltasDesarmadas) + sueltasAgregadas */
	const std::set<Id> partesSueltas() const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  true
	 *
	 * Post: determina si una parte existe
	 *
	 * Forma de implementarlo:
	 * !sueltasDesarmadas.contains(id)
	 * && (cambios.contains(id) || sistema->conjuntoPartes().contains(id)) */
	bool existeParte(Id) const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  existe una parte en el sistema con ese id 
	 *
	 * Post: informa del estado conocido de la parte
	 *
	 * Forma de implementarlo:
	 * cambios.contains(Id) ? cambios[Id]->estado
	 *                      : sistema->estadoParte(Id) */
	Estado estadoParte(Id) const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  existe una parte en el sistema con ese id 
	 *
	 * Post: informa del estado conocido de la parte
	 *
	 * Forma de implementarlo:
	 * cambios.contains(Id) ? cambios[Id]->hijos
	 *                      : sistema->hijosParte(Id) */
	const std::set<Id>& hijosParte(Id) const;
private:
	/* Invariante de representación:
	 * - Una parte existe sí y sólo sí su Id está en claves(cambios) ó en
	 *   sistema->conjuntoPartes() y no está en sueltasDesarmadas
	 * - Una parte es suelta sí y sólo sí está en sueltasAgregadas ó en
	 *   sistema->conjuntoPartes() y no está en sueltasDesarmadas */
	std::map<Id, Parte*> cambios;
	std::set<Id> sueltasDesarmadas;
	std::set<Id> sueltasAgregadas;
	const Sistema* sistema;
};

#endif
