#include "game.hpp"

game::game(sf::RenderWindow & window, sql & database, sf::Vector2f levelsize) :
	window(window),
	database(database),
	inv(window, database),
	levelsize(levelsize),
	arno(window, database, "1"),
	dialogbox("../../bin/pictures/dialog_box.png", "../../bin/pictures/game_font.ttf", {200, 800})
	
{
	std::vector<std::string>level_ids = database.get_level_ids();
	if (!level_ids.empty()) {
		background_values_map = database.get_level_background_value(level_ids.at(0));

		for (auto indexer = background_values_map.begin(); indexer != background_values_map.end(); indexer++) {
			if (indexer->second.at(indexer->second.size() - 1) != "1") {
				std::cout << indexer->second.at(1);
				collision_objects.push_back(database.get_collision_objects(indexer->second));
			}
		}

		get_items_from_database(background_values_map);
		object_values_map = database.get_level_object_value(level_ids.at(0));

		for (auto indexer = object_values_map.begin(); indexer != object_values_map.end(); indexer++) {
			collision_backgrounds.push_back(database.get_collision_objects(indexer->second));
		}
		get_items_from_database(object_values_map);
		std::vector<std::string>temp = { "1","3","4","5","6" };
		for (auto i : temp) {
			for (auto indexer : database.get_quest_parts(i)) {
				for (auto index : database.get_quest_text(i, indexer)) {
					if (index == "NULL") { continue; }
					begin_stories[i].push_back(index);
				}
			}
		}


		load_npc();
		draw_npc();
		draw_player();
	}
	game_view.setCenter(levelsize.x / 4 + 25, levelsize.y / 4 + 10);
	game_view.setSize(levelsize.x / 2, levelsize.y / 2);
	game_view.setViewport(sf::FloatRect(0, 0, 1, 1));
	dialogbox_view.setCenter(levelsize.x / 4 + 25, levelsize.y / 4 + 10);
	dialogbox_view.setSize(levelsize.x / 2, levelsize.y / 2);
}

void game::game_loop() {
	
	//while (window.isOpen()) {
	//	window.clear();
		
		if (game_begin) {
			window.setView(game_view);
			
			draw_background_store();
			move_player();
			draw_npc();
			player_skill();
			draw_player();

			game_viewer();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				while (sf::Keyboard::isKeyPressed(sf::Keyboard::R));
				arno.respawn();
			}
		}
		else {
			view_start_dialogs();
		}
		
		interact("1");

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
			inv.get_inventory();
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::I));
		}


	//	window.display();
		
		
	//	sf::Event event;
	//	if (window.pollEvent(event)) {
	//		if (event.type == sf::Event::Closed) {
	//			window.close();
	//		}
	//		sf::sleep(sf::milliseconds(1));
	//	}
	//}
}

void game::game_viewer() {
	if (mouse_intersects_left_edge(game_view)) game_view.move({ -2 , 0 });
	if (mouse_intersects_right_edge(game_view)) game_view.move({ 2, 0 });
	if (mouse_intersects_upper_edge(game_view)) game_view.move({ 0, -4 });;
	if (mouse_intersects_down_edge(game_view)) game_view.move({ 0, 4 });;
}

bool game::mouse_intersects_left_edge(sf::View & view) {
	return get_mouse_position(window).x <= 10 && (window.mapPixelToCoords(sf::Mouse::getPosition(window), view).x >= -5);
}

bool game::mouse_intersects_right_edge(sf::View & view) {
	return get_mouse_position(window).x >= (window.getSize().x - 10) && (window.mapPixelToCoords(sf::Mouse::getPosition(window), view).x <= (levelsize.x + 25));
}

bool game::mouse_intersects_upper_edge(sf::View & view) {
	return get_mouse_position(window).y <= 10 && (window.mapPixelToCoords(sf::Mouse::getPosition(window), view).y >= -5);
}

bool game::mouse_intersects_down_edge(sf::View & view) {
	return get_mouse_position(window).y >= (window.getSize().y - 10) && (window.mapPixelToCoords(sf::Mouse::getPosition(window), view).y <= (levelsize.y + 25));
}

void game::view_start_dialogs() {


	for (auto i = begin_stories.begin(); i != begin_stories.end(); i++) {
		for (auto x : i->second) {
			dialogbox.text_input((x + "\n[Press Space to continue]"), 25, sf::Color::White);
			window.setView(dialogbox_view);
			dialogbox.draw(window);
			window.display();

			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { sf::sleep(sf::milliseconds(10)); }
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { sf::sleep(sf::milliseconds(10)); }
		}

		window.clear();

		draw_background_store();draw_npc();draw_player();
		game_viewer();

		window.display();
		
		if (i->first == "1") {
			window.clear();
			perform_player_action("cast_spell_down");
			draw_background_store();draw_npc();draw_player();
			game_viewer();

			window.display();
			int x = 0;
			while (x < 50) {
				if (get_move_direction_from_button_keys() != sf::Vector2f(0, 0)) {
					window.clear();
					draw_background_store();draw_npc();move_player();draw_player();game_viewer();
					window.display();
					x++;
				}
			}
			
		}
		if (i->first == "3") {
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { sf::sleep(sf::milliseconds(10)); }
		}
		if (i->first == "4") {
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::F)) { sf::sleep(sf::milliseconds(10)); }
		}
		if (i->first == "5") {
			while (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) { sf::sleep(sf::milliseconds(10)); }
		}
		if (i->first == "6") {
			dialogbox.text_input(("Well, Good luck now!\n[Press Space to continue]"), 25, sf::Color::White);
			window.setView(dialogbox_view);
			dialogbox.draw(window);
			window.display();
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { sf::sleep(sf::milliseconds(10)); }
			while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { sf::sleep(sf::milliseconds(10)); }
		}

		player_skill();

	}
	game_begin = true;
}

