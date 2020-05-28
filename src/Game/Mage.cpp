#include "Mage.hpp"

#include "fmt/fmt.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <thread>
#include <utility>
#include "../Logic/Logger.hpp"
#include "../Logic/Filesystem.hpp"


// temporary, TODO: Convert animations indecies with json configuration
static std::vector<sf::Vector2u> RowFromIndex(uint row, uint len) {
    std::vector<sf::Vector2u> out{};
    std::generate_n(std::back_inserter(out), len, [row, index = 0u]() mutable { return sf::Vector2u { index++, row }; });
    return out;
}


namespace Veri {
	Mage::Mage(uint sceneWidth, sf::Vector2f const& pos, sf::Vector2f const& size, float switchTime)
		:   Character{ FindFile("../resources/Textures/mage.png"), { 7, 7 }, size, pos, 250.f, 150.f, switchTime, sceneWidth },

			m_SceneWidth{sceneWidth},
			m_Position{pos},
			m_Size{size},
			//                                  W      H          X    Y                            Path                         		   Color                      cast   right 
			m_Thunder      { Cast{ Rectangle{{ 200.f, 100.f }, { 0.f, 0.f }, FindFile("../resources/Particles/spark_05.png"),  sf::Color::Cyan  },            false, false }},
			m_ThunderCloud { Cast{ Rectangle{{ 200.f, 200.f }, { 0.f, 0.f }, FindFile("../resources/Particles/scorch_03.png"), sf::Color::Black },            false, false }},
			m_Fire         { Cast{ Rectangle{{ 100.f, 100.f }, { 0.f, 0.f }, FindFile("../resources/Particles/muzzle_05.png"), sf::Color { 240, 94, 35 }},    false, false }},
			m_Shield       { Cast{ Rectangle{{ 0.f,   0.f   }, { 0.f, 0.f }, FindFile("../resources/Particles/muzzle_05.png"), sf::Color::Transparent},       false, false }},
			m_Arcane	   { Cast{ Rectangle{{ 200.f, 200.f }, { 0.f, 0.f }, FindFile("../resources/Particles/light_03.png"),  sf::Color::Green},			  false, false }},

			m_Audio{false}
	{
		Init();
	}


	Mage::Mage(Mage&& other) noexcept {
		if (&other != this) {
			EventManager::GetInstance().RemoveEvent(other.m_KeyPressEvents);      // Removes the Mage's press events
			EventManager::GetInstance().RemoveEvent(other.m_KeyReleaseEvents);    // Removes the Mage's release events

			// Calls the parent's init function
			static_cast<Character*>(this)->Init(other.m_Filename, other.m_ImgCount, other.m_Size, other.m_Position, 
				other.m_Speed, other.m_JumpHeight, other.m_SwitchTime, other.m_SceneWidth);

			/* Moves all the mage's members */
			m_SceneWidth		 = std::move(other.m_SceneWidth);
			m_KeyPressEvents	 = std::move(other.m_KeyPressEvents);
			m_KeyReleaseEvents	 = std::move(other.m_KeyReleaseEvents);
			
			m_Thunder			 = std::move(other.m_Thunder);
			m_ThunderCloud		 = std::move(other.m_ThunderCloud);
			m_Fire				 = std::move(other.m_Fire);
			m_Shield			 = std::move(other.m_Shield);
			m_Arcane			 = std::move(other.m_Arcane);

			Init();
		}
	}

	Mage::~Mage() {
		//EventManager::GetInstance().RemoveEvent(m_KeyPressEvents);      // Removes the Mage's press events
		//EventManager::GetInstance().RemoveEvent(m_KeyReleaseEvents);    // Removes the Mage's release events
	}


	void Mage::Init() {
		// Cast animations
		m_Thunder.animation = {{ 3, 4 }, { 4, 4 }, { 5, 4 }, { 5, 4 }, { 5, 4 }};
		m_Fire.animation =    {{ 0, 3 }, { 1, 3 }, { 2, 3 }};
		m_Shield.animation =  RowFromIndex(5, 6);
		m_Arcane.animation =  {{ 5, 1 }, { 4, 2 }, { 4, 2 }, { 4, 2 }, { 4, 2 }};

		// Key Presses
		m_KeyPressEvents = KbEvent::MakeEvent(Type::KeyPressed, {
			// Q Pressed - Casts Thor's thunder
			KbEvent::KeyHook(KbEvent::Key::Q, [this] {
				// If the spell isn't on cooldown and nothing is casting
				if (!m_Cooldowns.IsOnCooldown(&m_Thunder) && !IsCasting()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(20));
					
					// Sets the cast animation
					SetCast(&m_Thunder);
					
					m_Audio.AddSound(FindFile("../resources/Sounds/Mage/thunder.wav"), 0.5f, Timer::Seconds(1));
					m_Cooldowns.AddAbility(&m_Thunder, 3.5f);
				}
			}),
			// W Pressed - Casts Surtur's fire
			KbEvent::KeyHook(KbEvent::Key::W, [this]{
				// If the spell isn't on cooldown and nothing is casting
				if (!m_Cooldowns.IsOnCooldown(&m_Fire) && !IsCasting()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(20));
					
					// Sets the cast animation
					SetCast(&m_Fire);

					m_Audio.AddSound(FindFile("../resources/Sounds/Mage/fire.wav"), 0.5f, Timer::MilliSeconds(200));			
					m_Cooldowns.AddAbility(&m_Fire, 2.0f);
				}
			}),
			// E Pressed - Casts Shield
			KbEvent::KeyHook(KbEvent::Key::E, [this]{
				// If the spell isn't on cooldown and nothing is casting
				if (!m_Cooldowns.IsOnCooldown(&m_Shield) && !IsCasting()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(20));

					SetCast(&m_Shield);

					// Adds 50 hp
					m_Health += 50.f;

					m_Audio.AddSound(FindFile("../resources/Sounds/Mage/heal.wav"), 0.5f);
					m_Cooldowns.AddAbility(&m_Shield, 10.f);
				}
			}),

