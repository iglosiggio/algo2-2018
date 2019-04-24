#include "Calculadora.h"
#include <stdexcept>
#include <stack>

#include <iostream>

Calculadora::Calculadora(Programa prog) {
	programa = prog;
}

void Calculadora::asignarVariable(Id idVariable, int valor) {
	variables[idVariable] = valor;
}

void Calculadora::ejecutar(Id idRutina) {
	std::stack<int> stack;
	int a;
	int b;

	for(int pc = 0; programa.esRutinaExistente(idRutina)
			&& pc < programa.longitud(idRutina); pc++) {
		Instruccion instr = programa.instruccion(idRutina, pc);

#ifdef PRINT_STACK
		std::cout << idRutina << ':' << pc << '\t' << instr.operacion() << '\t';
		std::stack<int> copy = stack;
		while(copy.size()) { std::cout << copy.top() << ' '; copy.pop(); }
		std:: cout << std::endl;
#endif

		switch (instr.operacion()) {
			case PUSH:
				stack.push(instr.valor());
				break;
			case ADD:
				a = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				b = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				stack.push(a + b);
				break;
			case SUB:
				a = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				b = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				stack.push(b - a);
				break;
			case MUL:
				a = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				b = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				stack.push(a * b);
				break;
			case READ:
				stack.push(valorVariable(instr.nombre()));
				break;
			case WRITE:
				a = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				asignarVariable(instr.nombre(), a);
				break;
			case JUMPZ:
				a = stack.empty() ? 0 : stack.top();
				if(stack.size()) stack.pop();
				if(a) break;
			case JUMP:
				idRutina = instr.nombre();
				pc = -1;
				break;
		}
	}
}

int Calculadora::valorVariable(Id idVariable) const {
	try {
		return variables.at(idVariable);
	} catch (const std::out_of_range& e) {
		return 0;
	}
}
