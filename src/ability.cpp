#include "ability.hpp"



ability::ability(std::string name, std::vector<sf::Sprite> & action_list, sf::Vector2f position):
	name(name),
	position(position)
{
	for (auto item : action_list) {
		item.setPosition(position);
		action.push_back(item);
	}
}

std::string ability::get_name() {
	return name;
}

void ability::move( sf::Vector2f new_position) {
	if(position != new_position){
		position = new_position;
		for (auto & item : action) {
			item.setPosition(position);
		}
		next_step();
		
	}
	else if (name.find("walk") != std::string::npos ){
		current_action_step = 0;
	}
	else {
		next_step();
	}
	
}

void ability::next_step() {
	
	if (current_action_step < int(action.size()) - 1) {
		current_action_step++;
	}
	else {
		current_action_step = 0;
	}
}


const void ability::draw(sf::RenderWindow & window) {
	window.draw(action.at(current_action_step));
}

void ability::add_sprite_to_action(sf::Sprite t) {
	action.push_back(t);
}

std::vector<sf::Sprite> ability::get_action() {
	return action;
}



ability::~ability(){
}
