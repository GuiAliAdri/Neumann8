# ⚡ Neumman - Processor Simulator

**Neumman** is a C++ project designed to simulate the inner workings of a CPU based on the **Von Neumann architecture**. It implements the core components of a computer system, including the Processor (CPU), Memory (RAM), and a custom Instruction Set Architecture (ISA).

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Architecture](https://img.shields.io/badge/Architecture-Von_Neumann-orange)
![License](https://img.shields.io/badge/License-MIT-green)

## 🧠 About the Project

The goal of Project Neumman is to emulate the low-level operations of a processor. It simulates the classic **Fetch-Decode-Execute** cycle, allowing users to write low-level assembly-like programs and see how the CPU processes instructions, manipulates registers, and accesses memory.

## ✨ Key Features

* **CPU Emulation:** Simulation of registers (PC, IR, Accumulator) and ALU (Arithmetic Logic Unit).
* **Memory Management:** A virtual RAM system to store both instructions and data.
* **Instruction Cycle:** Visual representation of the Fetch, Decode, and Execute stages.
* **Custom ISA:** Supports basic instructions such as `LOAD`, `STORE`, `ADD`, `SUB`, `JUMP`, and `HALT`.

## 📂 Project Structure

```text
Neumman/
├── src/
│   ├── main.cpp        # Entry point of the simulator
│   ├── cpu.cpp         # Processor logic (Fetch/Decode/Execute)
│   ├── memory.cpp      # RAM simulation
│   └── isa.h           # Instruction Set definitions
├── include/            # Header files
├── build/              # Compiled binaries
└── README.md
```
#### Made by: Guilherme Ali Adri