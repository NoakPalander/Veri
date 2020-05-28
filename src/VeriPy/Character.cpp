#include "Character.hpp"
#include "../Logic/Logger.hpp"


template<typename T>
static std::vector<sf::Vector2<T>> TupleVecToSfVec(std::vector<std::tuple<T, T>> const& input) {
    std::vector<sf::Vector2<T>> out{};
    out.reserve(input.size());

    for (auto const&[first, second] : input)
        out.emplace_back(sf::Vector2<T>{ first, second });

    return out;
}


namespace VeriPy {
    Character::Character(std::string const& path, std::tuple<float, float> const& imgCount, std::tuple<float, float> const& size, 
            std::tuple<float, float> const& position, uint sceneWidth)

        :   m_Filename{path}, m_ImageCount{imgCount}, m_Size{size}, m_Position{position}, m_SceneWidth{sceneWidth},
            m_Speed{150.f}, m_Idle{}, m_Walking{}, m_Cast{}, m_Character{}
    {
    }


    Character::Character()
        :   m_Filename{}, m_ImageCount{}, m_Size{}, m_Position{}, m_Speed{150.f}, m_Idle{}, m_Walking{}, m_Cast{}, m_Character{}
    {
    }


    void Character::Create() {
        auto[imgX, imgY] = m_ImageCount;    // count
        auto[width, height] = m_Size;       // size
        auto[x, y] = m_Position;            // pos

        // Creates the character
        m_Character.Init(m_Filename, { imgX, imgY }, { width, height }, { x, y }, m_Speed, 0.f, 0.3f, m_SceneWidth);
        m_Character.SetIdle(TupleVecToSfVec<uint>(m_Idle));
        m_Character.SetWalking(TupleVecToSfVec<uint>(m_Walking));
    }


    void Character::RemoveCast() {
        m_Character.RemoveCast();
        m_Cast.reset();
        m_Cast = nullptr;
    }


    void Character::OnCastCollision(std::shared_ptr<VeriPy::Rectangle> rect, std::function<void(void)> const& action) {
        if (m_Cast != nullptr) {
            sf::Vector2f direction{};

            if (rect->GetRectangle()->GetCollider().CheckCollision(m_Cast->GetCast()->cast.GetCollider(), direction, 1.f))
                action();
        }
    }


    void Character::SetFilename(std::string const& filename) {
        m_Filename = filename;
    }


    void Character::SetSceneWidth(uint sceneWidth) {
        m_SceneWidth = sceneWidth;
    }


    void Character::SetImageCount(std::tuple<float, float> const& imgCount) {
        m_ImageCount = imgCount;
    }
    

    void Character::SetImageCount(float x, float y) {
        m_ImageCount = std::make_tuple(x, y);
    }


    void Character::SetSize(std::tuple<float, float> const& size) {
        m_Size = size;
    }


    void Character::SetSize(float w, float h) {
        m_Size = std::make_tuple(w, h);
    }


    void Character::SetPosition(std::tuple<float, float> const& position) {
        m_Position = position;
    }


    void Character::SetPosition(float x, float y) {
        m_Position = std::make_tuple(x, y);
    }


    void Character::SetSpeed(float speed) {
        m_Speed = speed;
    }


    void Character::SetIdle(std::vector<std::tuple<uint, uint>> const& animation) {
        m_Idle = animation;
    }


    void Character::SetWalking(std::vector<std::tuple<uint, uint>> const& animation) {
        m_Walking = animation;
    }


    void Character::SetCast(std::shared_ptr<VeriPy::Cast> cast) {
        m_Cast = cast;
        m_Cast->Create();
        
        m_Character.SetCast(m_Cast->GetCast().get());
    }


    void Character::Walk(std::tuple<float, float> const& velocity) {
        m_Character.SetVelocity({ std::get<0>(velocity), std::get<1>(velocity) });
        m_Character.SetFacingLeft(m_Character.GetVelocity().x < 0.f);
    }


    void Character::Walk(float xVelocity, float yVelocity) {
        m_Character.SetVelocity({ xVelocity, yVelocity });
        m_Character.SetFacingLeft(m_Character.GetVelocity().x < 0.f);
    }


    void Character::TurnRight() {
        m_Character.SetFacingLeft(false);
    }


    void Character::TurnLeft() {
        m_Character.SetFacingLeft(true);
    }


    std::tuple<float, float> Character::GetImageCount() const {
        return m_ImageCount;
    }

    std::tuple<float, float> Character::GetSize() const {
        return std::make_tuple(m_Character.GetSize().x, m_Character.GetSize().y);
    } 

    std::tuple<float, float> Character::GetPosition() const {
        return std::make_tuple(m_Character.GetPosition().x, m_Character.GetPosition().y);
    }

    float Character::GetSpeed() const {
        return m_Speed;
    }
    
    Veri::Character& Character::GetCharacter() {
        return m_Character;
    }
}