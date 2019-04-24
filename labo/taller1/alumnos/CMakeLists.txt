cmake_minimum_required(VERSION 2.8)
project(algo2_labo_clase4)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -ggdb3 -g")

# Dependencia de Google Test
SET(BUILD_GMOCK OFF)
SET(BUILD_GTEST ON)
include_directories(src/ tests/googletest-release-1.8.0)
add_subdirectory(tests/googletest-release-1.8.0)

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.hpp)

# Leemos todos los archivos de test en ./tests
file(GLOB TEST_SOURCES tests/*.cpp)


add_executable(correrTests ${SOURCE_FILES} tests/lista_tests.cpp)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

# Test suites a ejecutar
add_test(correrTests lista_test)

# Target para correr Valgrind
add_custom_target(correrValgrind
        valgrind --leak-check=full -v ./correrTests 2>&1
        DEPENDS correrTests)
