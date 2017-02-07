#include "item.hpp"

item::item(std::string id, sql & database) :
	id(id),
	database(database)
{}

std::string item::get_name() {
	std::vector<std::string> name_vector = database.get_name_from_id_inventory(id);
	std::string name = name_vector.at(0);

	return name;
}

std::string item::get_in_game_name() {
	std::vector<std::string> in_game_name_vector = database.get_in_game_name_from_id_inventory(id);
	std::string name = in_game_name_vector.at(0);

	return name;
}

sf::Sprite item::get_sprite(int counter) {
	std::vector<std::string> sprite_vector = database.get_sprite_inventory(id);
	if (!texture.loadFromFile(sprite_vector.at(0))) { std::cout << "Error while loading sprite" << std::endl; }

	sprite.setTexture(texture);

	int y_counter = 1;

	if (counter % 4 == 0) {
		y_counter++;
	}
	//sprite.setPosition(362 + (50 * ((counter % 4) + 1)), 412);
	sprite.setPosition(362 + (50 * ((counter % 4) + 1)), 362 +  50 * y_counter);


	return sprite;
}