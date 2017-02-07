#ifndef _leveleditor_HPP
#define _leveleditor_HPP

#include "objects.hpp"
#include "dialogbox.hpp"
#include <functional>
#include <sstream>
#include <fstream>
#include "sql.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:

	/// Template function for bool
	//
	/// This method will create a boolean function with a specified use. \n 
	///
	action(std::function< bool() > condition, std::function< void() > work) :
		condition(condition),
		work(work)
	{}


	/// Template function for void
	//
	/// This method will create a void function with a specified use. \n 
	///
	action(std::function< void() > work) :
		condition([]()->bool {return true; }),
		work(work)
	{}


	/// Template function for key pressing
	//
	/// This method will create a boolean function with a specified use. \n
	/// And returns if a specified key is pressed. \n
	///
	action(sf::Keyboard::Key key, std::function< void() > work) :
		condition([key]()->bool { return sf::Keyboard::isKeyPressed(key); }),
		work(work)
	{}


	/// Template function for mouse button
	//
	/// This method will create a boolean function with a specified use. \n
	/// And returns if a specified mouse button is pressed. \n
	///
	action(sf::Mouse::Button button, std::function< void() > work) :
		condition([button]()->bool { return sf::Mouse::isButtonPressed(button); }),
		work(work)
	{}


	/// Overloader for operator()()
	//
	/// This method creates the operator()() so it can be used in this class. \n
	///
	void operator()() {
		if (condition()) {
			work();
		}
	}
};

class leveleditor {
private:
	sf::Vector2f levelsize = { 0,0 };
	sf::Vector2f rect_size = { 0,0 };
	std::vector<figure*> rectangle_store;
	std::vector<picture*> background_store;
	std::vector<picture*> tile_store;
	std::vector<picture*> temporary_store;
	std::vector<dialogbox*> level_buttons;

	std::vector<std::string>level_ids;
	std::map<std::string, std::vector<std::string>>background_values_map;
	std::map<std::string, std::vector<std::string>>object_values_map;
	std::string active_level;

	sf::RenderWindow & window;
	sql & database;
	picture back_to_menu_button;
	picture save_level_button;
	picture new_game_button;
	picture load_game_button;
	bool pressed_esc = true;
	bool pressed_load_game = false;

	action actions[12] = {
		action(sf::Keyboard::Left,  [&]() {view1.move(-16, 0); }),
		action(sf::Keyboard::Right, [&]() {view1.move(16, 0); }),
		action(sf::Keyboard::Up,    [&]() {view1.move(0, -32); }),
		action(sf::Keyboard::Down,  [&]() {view1.move(0, 32); }),
		action(sf::Keyboard::Z,     [&]() {view1.zoom(0.9f); }),
		action(sf::Keyboard::X,		[&]() {view1.zoom(1.1f); }),
		action(sf::Mouse::Left,     [&]() {if (is_object_under_mouse(rectangle_store, view1)) { create_object(get_position_from_rectangle_under_mouse()); } }),
		action(sf::Mouse::Left,		[&]() {if (is_object_under_mouse(tile_store, view2)) { set_selected(); } }),
		action(sf::Keyboard::S,		[&]() {view2.move(0,5); }),
		action(sf::Keyboard::W,		[&]() {view2.move(0,-5); }),
		action(sf::Keyboard::C,     [&]() {remove_object_under_mouse(); }),
		action(sf::Keyboard::BackSpace, [&]() {remove_last_object(); })
	};


	/// Check if a button is pressed at the given view.
	// 
	/// Parameters:
	/// -----------
	/// object : dialogbox& \n
	///	-> A dialog object.
	///
	/// view : view& \n
	///	-> A view.
	///
	/// Return:
	/// -------
	/// bool : bool \n
	///	-> returns true if left mouse button is pressed on the given dialogbox.
	/// 
	/// Example:
	/// --------
	/// Get_data(dialogbox, view1) \n
	/// return: {true}.
	///
	bool button_pressed(dialogbox & object, sf::View & view);


