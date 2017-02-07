#pragma once

#include "sql.hpp"

class item {
private:
	std::string id;
	sql & database;

	sf::Sprite sprite;
	sf::Texture texture;

public:

	/// Constructor
	//
	/// This method will crate an object of class item.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// id : std::string \n
	///	-> id of the item in the database.
	///
	/// database : sql& \n
	///	-> refference to the sqlite database.\n
	/// 
	///
	/// Example:
	/// --------
	/// item banana("1", database)\n
	///
	item(std::string id, sql & database);

	/// std::string get_name() : Get the name from an item
	//
	/// This function returns the name of an item by using its ID
	/// 
	/// Return:
	/// -------
	/// name : std::vector<std::string> \n
	///	-> The name of the requested item
	/// 
	/// Example:
	/// --------
	/// get_name() \n
	/// -> tokato_gloves
	///
	std::string get_name();

	/// std::string get_name() : Get the in game name from an item
	//
	/// This function returns the in game name of an item by using its ID
	/// 
	/// Return:
	/// -------
	/// name : std::vector<std::string> \n
	///	-> The in game name of the requested item
	/// 
	/// Example:
	/// --------
	/// get_in_game_name() \n
	/// -> Tokato Gloves
	///
	std::string get_in_game_name();

	/// std::string get_sprite() : Get the sprite from an item
	//
	/// This function returns the sprite of an item by using its ID
	/// 
	/// Return:
	/// -------
	/// sprite : sf::Sprite \n
	///	-> The sprite of the requested item
	/// 
	/// Example:
	/// --------
	/// get_sprite() \n
	/// -> sf::Sprite
	///
	sf::Sprite get_sprite(int counter);
};