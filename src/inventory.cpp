#include "inventory.hpp"

inventory::inventory(sf::RenderWindow & window, sql & database) :
	window(window),
	database(database)
{}

void inventory::get_inventory() {
	std::vector<std::string> inventory_string = database.get_inventory();

	std::cout << "Getting inventory 1" << std::endl;
	for (auto id : inventory_string) {
		inventory_vector.push_back(item(id, database));
	}

	if (!inventory_texture.loadFromFile("../../bin/objects/inventory.png")) { std::cout << "Error while loading sprite" << std::endl; }
	inventory_sprite.setTexture(inventory_texture);
	inventory_sprite.setPosition(412, 412);
	window.draw(inventory_sprite);
	std::cout << "Getting inventory 2" << std::endl;

	for (auto item : inventory_vector) {
		//std::cout << item.get_in_game_name() << std::endl;
		window.draw(item.get_sprite(counter));
		counter++;
		std::cout << "Getting inventory 2:" << counter << std::endl;

	}
	counter = 1;
}