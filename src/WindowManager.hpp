#pragma once

#include <SFML/Graphics.hpp>
#include <memory>


namespace Veri { namespace WindowMananger {
	sf::RenderWindow& CreateWindow(sf::VideoMode const& vm, std::string const& title);
	sf::RenderWindow& GetWindow();
}}