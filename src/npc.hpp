#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "ability.hpp"
#include "sql.hpp"


class npc{
private:
	std::vector<ability*>npc_actions;
	std::vector<std::string>npc_values;
	std::string id;
	sf::Vector2f position;
	
	sql & database;

	int sprite_size = 64;
	sf::Texture texture;
	sf::RenderWindow & window;
	std::string current_action = "walk_down";
	
	bool is_player = false;


	/// Load all abilities
	//
	/// This method will load all abilities of an NPC sprite sheet.\n
	///
	void load_all_actions();
	
	
	/// Load a npc ability
	//
	/// This method will load one ability of an NPC sprite sheet.\n
	/// This ability has a certain ammount of steps and stands on a certain level in the sprite sheet.\n
	///
	/// Parameters:
	/// -----------
	/// action_name : std::string\n
	/// -> name of the ability to load
	///
	/// steps_of_action : int \n
	/// -> ammount of steps of the ability. \n
	///
	void load_action(std::string action_name, int steps_of_action, int level);
	
public:
	
	/// Constructor
	//
	/// This method will crate an object of class npc.\n
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
	/// npc_id : sf::string \n
	///	-> id of the npc that has to be drawn.
	/// 
	/// is_player : bool \n
	///	-> boolean to select if this npc is the player or not.
	/// 
	///
	/// Example:
	/// --------
	/// ability a(window, database, "1")\n
	///
	npc(sf::RenderWindow & window, sql & database, std::string npc_id, bool is_player = false);
	
	/// Move the npc
	//
	/// This method moves the position an npc.\n
	///
	///
	/// Parameters:
	/// -------
	/// delta : sf::Vector2f\n
	/// -> new position of the npc.
	///
	///
	/// Example:
	/// --------
	/// move({2,0})\n
	/// npc has moved 2 pixels to the right\n
	///
	void move(sf::Vector2f delta);
	
	/// set action of npc
	//
	/// This method sets the current action of the npc.\n
	/// The standard value is walk down.\n
	///
	///
	/// Parameters:
	/// -------
	/// s : std::string\n
	/// -> name of the action that has to be set on active.
	///
	///
	/// Example:
	/// --------
	/// set_action("walk_up")\n
	/// npc is now set for walking up.\n
	///
	void set_action(std::string s = "0");
	
	/// Get the name of npc
	//
	/// This method returns the name of an npc.\n
	///
	///
	/// Return:
	/// -------
	/// name : std::String\n
	/// -> name of the ability
	///
	///
	/// Example:
	/// --------
	/// get_name()\n
	/// "monk"\n
	///
	std::string get_name();

	/// void draw() : Print NPC
	//
	/// This method draws the NPC on the screen. \n
	///
	/// Example:
	/// --------
	/// draw()\n
	/// -> Draw the NPC on the screen
	///
	const void draw();

	/// Get a bounds from a NPC
	//
	/// This function returns a sf::IntRect object which is created from the position and size of the NPC object.\n
	/// 
	/// Return:
	/// -------
	/// intrect_object : sf::IntRect \n
	///	-> a sf::IntRect object using the position and size of the NPC object
	/// 
	/// Example:
	/// --------
	/// get_bounds() \n
	/// return: sf::IntRect(100, 100, 30, 30) .
	///
	sf::IntRect get_bounds();

	/// Get interaction two NPC's
	//
	/// Call the 'get_interaction' function to check for a collision with another NPC.
	/// 
	/// Parameters:
	/// -----------
	/// other_npc : NPC & \n
	///	-> The NPC that will be check for a collision.
	///
	/// Return:
	/// -------
	/// 0 / 1 : integer \n
	///	-> Return a 1 if there's a collision detected, return a 0 if no collision is detected.
	/// 
	/// Example:
	/// --------
	/// get_interaction(*other_npc) \n
	/// -> return: {"1"}.
	///
	int get_interaction(npc & other_npc);



	/// Get interaction NPC and object.
	//
	/// Call the 'get_collision' function to check for a collision with a sf::IntRect object.\n
	/// 
	/// Parameters:
	/// -----------
	/// colliding_object : sf::IntRect \n
	///	-> The sf::IntRect that will be check for a collision.\n
	///
	/// Return:
	/// -------
	/// 0 / 1 : integer \n
	///	-> Return a 1 if there's a collision detected, return a 0 if no collision is detected.\n
	/// 
	/// Example:
	/// --------
	/// npc.get_collision(recangle) \n
	/// return: {"1"}.
	///
	int get_collision(sf::IntRect colliding_object);



	/// Get position of NPC
	//
	/// When this function is called, it will return the position of the NPC.\n
	/// 
	/// Return:
	/// -------
	/// position : sf::Vector2f \n
	///	-> The position of the NPC
	/// 
	/// Example:
	/// --------
	/// get_position() \n
	/// -> return sf::Vector(200,200)
	///
	void set_position(sf::Vector2f given_position);

	/// Get position of NPC
	//
	/// When this function is called, it will return the position of the NPC.
	/// 
	/// Return:
	/// -------
	/// position : sf::Vector2f \n
	///	-> The position of the NPC
	/// 
	/// Example:
	/// --------
	/// get_position() \n
	/// -> return sf::Vector(200,200)
	sf::Vector2f get_position() { return position; }


	/// Get NPC action
	//
	/// This function return a list of sprites that is asked from the NPC. \n
	/// 
	///
	/// Parameters:
	/// -----------
	/// action_to_perform : std::string \n
	///	-> The action that has to be shown.
	///
	///
	/// Return:
	/// -----------
	/// temp : std::vector<sf::Sprite> \n
	///	-> list of sprites containing the sprites of an ability.
	///
	///
	/// Example:
	/// --------
	/// get_action("walk_up") \n
	/// -> {sprite1,sprite2,....}
	///
	std::vector<sf::Sprite> npc::get_action(std::string action_to_get);


	/// Get current action of NPC
	//
	/// This function returns the name of the current action of a NPC. \n
	/// This is the action that the NPC is currently performing in the game.\n
	/// 
	///
	/// Return:
	/// -----------
	/// current_action : std::string \n
	///	-> Name of the current action from NPC.
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
	/// -> NPC will shoot an arrow northwards.
	///
	void show_ability(std::string action_to_show);


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~npc();
};

