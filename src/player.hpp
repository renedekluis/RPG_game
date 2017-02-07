#pragma once

#include <iostream>
#include <npc.hpp>


class player{
private:
	npc player_npc;
	std::string player_id;
	sf::Vector2f spawn;
	sf::Vector2f position;
	sf::Vector2f last_move;
	sql database;

public:

	/// Constructor
	//
	/// This method will create an object of class npc.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// window : sf::RenderWindow \n
	///	-> window where content will be drawn on.
	///
	/// database : sql \n
	///	-> referrence to the database class.\n
	///
	/// save : sf::string \n
	///	-> id of the current game save.
	/// 
	///
	/// Example:
	/// --------
	/// player a(window, database, "1")\n
	///
	player(sf::RenderWindow & window, sql & database, std::string save);


	/// void move() : Move the player
	//
	/// This method moves the position the player.\n
	///
	///
	/// Parameters:
	/// ------------
	/// delta : sf::Vector2f\n
	/// -> new position of the player.
	///
	///
	/// Example:
	/// --------
	/// move({2,0})\n
	/// player has moved 2 pixels to the right\n
	///
	void move(sf::Vector2f delta);


	/// void set_action(std::string s) : Set action of the player
	//
	/// This method sets the current action of the player.\n
	/// The standard value is walk down.\n
	///
	///
	/// Parameters:
	/// -------
	/// s : std::string\n
	/// -> name of the action that has to be set on active.
	///
	/// Example:
	/// --------
	/// set_action("walk_up")\n
	/// -> Player is now set for walking up.\n
	///
	void set_action(std::string s);

	/// void draw() : Print player
	//
	/// This method draws the player on the screen. \n
	///
	/// Example:
	/// --------
	/// draw()\n
	/// -> Draw the player on the screen
	///
	void draw();

	/// void respawn() : Respawn player
	//
	/// This method moves the player back to a specific location \n
	///
	/// Example:
	/// --------
	/// respawn()\n
	/// -> Player will be moved back to (200,200)
	///
	void respawn();

	/// int npc::get_interaction(npc & other_npc) : Get interaction between the player and a NPC
	//
	/// Call the 'get_interaction' function to check for a collision between the player and a NPC
	/// 
	/// Parameters:
	/// -----------
	/// other_npc : NPC & \n
	///	-> The NPC that will be checked with for a collision
	///
	/// Return:
	/// -------
	/// 0 / 1 : integer \n
	///	-> Return a 1 if there's a collision detected, return a 0 if no collision is detected
	/// 
	/// Example:
	/// --------
	/// get_interaction(*other_npc) \n
	/// -> return: {"1"}.
	///
	int get_interaction(npc & other_npc);

	/// int get_collision(sf::IntRect colliding_object) : Get interaction between a NPC and a sf::IntRect object
	//
	/// Call the 'get_collision' function to check for a collision with a sf::IntRect object
	/// 
	/// Parameters:
	/// -----------
	/// colliding_object : sf::IntRect \n
	///	-> The sf::IntRect that will be check for a collision
	///
	/// Return:
	/// -------
	/// 0 / 1 : integer \n
	///	-> Return a 1 if there's a collision detected, return a 0 if no collision is detected
	/// 
	/// Example:
	/// --------
	/// get_collision(recangle) \n
	/// -> return: {"1"}.
	///
	int get_collision(sf::IntRect colliding_object);

	/// void set_last_position() : Set the position back to its last position
	//
	/// When this function is called, the current location will be set to last location
	/// 
	/// Example:
	/// --------
	/// set_last_position() \n
	///  -> The position is now set to the last position
	///
	void set_last_position();

	/// sf::Vector2f get_position() : Get position of player
	//
	/// When this function is called, it will return the position of the player
	/// 
	/// Return:
	/// -------
	/// position : sf::Vector2f \n
	///	-> The position of the player
	/// 
	///
	/// Example:
	/// --------
	/// get_position() \n
	/// -> return sf::Vector(200,200)
	///
	sf::Vector2f get_position();

	/// void show_action(std::string action_to_perform) : Player acion
	//
	/// This function displays the right action of the player, so the right spritepart that displays the current action of the player, like walking up
	/// 
	/// Parameters:
	/// -----------
	/// action_to_perform : std::string \n
	///	-> The action that has to be shown
	///
	/// Example:
	/// --------
	/// show_action("walk_up") \n
	/// -> Now the player seems to be walking up
	///
	std::vector<sf::Sprite> get_action(std::string action_to_get);

	/// Get current action the player
	//
	/// This function returns the name of the current action of the player. \n
	/// This is the action that the player is currently performing in the game.\n
	/// 
	///
	/// Return:
	/// -----------
	/// current_action : std::string \n
	///	-> Name of the current action from the player.
	///
	///
	/// Example:
	/// --------
	/// get_current_action() \n
	/// -> "walk_up"
	///
	std::string get_current_action();


	/// Perform an action.
	//
	/// This function shows one step of the asked ability. \n
	/// This function has to be called in a loop that stops at the max size of the ability list. \n
	/// 
	///
	/// Parameters:
	/// -----------
	/// action_to_show : std::string \n
	///	-> Name of action.
	///
	///
	/// Example:
	/// --------
	/// show_ability("shoot_arrow_up") \n
	/// -> the player will shoot an arrow northwards.
	///
	void show_ability(std::string action_to_show);


	/// Get position of the player
	//
	/// When this function is called, it will return the position of the player.\n
	/// 
	/// Return:
	/// -------
	/// position : sf::Vector2f \n
	///	-> The position of the player
	/// 
	/// Example:
	/// --------
	/// get_position() \n
	/// -> return sf::Vector(200,200)
	///
	void set_position(sf::Vector2f new_position);


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~player();
};

