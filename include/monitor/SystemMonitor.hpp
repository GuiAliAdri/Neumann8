#pragma once
#include "hardware/CPU.hpp"
#include "hardware/Bus.hpp"

class SystemMonitor {
public:
    void render(CPU& cpu, Bus& bus);
};