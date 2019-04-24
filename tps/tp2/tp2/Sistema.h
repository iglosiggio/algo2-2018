#ifndef __SISTEMA_H
#define __SISTEMA_H

#include <set>
#include <map>

#include "Transaccion.h"
#include "Parte.h"

typedef int Legajo;

/* Dado que el enunciado no nos fuerza a registrar información sobre las partes
 * las acciones de comprar y registrar hijos no reciben información sobre cómo
 * son las partes registradas */
class Sistema {
	friend class Transaccion;
public:
	/***************
	 * Generadores *
	 ***************/

	/* Pre:  true
	 *
	 * Post: agrega una nueva parte suelta, devuelve su Id
	 *       se le solicita un id al sistema */
	Id comprar();


	/* Parámetros:
	 *      Id parte: el id de la parte
	 * 
	 * Pre:  existe una parte en el sistema con ese id
	 *       ningún empleado está trabjando sobre esa parte (bloqueada es false)
	 *
	 * Post: elimina esa parte del mapa de partes y del set de partes sueltas */
	void vender(Id);

	/* Parámetros:
	 *      Legajo empleado: el número de legajo del empleado que realiza
	 *                       la transacción
	 *      Id parte: la parte sobre la cual se va a realizar la
	 *                transacción
	 *
	 * Pre:  existe una parte en el sistema con ese id
	 *       el empleado no tiene otra transacción abierta
	 *       esa parte es suelta
	 *       esa parte no está bloqueada
	 *
	 * Post: devuelve una transacción sobre la cual se pueden realizar las
	 *       operaciones, bloquea la parte suelta y registra la transacción
	 *       en el mapa transacciones */
	Transaccion nuevaTransaccion(Legajo, Id);

	/* Parámetros:
	 *      Legajo empleado: el número de legajo del empleado que realiza
	 *                       la transacción
	 *
	 * Pre:  existe una transacción en el sistema de ese empleado
	 *
	 * Post: se insertan todos los elementos de cambios en partes
	 *       se insertan todos los elementos de sueltasAgregadas a sueltas
	 *       se quitan los elementos de sueltasDesarmadas de sueltas (si
	 *       existen)
	 *       se elimina la transacción del legajo */
	void confirmarTransaccion(Legajo);

	/* Parámetros:
	 *      Legajo empleado: el número de legajo del empleado que realiza
	 *                       la transacción
	 *
	 * Pre:  existe una transacción en el sistema de ese empleado
	 *
	 * Post: elimina la transacción del mapa de transacciones */
	void cancelarTransaccion(Legajo);
	
	/* Pre:  true
	 *
	 * Post: lastId se incrementa en uno y se devuelve un id
	 *       no usado
	 *
	 * Forma de implementarlo:
	 * lastId++ */
	Id nuevoId();

	/****************
	 * Observadores *
	 ****************/

	/* Pre:  true
	 *
	 * Post: devuelve el set de partes sueltas
	 *
	 * Forma de implementarlo:
	 * sueltas */
	const std::set<Id>& partesSueltas() const;

	/* Pre:  true
	 *
	 * Post: devuelve el set Ids de partes del sistema
	 *
	 * Forma de implementarlo:
	 * itera por el mapa agregando la clave al set de retorno */
	const std::set<Id> conjuntoPartes() const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  true
	 *
	 * Post: determina si una parte existe
	 *
	 * Forma de implementarlo:
	 * partes.contains(id) */
	bool existeParte(Id) const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  existe una parte en el sistema con ese id 
	 *
	 * Post: informa del estado conocido de la parte
	 *
	 * Forma de implementarlo:
	 * partes[Id]->estado */
	Estado estadoParte(Id) const;

	/* Parámetros:
	 *       Id parte: el id de la parte
	 * 
	 * Pre:  existe una parte en el sistema con ese id 
	 *
	 * Post: informa del estado conocido de la parte
	 *
	 * Forma de implementarlo:
	 * partes[Id]->hijos */
	const std::set<Id>& hijosParte(Id) const;

	/* Parámetros:
	 *       Legajo legajo: el número de legajo del empleado
	 * 
	 * Pre:  true
	 *
	 * Post: informa si hay una transacción registrada desde ese número
	 *       de legajo 
	 *
	 * Forma de implementarlo:
	 * transacciones.contains(Legajo) */
	bool tieneTransaccionEmpleado(Legajo) const;

	/* Parámetros:
	 *       Legajo legajo: el número de legajo del empleado
	 * 
	 * Pre:  existe una transacción registrada a ese número de legajo
	 *
	 * Post: devuelve la transacción en curso por ese empleado
	 *
	 * Forma de implementarlo:
	 * transacciones[Legajo] */
	const Transaccion& transaccionEmpleado(Legajo) const;

	/* Pre:  true
	 *
	 * Post: devuelve los números de legajo con transacciones en curso
	 *
	 * Forma de implementarlo:
	 * itera por el mapa agregando la clave al set de retorno */
	const std::set<Legajo> empleadosTrabajando() const;
private:
	/* Invariante de representación:
	 * - Una parte existe sí y sólo sí su Id está en claves(partes)
	 * - Una parte es suelta sí y sólo sí está en sueltas
	 * - Una parte es vendible si !partes[id]->bloqueada y
	 *   sueltas.contains(id)
	 * - Todos los ids del sistema son menores a lastId
	 * - Si una parte está bloqueada pertenece a los cambios de alguna
	 *   transacción en curso
	 * - Si una parte está bloqueada entonces es suelta
	 * - La interseccion en los cambios de las transacciones es vacía
	 * - Ninguna parte tiene como hijos a partes que lo tienen como hijo
	 *   (directa o indirectamente)
	 * - Las partes tienen a lo sumo un padre */
	Id lastId;
	std::set<Id> sueltas;
	std::map<Id, Parte*> partes;
	std::map<Legajo, Transaccion> transacciones;
};

#endif
