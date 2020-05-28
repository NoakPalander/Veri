# CMake version
cmake_minimum_required(VERSION 3.5)

project(RPG LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# C++ version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs/)

# Sets debug make flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
# Sets release make flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -w -O3")

# Build ImGUI and ImGUI-SFML as a static library
add_library(ImGUI STATIC
    deps/imgui/imgui.cpp
    deps/imgui/imgui_demo.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui-SFML.cpp
    deps/imgui/imgui_widgets.cpp
)

# Set ImGUI relative include paths
target_include_directories(ImGUI PUBLIC 
    deps/imgui/
)

# Add Pybind11 as a subdirectory and sets it's include directories
add_subdirectory(deps/pybind11)
include_directories(deps/)

# Adds the module
pybind11_add_module(VeriPython 
    src/VeriPy/VeriPy.cpp
    src/VeriPy/Scene.cpp
    src/VeriPy/Character.cpp
    src/VeriPy/Widgets.cpp
    src/VeriPy/Rectangle.cpp
    src/VeriPy/Player.cpp
    src/VeriPy/Cast.cpp

    src/WindowManager.cpp

    src/Graphics/Animator.cpp
    src/Graphics/Character.cpp
    src/Graphics/Rectangle.cpp
    src/Graphics/Camera.cpp

    src/Logic/Event/EventManager.cpp
    src/Logic/Event/KbEvent.cpp
    src/Logic/Event/MbEvent.cpp
    src/Logic/Event/MtEvent.cpp
    src/Logic/Event/MwEvent.cpp
    src/Logic/Event/WinEvent.cpp

    src/Logic/Logger.cpp
    src/Logic/Collider.cpp
    src/Logic/AudioPlayer.cpp

    src/Game/Mage.cpp
    src/Game/Cooldowns.cpp
    src/Game/Scene.cpp
    src/Game/SceneManager.cpp
)

set_target_properties(ImGUI PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(VeriPython PUBLIC ImGUI GL)


# If the build is debug
if (CMAKE_BUILD_TYPE MATCHES Debug)
    message("DEFINING MACRO RPG_DEBUG")
    add_compile_definitions(RPG_DEBUG)

# If the build is release
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_definitions(RPG_RELEASE)
    message("DEFINING MACRO RPG_RELEASE")
endif()

# All the source files that should be compiled
add_executable(RPG
    src/main.cpp
    src/WindowManager.cpp
    
    src/VeriPy/VeriPy.cpp
    src/VeriPy/Scene.cpp
    src/VeriPy/Character.cpp
    src/VeriPy/Player.cpp
    src/VeriPy/Widgets.cpp
    src/VeriPy/Rectangle.cpp
    src/VeriPy/Cast.cpp

    
    src/Graphics/Animator.cpp
    src/Graphics/Character.cpp
    src/Graphics/Rectangle.cpp
    src/Graphics/Camera.cpp

    src/Logic/Logger.cpp
    src/Logic/Collider.cpp
    src/Logic/AudioPlayer.cpp

    src/Logic/Event/EventManager.cpp
    src/Logic/Event/KbEvent.cpp
    src/Logic/Event/MbEvent.cpp
    src/Logic/Event/MtEvent.cpp
    src/Logic/Event/MwEvent.cpp
    src/Logic/Event/WinEvent.cpp

    src/Game/Mage.cpp
    src/Game/Cooldowns.cpp
    src/Game/Scene.cpp
    src/Game/SceneManager.cpp
)

# Library path
link_directories(${CMAKE_BINARY_DIR}/libs)

# Link directories
target_include_directories(RPG PUBLIC
    deps/ 
    deps/pybind11/include/
    ${PYTHON_INCLUDE_DIRS}
)

# Link the final executable
target_link_libraries(RPG PUBLIC sfml-window sfml-system sfml-graphics sfml-audio pthread pybind11::embed GL ImGUI stdc++)