void game::interact() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		for (auto one_npc : npc_list) {
			if (arno.get_interaction(*one_npc)) {

				for (auto indexer : database.get_quest_parts("0")) {
					for (auto index : database.get_quest_text("0", indexer)) {
						if (index == "NULL") { continue; }
						dialogbox.text_input((index), 25, sf::Color::White);
						window.setView(dialogbox_view);
						dialogbox.draw(window);
						window.display();

						while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
					}
				}
			}
		}

		window.clear();
		draw_player();
		window.display();
	}
}

void game::interact(std::string item_id) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		for (auto one_npc : npc_list) {
			if (arno.get_interaction(*one_npc)) {
				for (auto indexer : database.get_quest_parts("2")) {
					for (auto index : database.get_quest_text("2", indexer)) {
						if (index == "NULL") { continue; }
						dialogbox.text_input((index), 25, sf::Color::White);
						window.setView(dialogbox_view);
						dialogbox.draw(window);
						window.display();

						while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
						while (sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
					}
				}
				database.add_item_to_inventory(item_id);
			}
		}

		window.clear();
		draw_player();
		window.display();
	}
}

void game::get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map) {
	std::string path;
	float posx = 0;
	float posy = 0;
	for (auto map_indexer = item_values_map.begin(); map_indexer != item_values_map.end(); map_indexer++) {
		path = map_indexer->second.at(0);
		posx = std::stof(map_indexer->second.at(2));
		posy = std::stof(map_indexer->second.at(3));
		sf::Vector2f pos = { posx, posy };
		std::cout << "loaded: " << path << "\t" << pos.x << "\t" << pos.y << "\n";
		background_store.push_back(new picture(path, pos, { 0,0 }));
	}
}

void game::draw_background_store() {
	for (auto background_tile : background_store) {
		background_tile->draw(window);
	}
}


void game::draw_npc() {
	for (auto one_npc : npc_list) {
		one_npc->draw();
	}
}

void game::load_npc() {
	for (auto indexer : database.get_number_of_npcs()) {
		npc_list.push_back(new npc(window, database, indexer));
	}
}

void game::player_skill() {
	std::string temp = get_skill_from_button_keys();
	std::string current = arno.get_current_action();

	if (temp != "") {
		if ((current.find("up")) != std::string::npos) {
			temp += "_up";
			perform_player_action(temp);
		}
		else if ((current.find("left")) != std::string::npos) {
			temp += "_left";
			perform_player_action(temp);
		}
		else if ((current.find("down")) != std::string::npos) {
			temp += "_down";
			perform_player_action(temp);
		}
		else if ((current.find("right")) != std::string::npos) {
			temp += "_right";
			perform_player_action(temp);
		}
	}
}


void game::move_player() {
	bool no_collision = true;
	for (auto one_npc : npc_list) {
		if (arno.get_interaction(*one_npc)) {
			no_collision = false;
		}
	}
	for (auto indexer : collision_backgrounds) {
		if (arno.get_collision(indexer)) {
			no_collision = false;
		}
	}
	for (auto indexer : collision_objects) {
		if (arno.get_collision(indexer)) {
			no_collision = false;
		}
	}
	if (no_collision) {
		arno.set_action(get_action_name_from_button_keys());
		arno.move(get_move_direction_from_button_keys());
	}
	else {
		for (int i = 0; i < 3; i++) {
			arno.set_last_position();
		}
	}
	
}

void game::draw_player() {
	arno.draw();
}

void game::perform_player_action(std::string action) {
	std::vector<sf::Sprite> & temp = arno.get_action(action);
	std::string action_save = arno.get_current_action();
	arno.set_action(action);
	for (auto & index : temp) {
		window.clear();
		
		draw_background_store();
		draw_npc();
		arno.show_ability(action);

		window.display();
		sf::sleep(sf::milliseconds(50));
	}
	arno.set_action(action_save);
}

void game::perform_npc_action(std::string npc_name, std::string action) {
	std::vector<sf::Sprite> temp;
	std::string action_save;
	for (auto indexer : npc_list) {
		if (indexer->get_name() == npc_name) {
			temp = indexer->get_action(action);
			action_save = indexer->get_current_action();
			for (auto & index : temp) {
				window.clear();

				draw_background_store();
				draw_npc();
				indexer->show_ability(action);

				window.display();
				sf::sleep(sf::milliseconds(50));
			}
			indexer->set_action(action_save);
			break;
		}
	}
	
}