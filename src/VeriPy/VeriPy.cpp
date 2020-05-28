#include "Scene.hpp"
#include "Player.hpp"
#include "Character.hpp"
#include "Rectangle.hpp"
#include "Widgets.hpp"
#include "Helper.hpp"

#include "pybind11/embed.h"
#include "pybind11/pybind11.h"
#include "pybind11/functional.h"
#include "pybind11/stl.h"
#include "pybind11/operators.h"
#include "imgui/imgui.h"

namespace Py = pybind11;

PYBIND11_EMBEDDED_MODULE(VeriPython, m) {
    m.doc() = "RPG Module used for scripting";
    
    m.def("FindFile", &VeriPy::FindFile, "Attempts to find a file no matter if it has a relative or absolute file");
    m.def("Sleep", &VeriPy::Sleep, "Sleeps");    
    m.def("SleepOnce", &VeriPy::SleepOnce, "Sleeps once");

    // Window Flags
    Py::enum_<VeriPy::WindowFlags::_>(m, "WindowFlags", Py::arithmetic())
        .value("NoFlags",      VeriPy::WindowFlags::NoFlags)
        .value("NoBackground", VeriPy::WindowFlags::NoBackground)
        .value("NoDecoration", VeriPy::WindowFlags::NoDecoration)
        .value("NoInputs",     VeriPy::WindowFlags::NoInputs)
        .value("NoMouseInput", VeriPy::WindowFlags::NoMouseInput)
        .value("NoTitleBar",   VeriPy::WindowFlags::NoTitleBar);

    // Widgets
    Py::class_<VeriPy::Widgets>(m, "Widgets")
        .def_static("Begin",             &VeriPy::Widgets::Begin, "Begins the widget rendering")
        .def_static("End",               &VeriPy::Widgets::End, "Ends the widget rendering")
        .def_static("SetWindowPosition", &VeriPy::Widgets::SetWindowPosition, "Sets the window position")
        .def_static("SetFont",           &VeriPy::Widgets::SetFont, "Sets the font from a .ttf file")
        .def_static("Button",            &VeriPy::Widgets::Button, "Creates a button")
        .def_static("Text",              &VeriPy::Widgets::Text, "Creates a text-label")
        .def_static("ColoredText",       &VeriPy::Widgets::ColoredText, "Creates a colored text-label");

    // Scene
    Py::class_<VeriPy::Scene>(m, "Scene")
        .def(Py::init<std::string const&, uint>())
        .def("Init",              &VeriPy::Scene::Init, "The initialization method, is ran once")
        .def("Loop",              &VeriPy::Scene::Loop, "The loop method, is ran continiously")
        .def("Quit",              &VeriPy::Scene::Quit, "Quits")
 
        .def("SetBackground",     &VeriPy::Scene::SetBackground, "Sets the background")
        .def("SetPlayer",         &VeriPy::Scene::SetPlayer, "Sets the player")

        .def("AddBounds",         &VeriPy::Scene::AddBounds, "Adds another bounds to the scene")
        .def("AddCharacter",      &VeriPy::Scene::AddCharacter, "Adds another character to the scene")
        .def("AddRectangle",      &VeriPy::Scene::AddRectangle, "Adds a rectangle")

        .def("RemoveCharacter",   &VeriPy::Scene::RemoveCharacter, "Removes a character by name")
        .def("RemoveRectangle",   &VeriPy::Scene::RemoveRectangle, "Removes a rectangle by name")

        .def("GetTitle",          &VeriPy::Scene::GetTitle,  "Gets the scene title")
        .def("GetWidth",          &VeriPy::Scene::GetWidth,  "Gets the scene width")
        .def("GetCharacter",      &VeriPy::Scene::GetCharacter, "Gets a character by name")
        .def("GetRectangle",      &VeriPy::Scene::GetRectangle, "Gets a rectangle by name")
        .def("GetPlayer",         &VeriPy::Scene::GetPlayer, "Gets the player");

    // Player
    Py::class_<VeriPy::Player, std::shared_ptr<VeriPy::Player>>(m, "Player")
        .def(Py::init<std::tuple<float, float> const&, uint>())
        .def(Py::init<>())

        .def("OnCastCollision", &VeriPy::Player::OnCastCollision, "Checks for collision between a rectangle and a cast")

        .def("SetSceneWidth",   &VeriPy::Player::SetSceneWidth, "Sets the scene width")
        .def("SetSpeed",        &VeriPy::Player::SetSpeed, "Sets the character speed")
        .def("SetPosition",     Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Player::SetPosition))
        .def("SetPosition",     Py::overload_cast<float, float>(&VeriPy::Player::SetPosition))
        .def("SetFacingLeft",   &VeriPy::Player::SetFacingLeft, "Sets the player facing left or right")
        .def("RemoveCast",      &VeriPy::Player::RemoveCast, "Removes the cast")
        .def("GetPosition",     &VeriPy::Player::GetPosition, "Gets the player position");

    // Character
    Py::class_<VeriPy::Character, std::shared_ptr<VeriPy::Character>>(m, "Character")
        .def(Py::init<std::string const&, std::tuple<float, float> const&, std::tuple<float, float> const&, std::tuple<float, float> const&, uint>())
        .def(Py::init<>())
        
        .def("OnCastCollision", &VeriPy::Character::OnCastCollision, "Checks for collision between a rectangle and a cast")
        .def("RemoveCast",      &VeriPy::Character::RemoveCast, "Removes the cast")

        .def("SetSceneWidth",   &VeriPy::Character::SetSceneWidth, "Sets the scene width")
        .def("SetFilename",     &VeriPy::Character::SetFilename, "Sets the path to the sprite")
        
        .def("SetImageCount",   Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Character::SetImageCount), "Sets the image count")
        .def("SetSize",         Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Character::SetSize), "Sets the size")
        .def("SetPosition",     Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Character::SetPosition), "Sets the position")
        
        .def("SetImageCount",   Py::overload_cast<float, float>(&VeriPy::Character::SetImageCount), "Sets the image count")
        .def("SetSize",         Py::overload_cast<float, float>(&VeriPy::Character::SetSize), "Sets the size")
        .def("SetPosition",     Py::overload_cast<float, float>(&VeriPy::Character::SetPosition), "Sets the position")
        .def("SetSpeed",        &VeriPy::Character::SetSpeed, "Sets the moving speed")
        .def("SetCast",         &VeriPy::Character::SetCast, "Sets the cast")

        .def("SetIdle",         &VeriPy::Character::SetIdle, "Sets the idle animation")
        .def("SetWalking",      &VeriPy::Character::SetWalking, "Sets the walking animation")

        .def("GetImageCount",   &VeriPy::Character::GetImageCount, "GetImageCount")
        .def("GetSize",         &VeriPy::Character::GetSize, "Gets the size")
        .def("GetPosition",     &VeriPy::Character::GetPosition, "Gets the position")
        .def("GetSpeed",        &VeriPy::Character::GetSpeed, "Gets the speed")

        .def("Walk",            Py::overload_cast<float, float>(&VeriPy::Character::Walk), "Makes the character walk")
        .def("Walk",            Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Character::Walk), "Makes the character walk")
        .def("TurnRight",       &VeriPy::Character::TurnRight, "Turns the character towards the right")
        .def("TurnLeft",        &VeriPy::Character::TurnLeft, "Turns the character towards the left");

    // Rectangle
    Py::class_<VeriPy::Rectangle, std::shared_ptr<VeriPy::Rectangle>>(m, "Rectangle")
        .def(Py::init<>())
        .def("Create",      &VeriPy::Rectangle::Create, "Creates the rectangle")
        .def("SetFilename", &VeriPy::Rectangle::SetFilename, "Sets the filename for the texture")
        .def("SetSize",     Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Rectangle::SetSize), "Sets the size")
        .def("SetPosition", Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Rectangle::SetPosition), "Sets the position")
        .def("SetColor",    Py::overload_cast<std::array<std::uint8_t, 4> const&>(&VeriPy::Rectangle::SetColor), "Sets the color")

        .def("SetSize",     Py::overload_cast<float, float>(&VeriPy::Rectangle::SetSize), "Sets the size")
        .def("SetPosition", Py::overload_cast<float, float>(&VeriPy::Rectangle::SetPosition), "Sets the position")
        .def("SetColor",    Py::overload_cast<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>(&VeriPy::Rectangle::SetColor), "Sets the color")
        
        .def("GetSize",     &VeriPy::Rectangle::GetSize, "Gets the size")
        .def("GetPosition", &VeriPy::Rectangle::GetPosition, "Gets the position")
        .def("GetColor",    &VeriPy::Rectangle::GetColor, "Gets the color");

    // Cast
    Py::class_<VeriPy::Cast, std::shared_ptr<VeriPy::Cast>>(m, "Cast")
        .def(Py::init<>())
        .def("Create",       &VeriPy::Cast::Create, "Creates the cast")
        .def("SetFilename",  &VeriPy::Cast::SetFilename, "Sets the filenaem to the texture")
        .def("SetAnimation", &VeriPy::Cast::SetAnimation, "Sets the animation")

        .def("SetColor",     Py::overload_cast<std::array<std::uint8_t, 4> const&>(&VeriPy::Cast::SetColor), "Sets the color")
        .def("SetPosition",  Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Cast::SetPosition), "Sets the position")
        .def("SetColor",     Py::overload_cast<std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t>(&VeriPy::Cast::SetColor), "Sets the color")        
        .def("SetSize",      Py::overload_cast<std::tuple<float, float> const&>(&VeriPy::Cast::SetSize), "Sets the size")
        
        .def("SetDirection", &VeriPy::Cast::SetDirection, "Sets the direction")
        .def("SetPosition",  Py::overload_cast<float, float>(&VeriPy::Cast::SetPosition), "Sets the position")
        .def("SetSize",      Py::overload_cast<float, float>(&VeriPy::Cast::SetSize), "Sets the size")
        
        .def("GetAnimation", &VeriPy::Cast::GetAnimation, "Gets the animation")
        .def("GetColor",     &VeriPy::Cast::GetColor, "Gets the color")
        .def("GetDireciton", &VeriPy::Cast::GetDirection, "Gets the direction")
        .def("GetSize",      &VeriPy::Cast::GetSize, "Gets the size")
        .def("GetPosition",  &VeriPy::Cast::GetPosition, "Gets the position");
}