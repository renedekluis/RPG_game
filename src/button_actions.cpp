#include "button_actions.hpp"




sf::Vector2f Vector2f_from_Vector2i(sf::Vector2i vector){
	return sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));
}


sf::Vector2f get_move_direction_from_button_keys() {
	sf::Vector2f move_direction = {0,0};
	for (const auto& action : actions) {
		if (sf::Keyboard::isKeyPressed(action.Key)) {
			move_direction = sf::Vector2f{ action.x, action.y };
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				move_direction = {move_direction.x*2, move_direction.y * 2 };
			}
			
		}
	}
	return move_direction;
}

std::string get_skill_from_button_keys() {
	std::string temp = "";
	for (const auto& skill : skills) {
		if (sf::Keyboard::isKeyPressed(skill.Key) || sf::Mouse::isButtonPressed(skill.mouse_key)) {
			temp = skill.name;
		}
	}
	return temp;
}

std::string get_action_name_from_button_keys() {
	std::string name = "";
	for (const auto& action : actions) {
		if (sf::Keyboard::isKeyPressed(action.Key)) {
			name = action.name;
		}
	}
	return name;
}


sf::Vector2f get_mouse_position(sf::RenderWindow & window) {
	return Vector2f_from_Vector2i(sf::Mouse::getPosition(window));
}

bool check_mouse() {
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

