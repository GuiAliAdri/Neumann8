#pragma once
#include "Bus.hpp"
#include <string>

/**
 * @brief CPU 8-bit Simplificada
 * Registradores: A (Acumulador), X (Indice), PC (Program Counter)
 * Flags: Z (Zero), N (Negative)
 */
class CPU
{
public:
    uint8_t a = 0;
    uint8_t x = 0;
    uint16_t pc = 0;

    struct Flags
    {
        bool z = false;
        bool n = false;
    } flags;

    Bus &bus;

    CPU(Bus &b) : bus(b) {}

    void reset();
    void clock();

    bool isHalted = false;

private:
    uint8_t fetch();
};