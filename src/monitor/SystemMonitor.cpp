#include "monitor/SystemMonitor.hpp"
#include "imgui.h"
#include <bitset>

void TextBinary(uint8_t val) {
    for (int i = 7; i >= 0; i--) {
        bool bit = (val >> i) & 1;
        if (bit) ImGui::TextColored(ImVec4(0,1,0,1), "1");
        else ImGui::TextColored(ImVec4(0.3,0.3,0.3,1), "0");
        ImGui::SameLine();
    }
    ImGui::NewLine();
}

void SystemMonitor::render(CPU& cpu, Bus& bus) {
    ImGui::Begin("Neumann-8 Debugger");

    if (ImGui::CollapsingHeader("Registros Internos", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2, "cpu_cols", true);

        ImGui::Text("Reg A (Accumulator)");
        ImGui::Text("Hex: 0x%02X", cpu.x);
        ImGui::Text("Bin: "); ImGui::SameLine(); TextBinary(cpu.x);

        ImGui::Columns(1);
        ImGui::Separator();

        ImGui::Text("PC (Program Counter): 0x%04X", cpu.pc);

        ImGui::Text("Flags: ");
        ImGui::SameLine();
        ImGui::Checkbox("N (Negative)", &cpu.flags.n);
    }

    ImGui::Separator();
    if (cpu.isHalted) ImGui::TextColored(ImVec4(1,0,0,1), "STATUS: PARADO (HALT)");
    else ImGui::TextColored(ImVec4(0,1,0,1), "STATUS: AGUARDANDO CLOCK");

    if (ImGui::Button("STEP CLOCK (Executar 1 Instr)")) {
        cpu.clock();
    }
    ImGui::SameLine();
    if (ImGui::Button("RESET")) {
        cpu.reset();
    }

    // --- MEMORIA (HEX DUMP) ----
    ImGui::Separator();
    ImGui::Text("Visual de RAM (Primeiros 16 Bytes)");

    if (ImGui::BeginTable("ram_table", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        // Header
        ImGui::TableSetupColumn("Offset");
        for (int i=0; i<8; i++) ImGui::TableSetupColumn(std::to_string(i).c_str());
        ImGui::TableHeadersRow();

        for (int row = 0; row < 2; row++) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("0x%04X", row * 8);

            for (int col = 0; col < 8; col++) {
                ImGui::TableNextColumn();
                int addr = (row * 8) + col;

                if (cpu.pc == addr)
                    ImGui::TextColored(ImVec4(1,1,0,1), "%02X", bus.read(addr));
                else
                    ImGui::Text("%02X", bus.read(addr));
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}