#include "hardware/CPU.hpp"
#include <iostream>

void CPU::reset() {
    a = 0;
    x = 0;
    pc = 0;
    flags.z = false;
    flags.n = false;
    isHalted = false;
}

uint8_t CPU::fetch() {
    uint8_t data = bus.read(pc);
    pc++;
    return data;
}

void CPU::clock() {
    if (isHalted) return;

    uint8_t opcode = fetch();

    switch (opcode) {
        case 0x00:
            break;
        
        case 0xA9:
        {
            uint8_t value = fetch();
            a = value;
            flags.z = (a == 0);
            flags.n = (a & 0x80);
            break;
        }

        case 0xAA:
            x = a;
            flags.z = (x == 0);
            flags.n = (x & 0x80);
            break;

        case 0xE8:
            x++;
            flags.z = (x == 0);
            flags.n = (x & 0x80);
            break;
        
        case 0xFF:
            isHalted = true;
            break;
        
        default:
            std::cout << "Opcode desconhecido: " << std::hex << (int)opcode << "\n";
            isHalted = true;
            break;
    }
}