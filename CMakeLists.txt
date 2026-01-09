cmake_minimum_required(VERSION 3.14)

# Nome do projeto (Confira se sua pasta no VS Code tem esse nome)
project(Neumann8 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Baixando Dependências (ImGui + GLFW) ---
include(FetchContent)

# GLFW
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw GIT_TAG master)
FetchContent_MakeAvailable(glfw)

# ImGui
FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui GIT_TAG docking)
FetchContent_MakeAvailable(imgui)

# --- 2. Preparando o ImGui (Biblioteca Estática) ---
add_library(imgui_lib STATIC
    "${imgui_SOURCE_DIR}/imgui.cpp"
    "${imgui_SOURCE_DIR}/imgui_draw.cpp"
    "${imgui_SOURCE_DIR}/imgui_tables.cpp"
    "${imgui_SOURCE_DIR}/imgui_widgets.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
    "${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(imgui_lib PUBLIC 
    ${imgui_SOURCE_DIR} 
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PRIVATE glfw opengl32)

# --- 3. Seu Projeto (Neumann8) ---
# Encontra todos os arquivos .cpp na pasta src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Cria o executável
add_executable(Neumann8 ${SOURCES})

# --- A CORREÇÃO MÁGICA PARA OS INCLUDES ---
# Isso permite que você faça #include "hardware/CPU.hpp" sem erro
target_include_directories(Neumann8 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Linka tudo junto
target_link_libraries(Neumann8 PRIVATE imgui_lib glfw opengl32)