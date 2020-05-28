#include "SceneManager.hpp"
#include <unordered_map>
#include <memory>

namespace {
    std::unordered_map<std::string, std::shared_ptr<Veri::Scene>> s_Scenes;
}


namespace Veri {
    void SceneManager::CreateScene(std::string const& title, uint width) {
        s_Scenes.emplace(std::make_pair(title, std::make_shared<Scene>(title, width)));
    }


    void SceneManager::DestroyScene(std::string const& title) {
        s_Scenes.erase(title);
    }

    
    void SceneManager::DestroyScene(std::shared_ptr<Scene> ptr) {
        for (auto&[key, val] : s_Scenes) {
            if (val == ptr) {
                s_Scenes.erase(key);
                break;
            }
        }
    }


    std::shared_ptr<Scene> SceneManager::GetScene(std::string const& title) {
        if (auto where = s_Scenes.find(title); where != std::end(s_Scenes))
            return where->second;

        return nullptr;   
    }
}