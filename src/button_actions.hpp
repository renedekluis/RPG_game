#pragma once
#include <SFML\Graphics.hpp>

const struct {
	
	sf::Keyboard::Key Key;
	std::string name;
	float x; float y;
}actions[] = {
	{ sf::Keyboard::Left,	"walk_left",	-2,  0 },
	{ sf::Keyboard::Right,	"walk_right",	+2,  0 },
	{ sf::Keyboard::Up,		"walk_up",		 0, -2 },
	{ sf::Keyboard::Down,	"walk_down",	 0, +2 },

	{ sf::Keyboard::A,	"walk_left",	-2,  0 },
	{ sf::Keyboard::D,	"walk_right",	+2,  0 },
	{ sf::Keyboard::W,	"walk_up",		 0, -2 },
	{ sf::Keyboard::S,	"walk_down",	 0, +2 }
};

const struct {

	sf::Keyboard::Key Key;
	sf::Mouse::Button mouse_key;
	std::string name;

}skills[] = {
	{ 	sf::Keyboard::Space, 	sf::Mouse::Left,		"slash"			},
	{ 	sf::Keyboard::Right, 	sf::Mouse::Right,		"cast_spell"	},
	{ 	sf::Keyboard::F,		sf::Mouse::XButton1,	"shoot_arrow"	},
	{ 	sf::Keyboard::Down, 	sf::Mouse::XButton2,	"poke"			}
};


/// Convert a sf::vector2i to sf::Vector2f.
//
/// This method will convert a sf::Vector2i (a vector consisting 2 integer values), \n
/// to a sf::Vector2f (a vector consisting 2 float values). \n
/// 
///
/// Parameters:
/// -----------
/// vector : sf::Vector2f \n
///	-> Position to be converted.
/// 
///
/// Return:
/// -----------
/// Converted sf::Vector2i : sf::Vector2f \n
///	-> Converted vector2i.
///
///
/// Example:
/// --------
/// Vector2f_from_Vector2i({100 : int, 100 : int}) \n
/// -> {100 : float, 100 : float}
///
sf::Vector2f Vector2f_from_Vector2i(sf::Vector2i vector);


/// Check if skill button is pressed.
//
/// This method will check if one of the buttons in the defined struct of skill_buttons is pressed. \n
/// if that is the case, the method will return the name of the consisting skill. \n
/// 
///
/// Return:
/// -----------
/// skill_name : std::string \n
///	-> name of the skill button that is pressed.
///
///
/// Example:
/// --------
/// get_skill_from_button_keys() \n
/// -> "shoot_arrow"
///
std::string get_skill_from_button_keys();


/// Get the move direction if move button is pressed.
//
/// This method will check if one of the buttons in the defined struct of move action buttons is pressed. \n
/// if that is the case, the method will return the move direction of the consisting move. \n
/// 
///
/// Return:
/// -----------
/// direction : sf::Vector2f \n
///	-> Direction in which the player should move.\n
///
///
/// Example:
/// --------
/// get_move_direction_from_button_keys \n
/// -> {-1, 0}
///
sf::Vector2f get_move_direction_from_button_keys();


/// Get the name of a move if move button is pressed.
//
/// This method will return the name from a move if one of the buttons, \n
/// in the defined struct of move action buttons, is pressed. \n
/// 
///
/// Return:
/// -----------
/// direction : sf::Vector2f \n
///	-> Direction in which the player should move.\n
///
///
/// Example:
/// --------
/// get_action_name_from_button_keys() \n
/// -> "walk_up"
///
std::string get_action_name_from_button_keys();


/// Get the position of the mouse.
//
/// This method will return the position of the mouse on the window. \n
///
///
/// Parameters:
/// -----------
/// window : sf::RenderWindow&
/// -> window to check the mouse on.
/// 
///
/// Return:
/// -----------
/// mouse position : sf::Vector2f \n
///	-> Direction in which the player should move.\n
///
///
/// Example:
/// --------
/// get_mouse_position( window) \n
/// -> {100, 100}
///
sf::Vector2f get_mouse_position(sf::RenderWindow & window);


/// Check if left mouse button is pressed.
//
/// This method will check if the left mouse button is pressed. \n
/// If that is the case the function will return true. \n
/// 
///
/// Return:
/// -----------
/// button_pressed : bool \n
///	-> If the mousebutton is pressed.
///
///
/// Example:
/// --------
/// check_mouse() \n
/// -> true
///
bool check_mouse();


