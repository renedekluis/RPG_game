#ifndef _game_HPP
#define _game_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <functional>
#include "objects.hpp"
#include "dialogbox.hpp"
#include "button_actions.hpp"
#include "npc.hpp"
#include "player.hpp"
#include "leveleditor.hpp"
#include "inventory.hpp"

class game {
private:
	player arno;
	dialogbox dialogbox;
	sql & database;
	sf::RenderWindow & window;
	sf::View game_view;
	sf::View dialogbox_view;
	inventory inv;
	sf::Vector2f levelsize;
	std::vector<picture*> background_store;
	std::vector<npc*>npc_list;
	std::vector<sf::IntRect>collision_objects;
	std::vector<sf::IntRect>collision_backgrounds;
	std::map<std::string, std::vector<std::string>>background_values_map;
	std::map<std::string, std::vector<std::string>>object_values_map;
	std::map<std::string, std::vector<std::string>>begin_stories;

	bool game_begin = false;
	bool first_dialog_done = false;
	int count = 0;


	/// Checkt left edge of screen
	//
	/// This function checks if the mouse intersects with the left edge of the screen.\n
	///
	/// Parameters:
	/// -----------
	/// view : sf::View&\n
	///	-> The view is given with the function.
	///
	/// Example:
	/// --------
	/// mouse_intersects_left_edge(view1);
	///
	bool mouse_intersects_left_edge(sf::View & view);


	/// Checkt right edge of screen
	//
	/// This function checks if the mouse intersects with the right edge of the screen.\n
	///
	/// Parameters:
	/// -----------
	/// view : sf::View&\n
	///	-> The view is given with the function.
	///
	/// Example:
	/// --------
	/// mouse_intersects_right_edge(view1);
	///
	bool mouse_intersects_right_edge(sf::View & view);


	/// Checkt upper edge of screen
	//
	/// This function checks if the mouse intersects with the upper edge of the screen.\n
	///
	/// Parameters:
	/// -----------
	/// view : sf::View&\n
	///	-> The view is given with the function.
	///
	/// Example:
	/// --------
	/// mouse_intersects_upper_edge(view1);
	///
	bool mouse_intersects_upper_edge(sf::View & view);


	/// Checkt buttom edge of screen
	//
	/// This function checks if the mouse intersects with the down edge of the screen.\n
	///
	/// Parameters:
	/// -----------
	/// view : sf::View&\n
	///	-> The view is given with the function.
	///
	/// Example:
	/// --------
	/// mouse_intersects_down_edge(view1);
	///
	bool mouse_intersects_down_edge(sf::View & view);


	/// Activate game_viewr
	//
	/// This function is used to activate the game_viewer. \n
	///
	/// Example:
	/// --------
	/// game_viewer();
	///
	void game_viewer();

	/// Draw NPC's on the window
	//
	/// This function will go through a vector which contains NPC objects, 
	/// their draw function will be called on all of them one by one.\n
	///
	///
	/// Example:
	/// --------
	/// draw_npc() \n
	/// -> Drawing the NPC's on the window
	///
	void draw_npc();

	/// Get all the NPC's
	//
	/// This function will retrieve all the NPC's from the database and put them in the 'npc_list' vector.\n
	///
	///
	/// Example:
	/// --------
	/// load_npc() \n
	/// -> The npc_list vector will be filled with NPC objects from the database
	///
	void load_npc();

	/// Show beginning dialogues
	//
	/// This function shows the the dialogs that will be shown in the beginning of the game.\n
	///
	///
	/// Example:
	/// --------
	/// view_start_dialogs() \n
	/// -> Dialogues will be shown on the bottom of the screen
	///
	void view_start_dialogs();

	/// Show the store on the window
	//
	/// This function retrieves the background of the store from the vector it's in and displays it on the screen.\n
	///
	///
	/// Example:
	/// --------
	/// draw_background_store() \n
	/// -> The store will be shown on the window
	///
	void draw_background_store();

