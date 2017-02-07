
#include "exception_list.hpp"
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <functional>


std::ifstream & operator >> (std::ifstream & input, sf::Vector2f & rhs);

std::ifstream & operator >> (std::ifstream & input, char & rhs);

std::ifstream & operator >> (std::ifstream & input, std::string & rhs);
