#pragma once

#include <string>
#include <tuple>
#include <vector>

namespace VeriPy {
    namespace WindowFlags {
        // Copied from imgui.h
        enum _ : std::uint32_t {
            NoFlags      = 0,
            NoBackground = 1 << 7,
            NoDecoration = 1 | 2 | 32,
            NoInputs     = 1 << 9 | 1 << 18 | 1 << 19,
            NoMouseInput = 1 << 9,
            NoTitleBar   = 1 << 0
        };   
    }

    class Widgets {
    public:
        static bool Begin(std::uint32_t flags, std::tuple<float, float> const& size);
        static void End();

        static void SetWindowPosition(std::tuple<float, float> const& pos);
        static void SetFont(std::string const& filename, float size);

        static bool Button(std::string const& name, std::tuple<float, float> const& size);
        static void Text(std::string const& text);
        static void ColoredText(std::string const& text, float r, float g, float b, float a);
    };
}