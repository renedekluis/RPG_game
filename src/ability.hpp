#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>


class ability{
private:
	std::string name;
	std::vector<sf::Sprite>action;
	sf::Vector2f position;
	int current_action_step = 0;
	

public:

	/// Constructor
	//
	/// This method will crate an object of class ability.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// name : std::string \n
	///	-> name of the ability to be loaded.
	///
	/// action : std::vector<sf::Sprite> \n
	///	-> list of sprites that the animation of the ability needs.\n
	///
	/// position : sf::Vector2f \n
	///	-> position of the player, so the ability is loaded on that spot.
	/// 
	///
	/// Example:
	/// --------
	/// ability a("arno", {...}, {100,100})\n
	///
	ability(std::string name, std::vector<sf::Sprite> & action, sf::Vector2f position);


	/// Get the name of the ability
	//
	/// This method returns the name of the saved ability.\n
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
	/// "walk_up"\n
	///
	std::string get_name();


	/// Move the current ability
	//
	/// This method moves the position of the ability, \n
	/// so that the ability sprite is printed on the same position as the player or NPC.\n
	///
	///
	/// Parameters:
	/// -------
	/// new_position : sf::Vector2f\n
	/// -> new position of the ability sprite
	///
	///
	/// Example:
	/// --------
	/// move({200,200})\n
	/// ability position now set on 200, 200\n
	///
	void move( sf::Vector2f new_position);


	/// Print ability
	//
	/// This method draws the ability on the screen. \n
	/// Because there are likely multiple sprites in an ability, \n
	/// the sprite that have to be printed is handle by the current_action_step value. \n
	///
	///
	/// Parameters:
	/// -------
	/// window : sf::RenderWindow\n
	/// -> window where the ability have to be drawn on.\n
	///
	const void draw(sf::RenderWindow & window);


	/// Add a sprite to the action
	//
	/// This method will add a new sprite to the action. \n
	/// This method can be used if you think that the animation is not complete enough,\n
	/// and want to add an extra sprite to the animation.\n
	///
	///
	/// Parameters:
	/// -------
	/// t : sf::Sprite\n
	/// -> new sprite that will be added to the ability.
	///
	///
	/// Example:
	/// --------
	/// add_sprite_to_action(example_sprite)\n
	///
	void add_sprite_to_action(sf::Sprite t);


	/// Get list of sprites from an ability
	//
	/// This method returns a list that contains all sprites from the ability. \n
	///
	///
	/// Return:
	/// -------
	/// action : std::vector<sf::Sprite>\n
	/// -> List of sprites, containing the ability.
	///
	///
	/// Example:
	/// --------
	/// get_action()\n
	/// {sprite1,sprite2,sprite3}
	///
	std::vector<sf::Sprite> get_action();


	/// Skip to the next action step
	//
	/// This method moves the current_action_step to the next value. \n
	///
	///
	/// Example:
	/// --------
	/// current_action_step = 5\n
	/// next_step()\n
	/// current_action_step = 6\n
	///
	void next_step();


	/// Decontructor
	//
	/// Will be called when the object is deleted. \n
	/// 
	~ability();
};

