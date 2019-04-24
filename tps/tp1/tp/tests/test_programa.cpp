#include "gtest/gtest.h"

#include "../src/Instruccion.h"
#include "../src/Programa.h"

TEST(test_programa, rutinaExistente) {
    Programa p;
    EXPECT_EQ(p.esRutinaExistente("a"), false);
    EXPECT_EQ(p.esRutinaExistente("b"), false);
    p.agregarInstruccion("a", Instruccion(PUSH, 10));
    p.agregarInstruccion("a", Instruccion(ADD));
    EXPECT_EQ(p.esRutinaExistente("a"), true);
    EXPECT_EQ(p.esRutinaExistente("b"), false);
    p.agregarInstruccion("b", Instruccion(WRITE, "z"));
    EXPECT_EQ(p.esRutinaExistente("a"), true);
    EXPECT_EQ(p.esRutinaExistente("b"), true);
}

TEST(test_programa, longitud) {
    Programa p;
    p.agregarInstruccion("foo", Instruccion(PUSH, 10));
    EXPECT_EQ(p.longitud("foo"), 1);
    p.agregarInstruccion("foo", Instruccion(ADD));
    EXPECT_EQ(p.longitud("foo"), 2);
    p.agregarInstruccion("foo", Instruccion(PUSH, 12));
    EXPECT_EQ(p.longitud("foo"), 3);
    p.agregarInstruccion("foo", Instruccion(MUL));
    EXPECT_EQ(p.longitud("foo"), 4);
}

TEST(test_programa, instruccion) {
    Programa p;
    p.agregarInstruccion("X", Instruccion(READ, "x"));
    p.agregarInstruccion("X", Instruccion(PUSH, 2));
    p.agregarInstruccion("X", Instruccion(MUL));
    p.agregarInstruccion("X", Instruccion(READ, "y"));
    p.agregarInstruccion("X", Instruccion(ADD));
    EXPECT_EQ(p.longitud("X"), 5);
    EXPECT_EQ(p.instruccion("X", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("X", 0).nombre(), "x");
    EXPECT_EQ(p.instruccion("X", 1).operacion(), PUSH);
    EXPECT_EQ(p.instruccion("X", 1).valor(), 2);
    EXPECT_EQ(p.instruccion("X", 2).operacion(), MUL);
    EXPECT_EQ(p.instruccion("X", 3).operacion(), READ);
    EXPECT_EQ(p.instruccion("X", 3).nombre(), "y");
    EXPECT_EQ(p.instruccion("X", 4).operacion(), ADD);
}

TEST(test_programa, dosRutinas) {
    Programa p;
    p.agregarInstruccion("A", Instruccion(READ, "a"));
    p.agregarInstruccion("B", Instruccion(WRITE, "b"));
    p.agregarInstruccion("A", Instruccion(JUMP, "c"));
    p.agregarInstruccion("B", Instruccion(JUMPZ, "d"));
    p.agregarInstruccion("A", Instruccion(READ, "e"));

    EXPECT_EQ(p.longitud("A"), 3);
    EXPECT_EQ(p.longitud("B"), 2);
    EXPECT_EQ(p.instruccion("A", 0).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 0).nombre(), "a");
    EXPECT_EQ(p.instruccion("A", 1).operacion(), JUMP);
    EXPECT_EQ(p.instruccion("A", 1).nombre(), "c");
    EXPECT_EQ(p.instruccion("A", 2).operacion(), READ);
    EXPECT_EQ(p.instruccion("A", 2).nombre(), "e");

    EXPECT_EQ(p.instruccion("B", 0).operacion(), WRITE);
    EXPECT_EQ(p.instruccion("B", 0).nombre(), "b");
    EXPECT_EQ(p.instruccion("B", 1).operacion(), JUMPZ);
    EXPECT_EQ(p.instruccion("B", 1).nombre(), "d");
}

