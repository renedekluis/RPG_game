#pragma once

#include "item.hpp"
#include <iostream>
#include "SFML/Graphics.hpp"
#include "sql.hpp"


class inventory {
private:
	sf::RenderWindow & window;
	sql & database;
	std::vector<item> inventory_vector;

	int counter = 1;

	sf::Sprite inventory_sprite;
	sf::Texture inventory_texture;

public:


	/// Constructor
	//
	/// This method will crate an object of class inventory.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// window : sf::Renderwindow& \n
	///	-> window the inventory hs to be drawn one.
	///
	/// database : sql& \n
	///	-> refference to the sqlite database.\n
	/// 
	///
	/// Example:
	/// --------
	/// inventory inv(window, database)\n
	///
	inventory(sf::RenderWindow & window, sql & database);

	/// void get_inventory() : Get the inventory
	//
	/// This function returns the items in the inventory
	/// 
	/// Example:
	/// --------
	/// get_inventory(1) \n
	/// -> Shows the items in the inventory
	///
	void get_inventory();
};