	/// Get data from the database by giving a map.
	// 
	/// Parameters:
	/// -----------
	/// map vector : std::map<std::string, std::vector<std::string>>& \n
	///	-> a map vector which contains a string with all the database values. 
	///
	/// Return:
	/// -------
	/// vector : std::vector<object> \n
	///	-> returns a vector with all the objects from the database.
	/// 
	/// Example:
	/// --------
	/// get_items_from_database(object_map) \n
	/// -> item_map is now filled with objects.
	///
	void get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map);
	
	
	/// This function loads all background rectangles in the background vector.
	//
	/// This method will fill the rectangle_store with rectangles.
	///
	void load_rectangles();
	
	
	/// This method loads all tiles which can be choosen at the right side of the level editor.
	//
	/// This method will fill the tile_store with objects.
	///
	void load_tile_list();
	
	
	///Set a object from the tile list as selected when there is clicked on it.
	//
	/// This method is used in the code to be able to switch between objects.
	///
	void set_selected();
	
	
	/// Removes the last object from the temporary store.
	//
	/// This function removes the last object from the temporary store.
	///
	void remove_last_object();
	
	
	/// This function removes the object under the mouse by pressing c.
	//
	/// Return:
	/// -------
	/// bool : bool \n
	///	-> returns a bool.
	/// 
	///
	/// Example:
	/// --------
	/// remove_object_under_mouse()
	/// -> true
	///
	bool remove_object_under_mouse();
	
	
	/// Creates an object which is selected at the given position.
	//
	/// Parameters:
	/// -----------
	/// position : sf::Vector2f
	///	-> position for object
	///
	///
	/// Example:
	/// --------
	/// Create_object({100,50})
	/// Creates a selected object at position {100,50}.
	///
	void create_object(sf::Vector2f position);
	
	
	/// Converts a mouse position to map coords on the given view.
	//
	/// Parameters:
	/// -----------
	/// view : sf::View& \n
	///	-> view of the editor
	///
	///
	/// Return:
	/// -------
	/// vector : sf::Vector2f \n
	///	-> A vector converted to mapcoords.
	/// 
	///
	/// Example:
	/// --------
	/// convert_to_coords(view1);
	/// -> (256,596)
	///
	sf::Vector2f convert_to_coords(sf::View & view);
	
	
	///Get the position of the rectangle from rectangle store under the mouse.
	//
	/// Return:
	/// -------
	/// position : sf::Vector2f \n
	///	-> A vector2f position.
	/// 
	/// Example:
	/// --------
	/// get_position_from_rectangle_under_mouse() \n
	/// -> (234,262)
	///
	sf::Vector2f get_position_from_rectangle_under_mouse();

	
	///Check if a picture object is under the mouse.
	//
	/// Parameters:
	/// -----------
	/// vector : std::vector<picture*>& \n
	///	-> Give a picture vector with the function.
	///
	/// view : sf::View \n
	///	-> Give a view with the function.
	///
	/// Return:
	/// -------
	/// picture_under_mouse : bool \n
	///	-> Returns true if the mouse is on a object. \n
	/// 
	/// Example:
	/// --------
	/// is_object_under_mouse(picture_vector, view1) \n
	/// -> true
	///
	bool is_object_under_mouse(std::vector<picture*> & vector, sf::View & view);
	
	
	///Check if a figure object is under the mouse.
	//
	/// Parameters:
	/// -----------
	/// vector : std::vector<picture*>& \n
	///	-> Give a figure vector with the function. \n
	///
	/// view : sf::View \n
	///	-> Give a view with the function. \n
	///
	///
	/// Return:
	/// -------
	/// figure_under_mouse : bool \n
	///	-> Returns true if the mouse is on a object. \n
	/// 
	///
	/// Example:
	/// --------
	/// is_object_under_mouse(figure_vector, view2) \n
	/// -> true \n
	///
	bool is_object_under_mouse(std::vector<figure*> & vector, sf::View & view);
	
	
	/// Check if a button is pressed at the given view. 
	// 
	/// Parameters:
	/// -----------
	/// object : 'picture& \n
	///	-> A picture object. \n
	///
	/// view : view& \n
	///	-> A view. \n
	///
	/// Return:
	/// -------
	/// button_pressed : bool \n
	///	-> returns true if left mouse button is pressed on the given picture. \n
	/// 
	/// Example:
	/// --------
	/// Get_data(picture, view1) \n
	/// -> true \n
	///
	bool is_button_pressed(picture & object, sf::View & view);
	
	
	/// Looks if a menu button is pressed.
	//
	/// Return:
	/// -------
	/// back_to_menu_button_pressed : bool \n
	///	-> returns true if the back to menu button is pressed.  \n
	/// sets other variables in the hpp on true or false if a button is pressed. \n
	///
	/// Example:
	/// --------
	/// menu_options() \n
	/// -> true \n
	///
	bool menu_options();


public:
	sf::View view1;
	sf::View view2;
	sf::View view3;
	sf::View view4;

	/// Constructor
	//
	/// This will create a leveleditor object. \n
	//
	/// Parameters:
	/// -----------
	/// levelsize : sf::Vector2f \n
	///	-> Give the levelsize with the function.  \n
	///
	/// tilesize : sf::Vector2f \n
	///	-> Give the tilesize with the function. \n
	///
	/// window : sf::RenderWindow& \n
	///	-> Give a window with the function where the leveleditor needs to be drawn at.  \n
	///
	/// database : sql& \n
	///	-> Give the database to the function.\n
	///
	/// Example:
	/// --------
	/// leveleditor({1080,1080}, {32,32}, window, database); \n
	///
	leveleditor(sf::Vector2f levelsize, sf::Vector2f tilesize, sf::RenderWindow & window, sql & database);


	/// The main loop for the editor to stay working.
	//
	/// Example:
	/// --------
	/// editor_loop(); \n
	///
	void editor_loop();
	
	
	/// Loop through the actions in the action class.
	//
	///
	void get_actions();
	
	
	/// Draw the rectangle store on the screen.
	//
	/// Example:
	/// --------
	/// draw_rectangle_store() \n
	/// rectangle_store is now drawn on the screen. \n
	///
	void draw_rectangle_store();
	
	
	/// Draw the background store.
	//
	/// Example:
	/// --------
	/// draw_background_store() \n
	/// background_store is now drawn on the screen. \n
	///
	void draw_background_store();
	
	
	/// Draw the tile store.
	//
	/// Example:
	/// --------
	/// draw_tile_store() \n
	/// Draw the objects from the tile_store. \n
	///
	void draw_tile_store();
	
	
	/// Draw the temporary store.
	//
	/// Example:
	/// --------
	/// draw_temporary_store() \n
	/// Draw the objects from the temporary_store. \n
	///
	void draw_temporary_store();
};

#endif
