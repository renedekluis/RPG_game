#ifndef _dialogbox_HPP
#define _dialogbox_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "objects.hpp"

class dialogbox{
private:
	sf::Font font;
	std::string font_path;
	sf::Vector2f position;
	picture box;

public:
	std::string last_text;
	sf::Text text;


	/// Constructor.
	// 
	/// This method will create a object of this class.
	///
	///
	/// Parameters:
	/// -----------
	/// box path : std::string \n
	///	-> The path which contains the background of the dialogbox. \n
	///
	/// font_path : std::string \n
	///	-> The path which contains font of the text in the dialogbox. \n
	///
	/// position : sf::vector2f \n
	///	-> This is the position of the dialogbox on the screen. \n
	///
	/// Example:
	/// --------
	/// dialogbox d("background.png", "font.ttf", {200, 800});
	///
	dialogbox(std::string box_path, std::string font_path, sf::Vector2f position);
	
	
	/// Draw the dialogbox
	//
	/// This method draws the dialogbox on the screen.
	///
	///
	/// Parameters:
	/// -----------
	/// window : sf::RenderWindow& \n
	///	-> The window where the dialogbox is shown on. \n
	///
	///
	/// Example:
	/// --------
	/// dialogbox.draw(window);
	///
	void draw(sf::RenderWindow & window);
	
	
	/// Set text in the dialogbox.
	// 
	/// This method sets a given text in a dialogbox. \n
	/// Also is the font size given and in what color the text should appear. \n
	///
	///
	/// Parameters:
	/// -----------
	/// sentence : std::string \n
	///	-> The sentence which is shown in the dialogbox. 
	///
	/// char_size : int \n
	///	-> The size of the characters in the dialogbox. 
	///
	/// color : sf::Color \n
	///	-> The color of the text. 
	///
	///
	/// Example:
	/// --------
	/// text_input("hey", 30, sf::Color::Red);
	///
	void text_input(std::string sentence, int char_size, sf::Color color);
	
	
	/// Get bounds of dialogbox
	//
	/// This method will return the boundary of the text in the dialogbox.
	///
	/// Return:
	/// -------
	/// sf::FloatRect : sf::FloatRect
	///	-> The boundary of the text in the dialogbox.
	/// 
	///
	/// Example:
	/// --------
	/// getBounds();
	/// -> (100,100,50,50)
	///
	sf::FloatRect getBounds();
	
};

#endif
