#include "Widgets.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include "../WindowManager.hpp"
#include "fmt/fmt.hpp"

namespace VeriPy {
    bool Widgets::Begin(std::uint32_t flags, std::tuple<float, float> const& size) {
        ImGui::SetNextWindowSize(ImVec2{ std::get<0>(size), std::get<1>(size) });

        return ImGui::Begin("VeriPy-window", nullptr, flags);
    }


    void Widgets::End() {
        ImGui::End();
    }


    void Widgets::SetWindowPosition(std::tuple<float, float> const& pos) {
        ImGui::SetWindowPos(ImVec2{ std::get<0>(pos), std::get<1>(pos) });
    }


    void Widgets::SetFont(std::string const& filename, float size) {
        ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), size);
        ImGui::SFML::UpdateFontTexture();
    }


    bool Widgets::Button(std::string const& name, std::tuple<float, float> const& size) {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{0.5f, -100.f});
        bool result = ImGui::Button(name.c_str(), ImVec2{ std::get<0>(size), std::get<1>(size) });
        ImGui::PopStyleVar();
        return result;
    }


    void Widgets::Text(std::string const& text) {
        ImGui::TextUnformatted(text.c_str());
    }


    void Widgets::ColoredText(std::string const& text, float r, float g, float b, float a) {
        ImGui::TextColored(ImVec4{ r, g, b, a }, "%s", text.c_str());
    }
}