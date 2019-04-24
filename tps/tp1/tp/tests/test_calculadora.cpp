#include "gtest/gtest.h"

#include "../src/Calculadora.h"

TEST(test_calculadora, termina) {
	Programa p;

	Calculadora c(p);

	c.ejecutar("cosas");
}

TEST(test_calculadora, asignar_variables) {
	Programa p;
	Calculadora c(p);

	c.asignarVariable("cosas", 107);
	EXPECT_EQ(c.valorVariable("cosas"), 107);
	EXPECT_EQ(c.valorVariable("otrascosas"), 0);
}

TEST(test_calculadora, correr_1_a_10) {
	Programa p;
	p.agregarInstruccion("starp", Instruccion(PUSH,  1));
	p.agregarInstruccion("starp", Instruccion(JUMP,  "lup"));
	p.agregarInstruccion("lup",   Instruccion(WRITE, "dup"));
	p.agregarInstruccion("lup",   Instruccion(READ,  "dup"));
	p.agregarInstruccion("lup",   Instruccion(READ,  "dup"));
	p.agregarInstruccion("lup",   Instruccion(PUSH,  1));
	p.agregarInstruccion("lup",   Instruccion(ADD));
	p.agregarInstruccion("lup",   Instruccion(WRITE, "dup"));
	p.agregarInstruccion("lup",   Instruccion(READ,  "dup"));
	p.agregarInstruccion("lup",   Instruccion(READ,  "dup"));
	p.agregarInstruccion("lup",   Instruccion(PUSH,  10)); /* Límite del loop */
	p.agregarInstruccion("lup",   Instruccion(SUB));
	p.agregarInstruccion("lup",   Instruccion(JUMPZ, "end"));
	p.agregarInstruccion("lup",   Instruccion(JUMP,  "lup"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out9"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out8"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out7"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out6"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out5"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out4"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out3"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out2"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out1"));
	p.agregarInstruccion("end",   Instruccion(WRITE, "out0"));

	Calculadora c(p);

	c.ejecutar("starp");
	EXPECT_EQ(c.valorVariable("out0"),  1);
	EXPECT_EQ(c.valorVariable("out1"),  2);
	EXPECT_EQ(c.valorVariable("out2"),  3);
	EXPECT_EQ(c.valorVariable("out3"),  4);
	EXPECT_EQ(c.valorVariable("out4"),  5);
	EXPECT_EQ(c.valorVariable("out5"),  6);
	EXPECT_EQ(c.valorVariable("out6"),  7);
	EXPECT_EQ(c.valorVariable("out7"),  8);
	EXPECT_EQ(c.valorVariable("out8"),  9);
	EXPECT_EQ(c.valorVariable("out9"), 10);
}

TEST(test_calculadora, correr_fibonacci) {
	Programa p;
	p.agregarInstruccion("fib", Instruccion(PUSH,  0));
	p.agregarInstruccion("fib", Instruccion(READ, "in"));
	p.agregarInstruccion("fib", Instruccion(JUMPZ, "end"));
	p.agregarInstruccion("fib", Instruccion(READ, "in"));
	p.agregarInstruccion("fib", Instruccion(PUSH,  1));
	p.agregarInstruccion("fib", Instruccion(SUB));
	p.agregarInstruccion("fib", Instruccion(WRITE,  "in"));
	p.agregarInstruccion("fib", Instruccion(PUSH,  1));
	p.agregarInstruccion("fib", Instruccion(READ, "in"));
	p.agregarInstruccion("fib", Instruccion(JUMPZ, "end"));
	p.agregarInstruccion("fib", Instruccion(READ, "in"));
	p.agregarInstruccion("fib", Instruccion(PUSH,  1));
	p.agregarInstruccion("fib", Instruccion(SUB));
	p.agregarInstruccion("fib", Instruccion(WRITE, "in"));
	p.agregarInstruccion("fib", Instruccion(JUMP, "lup"));
	p.agregarInstruccion("lup", Instruccion(WRITE, "tmp0"));
	p.agregarInstruccion("lup", Instruccion(READ, "tmp0"));
	p.agregarInstruccion("lup", Instruccion(ADD));
	p.agregarInstruccion("lup", Instruccion(WRITE,  "tmp1"));
	p.agregarInstruccion("lup", Instruccion(READ, "tmp0"));
	p.agregarInstruccion("lup", Instruccion(READ, "tmp1"));
	p.agregarInstruccion("lup", Instruccion(READ, "in"));
	p.agregarInstruccion("lup", Instruccion(JUMPZ, "end"));
	p.agregarInstruccion("lup", Instruccion(READ, "in"));
	p.agregarInstruccion("lup", Instruccion(PUSH,  1));
	p.agregarInstruccion("lup", Instruccion(SUB));
	p.agregarInstruccion("lup", Instruccion(WRITE,  "in"));
	p.agregarInstruccion("lup", Instruccion(JUMP,  "lup"));
	p.agregarInstruccion("end", Instruccion(WRITE,  "out"));

	Calculadora c(p);

	c.asignarVariable("in", 0);
	c.ejecutar("fib");
	EXPECT_EQ(c.valorVariable("out"), 0);

	c.asignarVariable("in", 1);
	c.ejecutar("fib");
	EXPECT_EQ(c.valorVariable("out"), 1);

	c.asignarVariable("in", 2);
	c.ejecutar("fib");
	EXPECT_EQ(c.valorVariable("out"), 1);

	c.asignarVariable("in", 10);
	c.ejecutar("fib");
	EXPECT_EQ(c.valorVariable("out"), 55);

	c.asignarVariable("in", 12);
	c.ejecutar("fib");
	EXPECT_EQ(c.valorVariable("out"), 144);
}

TEST(test_calculadora, evaluar_cuadratica) {
	Programa p;
	p.agregarInstruccion("f(x)", Instruccion(READ, "c"));
	p.agregarInstruccion("f(x)", Instruccion(READ, "b"));
	p.agregarInstruccion("f(x)", Instruccion(READ, "x"));
	p.agregarInstruccion("f(x)", Instruccion(MUL));
	p.agregarInstruccion("f(x)", Instruccion(ADD));
	p.agregarInstruccion("f(x)", Instruccion(READ, "a"));
	p.agregarInstruccion("f(x)", Instruccion(READ, "x"));
	p.agregarInstruccion("f(x)", Instruccion(READ, "x"));
	p.agregarInstruccion("f(x)", Instruccion(MUL));
	p.agregarInstruccion("f(x)", Instruccion(MUL));
	p.agregarInstruccion("f(x)", Instruccion(ADD));
	p.agregarInstruccion("f(x)", Instruccion(WRITE, "y"));

	Calculadora c(p);

	c.asignarVariable("a", 7);
	c.asignarVariable("b", 2);
	c.asignarVariable("c", 4);
	c.asignarVariable("x", 5);
	c.ejecutar("f(x)");
	/* f(x) = 7x^2 + 2x + 4
	 * f(5) = 189 */
	EXPECT_EQ(c.valorVariable("y"), 189);
}

TEST(test_calculadora, rutina_invalida) {
	Programa p;
	p.agregarInstruccion("rutina_posta", Instruccion(PUSH,  42));
	p.agregarInstruccion("rutina_posta", Instruccion(WRITE, "out"));
	p.agregarInstruccion("rutina_posta", Instruccion(JUMP,  "rutina_invalida"));
	p.agregarInstruccion("rutina_posta", Instruccion(PUSH,  28));
	p.agregarInstruccion("rutina_posta", Instruccion(WRITE, "out"));

	Calculadora c(p);

	c.ejecutar("rutina_posta");
	EXPECT_EQ(c.valorVariable("out"), 42);

	p.agregarInstruccion("rutina_invalida", Instruccion(PUSH,  28));
	p.agregarInstruccion("rutina_invalida", Instruccion(WRITE, "out"));

	Calculadora c2(p);

	c2.ejecutar("rutina_posta");
	EXPECT_EQ(c2.valorVariable("out"), 28);
}
