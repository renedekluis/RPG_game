#ifndef _main_menu_HPP
#define _main_menu_HPP

#include "objects.hpp"

class main_menu {
private:
	sf::RenderWindow & window;
	picture background;

	void draw_main_menu();

public:
	sf::View view1;
	sf::View view2;
	picture level_editor_button;
	picture play_game_button;
	picture load_screen_pic;
	picture gid_gud;


	/// Constructor
	//
	/// This method will crate an object of class main_menu.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// window : sf::RenderWindow& \n
	///	-> refference to the SFML window.\n
	/// 
	///
	/// Example:
	/// --------
	/// main_menu m(window)\n
	///
	main_menu(sf::RenderWindow & window);


	/// Show menu
	//
	/// This method shows the menu.\n
	///
	/// Example:
	/// --------
	/// show_menu() \n
	/// -> You can now see the menu
	///
	void show_menu();


	/// Ceck if a button is pressed
	//
	/// This method return a boolean if a menu button is pressed with the mouse or not.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// object : picture& \n
	///	-> refference to picture class object "object".\n
	///
	/// view : sf::View& \n
	/// -> view where the mouse click is checked on.\n
	/// 
	///
	/// Return:
	/// -------
	/// button pressed : bool
	/// -> button pressed with mouse
	///
	///
	/// Example:
	/// --------
	/// button_pressed(play_game, menu_view)\n
	/// -> true
	///
	bool button_pressed(picture & object, sf::View & view);
	
	
	/// Load the load screen
	//
	/// This method will start a small loop, \n
	/// that smoothly change the main_menu to the load screen. \n
	///
	void load_screen();
	
	
	/// Creater screen
	//
	/// This method will start the advertisement screen from the creators of the game. \n
	///
	void gid_gud_splash();
	
	
	/// start the load screen
	//
	/// This method will start draw the loadscreen pic. \n
	/// This is so that the player does not only see a black screen while waiting. \n
	///
	void loading();

};

#endif
