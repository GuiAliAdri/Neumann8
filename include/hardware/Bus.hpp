#pragma once
#include <array>
#include <cstdint>
#include <vector>

class Bus
{
public:
    std::array<uint8_t, 64 * 1024> ram;

    Bus()
    {
        ram.fill(0);
    }

    uint8_t read(uint16_t addr) const
    {
        return ram[addr];
    }

    void write(uint16_t addr, uint8_t data)
    {
        ram[addr] = data;
    }

    void loadProgram(const std::vector<uint8_t> &program, uint16_t offset = 0)
    {
        for (size_t i = 0; i < program.size(); i++)
        {
            if (offset + i < ram.size())
            {
                ram[offset + i] = program[i];
            }
        }
    }
};