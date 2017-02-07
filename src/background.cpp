#include "background.hpp"


background::background(std::string background_file_path) :
	background_file_path(background_file_path)
{
	input.open(background_file_path);
	if (!input.is_open()) {
		throw unknown_tile(background_file_path);
	}

	try {
		input >> level_name;
		for (;;) {
			background_tile_list.push_back(read_background(input));
		} 
	} catch (end_of_file) {
		std::cout << "end of file reached";
		//continue
	}
	catch (std::exception & problem) {
		std::cout << problem.what();
	}
}

void background::draw(sf::RenderWindow & window) {
	for (auto tile : background_tile_list) {
			window.draw(tile);
	}
	
}


sf::Sprite background::read_background(std::ifstream & input) {
	sf::Vector2f position;
	std::string tile_path;
	int sprite_size;
	
	input >> position >> tile_path >> sprite_size;
	std::cout << "(" << position.x << "," << position.y << ") " << tile_path << " " << sprite_size << " " << sprite_size << "\n";
	//if (tile_path != "../../tiles/grass.png") {
		texture.loadFromFile(tile_path, sf::IntRect(0, 0, sprite_size, sprite_size));
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setPosition(position.x, position.y);
	//}
	return sprite;
	
}


void background::save() {
	std::ofstream output(background_file_path);
	/*
	for (auto tile : background_tile_list) {
		output << tile.iets();
		output << "\n";
	}
	*/
	output.close();
}


background::~background()
{
}
