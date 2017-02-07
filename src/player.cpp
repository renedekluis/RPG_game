#include "player.hpp"



player::player(sf::RenderWindow & window, sql & database, std::string save) :
	player_npc(window, database, save, true),
	database(database),
	player_id(save)
{
	player_npc.draw();
	spawn = { 
		std::stof(database.get_player_value(player_id).at(4)), 
		std::stof(database.get_player_value(player_id).at(5)) 
	};
	position = spawn;
}

void player::move(sf::Vector2f delta) {
	player_npc.move(delta);
	last_move = delta;
	position += delta;
}

void player::set_action(std::string s) {
	player_npc.set_action(s);
}

void player::draw() {
	player_npc.draw();
}

void player::set_last_position() {
	position -= last_move;
	player_npc.set_position(position);
}

void player::respawn() {
	position = spawn;
	player_npc.set_position(spawn);
}

int player::get_interaction(npc & other_npc) {
	return player_npc.get_interaction(other_npc);
}

int player::get_collision(sf::IntRect colliding_object) {
	return player_npc.get_collision(colliding_object);
}


sf::Vector2f player::get_position() {
	return player_npc.get_position();
}

std::string player::get_current_action() {
	return player_npc.get_current_action();
}

std::vector<sf::Sprite> player::get_action(std::string action_to_get){
	return player_npc.get_action(action_to_get);
}

void player::set_position(sf::Vector2f new_position) {
	player_npc.set_position(new_position);
}


void player::show_ability(std::string action_to_show) {
	player_npc.show_ability(action_to_show);
}

player::~player()
{
}