			// R Pressed - Casts Arcane
			KbEvent::KeyHook(KbEvent::Key::R, [this]{
				// If the spell isn't on cooldown and nothing is casting
				if (!m_Cooldowns.IsOnCooldown(&m_Arcane) && !IsCasting()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(20));
					
					// Sets the arcane animation
					SetCast(&m_Arcane);
				
					m_Audio.AddSound(FindFile("../resources/Sounds/Mage/arcane.wav"), 5.f, Timer::MilliSeconds(750));
					m_Cooldowns.AddAbility(&m_Arcane, 15.f);
				}
			}),
			
			// Simulates dying
			KbEvent::KeyHook(KbEvent::Key::Escape, [this]{ 
				Hit(100.f); 
			}),
			
			// A Pressed - Moves Left
			KbEvent::KeyHook(KbEvent::Key::A, [this] {
				m_Velocity.x -= m_Speed;
				m_Animator->SetFacing(true);
			}),
			// D Pressed - Move Right
			KbEvent::KeyHook(KbEvent::Key::D, [this] {
				m_Velocity.x += m_Speed;
				m_Animator->SetFacing(false);
			}),
			// Space Pressed - Jump
			KbEvent::KeyHook(KbEvent::Key::Space, [this] {
				if (m_CanJump) {
					m_CanJump = false;
					m_Velocity.y = -std::sqrt(2.f * 982.f * m_JumpHeight);
				}
			})
		});
		
		// Key Releases
		m_KeyReleaseEvents = KbEvent::MakeEvent(Type::KeyReleased, {
			// A Released - Stop moving
			KbEvent::KeyHook(KbEvent::Key::A, [this] { 
				m_Velocity.x = 0.f; 
			}),
			// D Released - Stop moving
			KbEvent::KeyHook(KbEvent::Key::D, [this] { 
				m_Velocity.x = 0.f;
			})
		});

		EventManager::GetInstance().AddEvent(m_KeyPressEvents);
		EventManager::GetInstance().AddEvent(m_KeyReleaseEvents);

		SetIdle({{ 5, 2 }, { 6, 2 } });                                              // Sets the idle animation
		SetWalking(RowFromIndex(6, 6));                                              // Sets the walking animation
		SetJumping({{ 1, 1 }, { 2, 1 }});                                            // Sets the jumping animation
		SetDeath({ { 4, 1 }, { 5, 1 }, { 6, 1 }, { 6, 1 }, { 6, 1 }, { 6, 1 } });    // Sets the death animation
	}


	/*virtual*/ void Mage::Update(float deltaTime) /*override*/ {
		// Updates the cooldowns timers
		m_Cooldowns.Update(deltaTime);

		// Calls parent's implementation
		Character::Update(deltaTime);

		// If a cast animation is playing and arcane is casted, prepare arcane
		if (m_Arcane.isCasting) {
			m_Arcane.isRight = m_Animator->IsFacingLeft();
			m_Arcane.cast.SetPosition({ m_Body.getPosition().x - (m_Arcane.isRight ? -65.f : 65.f), m_Body.getPosition().y - 40 });
		}
		// Move the arcane
		else if (m_Arcane.isCasted) {
			// A vibration variable that makes it move up and down
			static float vibration = 3.f;

			m_Arcane.cast.Rotate(30.f);
			m_Arcane.cast.Move({ deltaTime * (m_Arcane.isRight ? -500.f : 500.f), (vibration *= -1) });
			if (m_Arcane.cast.GetPosition().x >= m_SceneWidth || m_Arcane.cast.GetPosition().x <= 0)
				m_Arcane.isCasted = false;
		}
	}


	/*virtual*/ void Mage::Draw(sf::RenderWindow& window) /*override*/ {		
		// Draws the thunder if thunder was previously casted but isn't casting
		if (m_Thunder.isCasted)
			m_Thunder.cast.Draw(window);
		
		// Draws a thunder cloud
		else if (m_Thunder.isCasting) {
			// Sets the cloud's position above the player
			m_ThunderCloud.isRight = m_Animator->IsFacingLeft();
			m_ThunderCloud.cast.SetPosition({ m_Body.getPosition().x, m_Body.getPosition().y - 200.f });
			m_ThunderCloud.cast.Draw(window);
		}

		// Draws the fire if the fire was previously casted but isn't casting
		if (m_Fire.isCasted)
			m_Fire.cast.Draw(window);

		// Draws the arcane if arcane was previously casted but isn't casting
		if (m_Arcane.isCasted)
			m_Arcane.cast.Draw(window);

		window.draw(m_Body);
	}


	void Mage::RemoveThunder(bool proc) {
		// If the ability procs, then it resets the cooldown
		if (proc)
			m_Cooldowns.RemoveAbility(&m_Thunder);
			
		m_Thunder.isCasted = false;
	}


	void Mage::RemoveFire(bool proc) {
		// If the ability procs, then it resets the cooldown
		if (proc)
			m_Cooldowns.RemoveAbility(&m_Fire);
		
		m_Fire.isCasted = false;
	}
}