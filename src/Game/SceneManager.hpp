#pragma once

#include "Scene.hpp"
#include <string>

namespace Veri { namespace SceneManager {
    void CreateScene(std::string const& title, uint width);
    void DestroyScene(std::string const& title);
    void DestroyScene(std::shared_ptr<Scene> ptr);

    std::shared_ptr<Scene> GetScene(std::string const& title);
}}