#pragma once

#include "Cast.hpp"
#include <unordered_map>

namespace Veri {
    class Cooldowns {
    public:
        Cooldowns() = default;
        ~Cooldowns() = default;
        
        void Update(float deltaTime);
        bool IsOnCooldown(Cast* ability);

        void AddAbility(Cast* ability, float time);
        void RemoveAbility(Cast* ability);

    private:
        std::unordered_map<Cast*, float> m_Cooldowns;
    };
}