# Veri & VeriPy
![Veri-logo](resources/Logos/veri.png)

Veri is a minimalistic and simple RPG-Game engine developed in C++, for Python. It was built as a high school project in 2 weeks, where the aim was to be able to create simple games in python running a C++ backend.

It utilizes some popular 3d party libraries, all but 1 built within the project itself
  - [SFML 2.5.1](https://www.sfml-dev.org/)
  - [Pybind11](https://github.com/pybind/pybind11)
  - [Dear ImGui](https://github.com/ocornut/imgui)
  - [ImGUI - SFML (binding)](https://github.com/eliasdaler/imgui-sfml)
  - [FmtLib](https://github.com/fmtlib/fmt)
  - [Spdlog](https://github.com/gabime/spdlog)

### Current release
It's currently in the 1.0 alpha stage, it does compile, it does run, but is not filled with bloated features.
It has official testing under several Linux distributions including:
- Arch Linux
- Manjaro Linux
- Debian-based Linux
Unofficial support is available for all platforms supporting a C++17 compiler (preferrably GCC 9.3), Python 3, and OpenGL for internal drawing.

### How does it work
You simply import the built VeriPy python module and of you go. Each function call inside of the module maps to a unique
function or object instansiated in native C++ for optimal performance.
It's simple to use, lightweight, but also completely customizable due to the open source nature of the project.

It's built using SFML instead of directly utilizing graphics api's like OpenGL, Vulkan, Metal, or DirectX, mainly due to the simplistic nature of the project, it's very easy to modify due to this design choice.

### Requirements
VeriPy requires you to manually install SFML 2.5, this can be done in several ways, 
For the debian Linux distribution it is usually done via the apt package manager it can be done via: [`sudo apt-get install libsfml-dev`]
For arch-based distributions using the pacman package manager it can be done via: [`sudo pacman -S sfml`]

The native build system for Veri is CMake, this can also be installed using serverla different package managers.
For debian Linux distributions it can be done by using the apt package manager via: [`sudo apt-get install cmake`]
or using pacman on Arch based distributions via: [`sudo pacman -S cmake`]

#### Building
To build the project you must ensure that you have support for the requirements above, building can either be done via the CMake GUI, or via the CMake CLI. To build with the CLI you can e.g use:
```bash
mkdir build                                     # Creates a build folder
cd build                                        # Enters the build folder
cmake -S ../ -B . -DCMAKE_BUILD_TYPE=Release    # Generates the build files
make                                            # Compiles all submodules
```
#### Debugging
You can use whatever debugger you prefer, but GDB has been used for this project.



License
----
MIT License

Copyright (c) [2020] [Noak Palander]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
