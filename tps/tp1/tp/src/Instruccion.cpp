#include "Instruccion.h"

// Precondición: la operación es PUSH
Instruccion::Instruccion(Operacion operacion, int valor) {
	switch (operacion) {
		case PUSH:
			opcode = operacion;
			v = valor;
			return;
		default:
			throw "Pasaron cosas";
	}
}

// Precondición: la operación es ADD, SUB o MUL
Instruccion::Instruccion(Operacion operacion) {
	switch (operacion) {
		case ADD:
		case SUB:
		case MUL:
			opcode = operacion;
			return;
		default:
			throw "Pasaron cosas";
	}
}

// Precondición: la operación es READ, WRITE, JUMP o JUMPZ
Instruccion::Instruccion(Operacion operacion, Id nombre) {
	switch (operacion) {
		case READ:
		case WRITE:
		case JUMP:
		case JUMPZ:
			opcode = operacion;
			id = nombre;
			return;
		default:
			throw "Pasaron cosas";
	}
}

// Construcción de copia
Instruccion::Instruccion(const Instruccion& instruccion) {
	opcode = instruccion.opcode;
	switch (opcode) {
		case READ:
		case WRITE:
		case JUMP:
		case JUMPZ:
			id = instruccion.id;
			break;
		case PUSH:
			v = instruccion.v;
			break;

	}
}

Operacion Instruccion::operacion() const {
	return opcode;
}

// Precondición: la operación es PUSH
int Instruccion::valor() const {
	switch (opcode) {
		case PUSH:
			return v;
		default:
			throw "Pasaron cosas";
	}
}

// Precondición: la operación es READ, WRITE, JUMP o JUMPZ
Id Instruccion::nombre() const {
	switch (opcode) {
		case READ:
		case WRITE:
		case JUMP:
		case JUMPZ:
			return id;
		default:
			throw "Pasaron cosas";
	}
}
