#include "sprite.hpp"



sprite::sprite(sf::Vector2f position, sf::Texture texture){
	created_sprite.setTexture(texture);
	created_sprite.setPosition(position);
}

sf::FloatRect sprite::get_bounds() {
	return created_sprite.getGlobalBounds();
}


sprite::~sprite(){}