	/// Moves the player
	//
	/// This function will move the player as long as there's no collision. \n
	/// When there's a collision the player will be set back to its previous position before the collision.\n
	///
	///
	/// Example:
	/// --------
	/// move_player() \n
	/// -> Move the player
	///
	void move_player();

	/// Draws the player on the screen
	//
	/// This function calls the draw function from the 'player' class, 
	/// which will then draw the player on the screen.
	/// 
	///
	/// Example:
	/// --------
	/// move_player() \n
	/// -> Player will be shown on the screen
	///
	void draw_player();

	/// Show the sprite that belongs to the action
	//
	/// This function shows the action the belongs to the state of the player, \n
	/// if he walks up, the sprite will be shown of the player walking up. \n
	/// 
	///
	/// Parameters:
	/// -----------
	/// action : std::string\n
	///	-> The name of the action that must be performed
	///
	/// Example:
	/// --------
	/// perform_player_action("walk_up") \n
	/// - > The player will be shown doing something, like walking up, walking down or dying
	///
	void perform_player_action(std::string action);

	/// Show the sprite that belongs to the action.
	//
	/// This function shows the action the belongs to the state of the NPC, 
	/// if it walks up, the sprite will be shown of the NPC walking up.\n
	/// 
	///
	/// Parameters:
	/// -----------
	/// action : std::string\n
	///	-> The name of the action that must be performed.
	///
	/// npc_name : std::string\n
	///	-> The name of the NPC on which this function must be executed.
	///
	///
	/// Example:
	/// --------
	/// perform_npc_action("henk", "walk_up") \n
	/// - > The NPC will be shown doing something, like walking up, walking down or dying
	///
	void perform_npc_action(std::string npc_name, std::string action);


	/// Show action if action button pressed
	//
	/// This method will let the player perform a certain skill if the consisting button is pressed. \n
	/// The consisting keys and buttons are defined in button_actions.\n
	/// 
	///
	void player_skill();

	/// Interact with a NPC
	//
	/// Call the 'interact' function to see if the player can interact with a player.\n
	///
	///
	/// Example:
	/// --------
	/// player.interact() \n
	/// -> Executing the function which will show text on the screen
	///
	void interact();

	/// Interact with a object or tile
	//
	/// Call the 'interact' function to see if the player can interact with a player.\n
	/// 
	///
	/// Parameters:
	/// -----------
	/// item_name : std::string\n
	///	-> The name of an item which will be given to the player
	///
	///
	/// Example:
	/// --------
	/// player.interact("banana") \n
	/// - > Give the player an item and update this in the database
	///
	void interact(std::string item_id);

public:

	/// The constructor
	//
	/// The constructor of the 'game' class, this creates a game object.\n
	/// 
	///
	/// Parameters:
	/// -----------
	/// levelsize :  sf::Vector2f \n
	///	-> The size of the level
	/// 
	/// database : sql & \n
	///	-> A 'SQ' object, this will be used to get information from the database
	///
	/// window :sf::RenderWindow \n
	///	-> The window on which the game has to be drawn
	///
	///
	/// Example:
	/// --------
	/// game(window, database, levelsize) \n
	/// - > This will create a 'game' object
	///
	game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize);

	/// Loop that handles the game
	//
	/// This funtion will execute everything that will be needed to run the game, \n
	/// like drawing the window, loading the NPC's and working with them
	/// 
	///
	/// Example:
	/// --------
	/// game_loop() \n
	/// - > This will start the game
	///
	void game_loop();

	/// Get the items from the database
	//
	/// This function gets all the items from the database and places it in a std::map.\n
	/// 
	///
	/// Parameters:
	/// -----------
	/// item_values_map :  std::map<std::string, std::vector<std::string>> & \n
	///	-> The map that contains all the items and its location
	///
	///
	/// Example:
	/// --------
	/// get_items_from_database(background_values_map) \n
	/// - > The std::map will be filled with the items
	///
	void get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map);
};

#endif
