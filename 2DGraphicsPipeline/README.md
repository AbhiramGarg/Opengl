# 🚀 OpenGL 2D Graphics Pipeline

A foundational graphics project engineered from scratch, demonstrating core competency in **OpenGL** rendering, **GLSL** shader programming, and minimal 2D pipeline construction. Developed using a lightweight **WSL/Vim** workflow.

---

## ✨ Project Highlights

* **Custom 2D Pipeline:** Built a basic 2D graphics pipeline using **OpenGL** to manage vertices, draw calls, and the rendering loop.
* **Shader Programming:** Implemented custom **GLSL** (OpenGL Shading Language) Vertex and Fragment shaders to define geometry manipulation and multi-color rendering.
* **Minimal Rendering:** Successfully loads and renders a simple **multi-color rectangle** using the custom shader program, proving end-to-end functionality.
* **Development Environment:** Developed in a **Linux-like environment (WSL/Vim)** using **C++** and **SDL** for window management, showcasing proficiency with terminal-based development workflows.

---

## 🛠️ Technologies Used

| Technology | Purpose |
| :--- | :--- |
| **C++** | Primary language for the application logic and rendering engine. |
| **OpenGL** | Core API used for hardware-accelerated 2D rendering. |
| **GLSL** | Used to write custom Vertex and Fragment shaders. |
| **SDL2** | Handled window creation, context management, and input events. |
| **WSL/Vim** | Development environment, emphasizing lightweight and efficient tooling. |

---

## ⚙️ Build and Run

This project was developed on a Linux-like environment (WSL/Ubuntu).

### Prerequisites

You'll need a C++ compiler and the following libraries installed:

1.  **SDL3**
2.  **OpenGL/GLEW** (or equivalent modern OpenGL loader)
3.  **GCC/G++** or **Clang**

## 💡 Code Structure

The project primarily focuses on the rendering process:

* `main.cpp`: Initializes SDL and OpenGL, sets up the main rendering loop, and defines the vertex data.
* `./shaders`: Contains the following shaders.
* `vert.glsl`: Vertex Shader source file (GLSL).
* `frag.glsl`: Fragment Shader source file (GLSL) containing the multi-color logic.

---
