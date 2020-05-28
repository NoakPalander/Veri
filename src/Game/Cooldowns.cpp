#include "Cooldowns.hpp"

namespace Veri {
    void Cooldowns::Update(float deltaTime) {
        for (auto&[ability, timer]: m_Cooldowns) {
            // Updates the time remaining
            timer -= deltaTime;
            
            // If the time remaining is <= 0, remove it from the cooldowns list
            if (timer <= 0.f)
                if (IsOnCooldown(ability)) {
                    ability->isCasted = false;
                    m_Cooldowns.erase(ability);
                }
        }
    }


    bool Cooldowns::IsOnCooldown(Cast* ability) {
        auto finder = [ability](auto&& cast) -> bool { return cast.first == ability; };
        return std::find_if(std::begin(m_Cooldowns), std::end(m_Cooldowns), finder) != std::end(m_Cooldowns);
    }


    void Cooldowns::AddAbility(Cast* ability, float time) {
        m_Cooldowns.emplace(std::make_pair(ability, time));
    }


    void Cooldowns::RemoveAbility(Cast* ability) {
        if (IsOnCooldown(ability))
            m_Cooldowns.erase(ability);
    }
}