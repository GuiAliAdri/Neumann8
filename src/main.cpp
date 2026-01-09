#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "hardware/Bus.hpp"
#include "hardware/CPU.hpp"
#include "monitor/SystemMonitor.hpp"

int main() {
    if (!glfwInit())
        return 1;
    GLFWwindow* window = glfwCreateWindow(800, 600, "Neumann-8 CPU Emulator", NULL, NULL);
    if (!window)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Instacia
    Bus bus;
    CPU cpu(bus);
    SystemMonitor monitor;

    // Firmware
    // Opcodes: A9=LDA, AA=TAX, E8=INX, FF=HALT
    std::vector<uint8_t> programa = {
        0xA9, 0x0A, // 00: LDA #10 (Decimal 10)
        0xAA,       // 02: TAX     (Copia pára X)
        0xE8,       // 03: INX     (X = 11)
        0xE8,       // 04: INX     (X = 12)
        0xFF,       // 05: HALT
    };

    bus.loadProgram(programa, 0x0000); // Carrega no endereco 0

    // MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        monitor.render(cpu, bus);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}