#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

class sprite{
private:
	sf::Sprite created_sprite;
	
public:
	sprite(sf::Vector2f position, sf::Texture texture);

	sf::FloatRect get_bounds();

	~sprite();
};

