#include "Programa.h"

// La clase Programa sirve para representar una secuencia de instrucciones.
//
//     Programa programa;
//
//     programa.agregarInstruccion("A", Instruccion(PUSH, 10));
//     programa.agregarInstruccion("A", Instruccion(PUSH, 20));
//     programa.agregarInstruccion("A", Instruccion(ADD));
//     programa.agregarInstruccion("A", Instruccion(JUMP, "A"));
//
//     programa.agregarInstruccion("B", Instruccion(PUSH, 30));
//     programa.agregarInstruccion("B", Instruccion(WRITE, "x"));
//
// Corresponde a las siguientes rutinas:
//
//     --- A ---
//       push(10)
//       push(20)
//       add
//       jump(A)
//
//     --- B ---
//       push(30)
//       write(x)

// Inicialmente no hay ninguna rutina.
Programa::Programa() {}

// Agrega una instrucción a la rutina indicada.
// Si la rutina indicada no existe, crea una nueva rutina
// con dicho nombre.
void Programa::agregarInstruccion(Id idRutina, Instruccion instruccion) {
	// operator[] corre el default constructor si no existe, es re buena onda
	code[idRutina].push_back(instruccion);
}

// Devuelve True si idRutina representa una rutina existente.
bool Programa::esRutinaExistente(Id idRutina) const {
	return code.find(idRutina) != code.end();
}

// Devuelve la longitud (cantidad de instrucciones) de la rutina
// indicada.
//
// Precondición: esRutinaExistente(idRutina)
int Programa::longitud(Id idRutina) const {
	return code.at(idRutina).size();
}

// Devuelve la i-ésima instrucción de la rutina indicada.
//
// Precondición:
//   esRutinaExistente(idRutina) && 0 <= i && i < longitud(idRutina)
Instruccion Programa::instruccion(Id idRutina, int i) const {
	return code.at(idRutina)[i];
}
