#include "file_reading_operators.hpp"


std::ifstream & operator >> (std::ifstream & input, sf::Vector2f & rhs) {
	char c;
	if (!(input >> c)) { throw end_of_file(); }
	
	while (c == '\n' || c == ' ') {
		c = input.get();
		if (c == EOF) { throw end_of_file(); }
	}
	
	if (c != '(') { throw invalid_position(c); }

	if (!(input >> rhs.x)) { throw invalid_position(c); }

	if (!(input >> c)) { throw invalid_position(c); }

	if (!(input >> rhs.y)) { throw invalid_position(c); }

	if (!(input >> c)) { throw invalid_position(c); }

	if (c != ')') { throw invalid_position(c); }

	return input;
}

std::ifstream & operator >> (std::ifstream & input, char & rhs) {
	rhs = input.get();
	return input;
}


std::ifstream & operator >> (std::ifstream & input, std::string & rhs) {
	char c;
	rhs = "";
	for (;;) {
		c = input.get();
		if (c == '\0' || c == '\n' || c == ' ' || c == EOF) {
			if (rhs != "") {
				break;
			}
		}
		else if (c != '\r') {
			rhs += c;
		}
	}
	return input;
}
