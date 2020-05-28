#pragma once

#include <string>
#include <tuple>
#include <memory>
#include <functional>
#include "Cast.hpp"
#include "Rectangle.hpp"
#include "../Graphics/Character.hpp"

namespace VeriPy {
    class Character : public std::enable_shared_from_this<Character> {
    public:
        std::shared_ptr<Character> getptr() { return shared_from_this(); }

        Character(std::string const& path, std::tuple<float, float> const& imgCount, std::tuple<float, float> const& size, 
            std::tuple<float, float> const& position, uint sceneWidth);

        Character();
        ~Character() = default;

        void Create();
        void RemoveCast();

        void OnCastCollision(std::shared_ptr<VeriPy::Rectangle> rect, std::function<void(void)> const& action);

        /* Setters */
        void SetFilename(std::string const& filename);
        void SetSceneWidth(uint sceneWidth);

        void SetImageCount(std::tuple<float, float> const& imgCount);
        void SetImageCount(float x, float y);

        void SetSize(std::tuple<float, float> const& size);
        void SetSize(float w, float h);

        void SetPosition(std::tuple<float, float> const& position);
        void SetPosition(float x, float y);

        void SetIdle(std::vector<std::tuple<uint, uint>> const& animation);
        void SetWalking(std::vector<std::tuple<uint, uint>> const& animation);
        void SetCast(std::shared_ptr<VeriPy::Cast> cast);

        void SetSpeed(float speed);

        void Walk(std::tuple<float, float> const& velocity);
        void Walk(float xVelocity, float yVelocity);

        void TurnRight();
        void TurnLeft();

        /* Getters */
        std::tuple<float, float>  GetImageCount() const; 
        std::tuple<float, float>  GetSize()       const; 
        std::tuple<float, float>  GetPosition()   const;
        float                     GetSpeed()      const; 
        Veri::Character&          GetCharacter();

    private:
        std::string m_Filename;
        std::tuple<float, float> m_ImageCount;
        std::tuple<float, float> m_Size;
        std::tuple<float, float> m_Position;
        uint m_SceneWidth;
        float m_Speed;

        std::vector<std::tuple<uint, uint>> m_Idle;
        std::vector<std::tuple<uint, uint>> m_Walking;
        
        std::pair<std::shared_ptr<VeriPy::Rectangle>, std::function<void(void)>> m_CastCollision;

        std::shared_ptr<VeriPy::Cast> m_Cast;
        Veri::Character m_Character;
    };
}