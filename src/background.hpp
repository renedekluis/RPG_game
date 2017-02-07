#pragma once
#include <fstream>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "exception_list.hpp"
#include "file_reading_operators.hpp"
#include "background.hpp"

//#include "exception_list.hpp"
//#include "file_reading_operators.hpp"

class background{
private:
	std::string level_name;
	std::ifstream input;
	std::string background_file_path;
	std::vector<sf::Sprite>background_tile_list;
	sf::Texture texture;
	sf::Sprite sprite;

	//functions
	sf::Sprite read_background(std::ifstream & input);

public:
	background(std::string background_file_path);
	void save();
	void draw(sf::RenderWindow & window);
	~background();
};

