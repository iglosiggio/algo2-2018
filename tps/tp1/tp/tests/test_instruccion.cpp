#include "gtest/gtest.h"

#include "../src/Instruccion.h"

TEST(test_instruccion, i_push) {
    Instruccion i(PUSH, 121);
    EXPECT_EQ(i.operacion(), PUSH);
    EXPECT_EQ(i.valor(), 121);
}

TEST(test_instruccion, i_add) {
    Instruccion i(ADD);
    EXPECT_EQ(i.operacion(), ADD);
}

TEST(test_instruccion, i_sub) {
    Instruccion i(SUB);
    EXPECT_EQ(i.operacion(), SUB);
}

TEST(test_instruccion, i_mul) {
    Instruccion i(MUL);
    EXPECT_EQ(i.operacion(), MUL);
}

TEST(test_instruccion, i_read) {
    Instruccion i(READ, "foo");
    EXPECT_EQ(i.operacion(), READ);
    EXPECT_EQ(i.nombre(), "foo");
}

TEST(test_instruccion, i_write) {
    Instruccion i(WRITE, "bar");
    EXPECT_EQ(i.operacion(), WRITE);
    EXPECT_EQ(i.nombre(), "bar");
}

TEST(test_instruccion, i_jump) {
    Instruccion i(JUMP, "baz");
    EXPECT_EQ(i.operacion(), JUMP);
    EXPECT_EQ(i.nombre(), "baz");
}

TEST(test_instruccion, i_jumpz) {
    Instruccion i(JUMPZ, "quux");
    EXPECT_EQ(i.operacion(), JUMPZ);
    EXPECT_EQ(i.nombre(), "quux");
}

