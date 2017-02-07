#pragma once


#include <iostream>
#include <SFML\Graphics.hpp>


class tile{
private:
	std::string tile_name;
	sf::Vector2f position;
	std::string path;
	sf::Texture texture;
	sf::Sprite sprite;
	
	void get_tile();
public:
	tile(sf::Vector2f position, std::string tile_name);
	~tile();
};

