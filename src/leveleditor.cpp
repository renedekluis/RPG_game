#include "leveleditor.hpp"

leveleditor::leveleditor(sf::Vector2f levelsize, sf::Vector2f rect_size, sf::RenderWindow & window, sql & database):
	levelsize(levelsize),
	rect_size(rect_size),
	database(database),
	save_level_button("../../bin/pictures/save_level_button.png", { 0 , ((float)window.getSize().y / 9 ) + 120 }, { 0,0 }),
	back_to_menu_button("../../bin/pictures/back_to_menu_button.png", { 0, (float)window.getSize().y / 9 + 180}, { 0,0 }),
	new_game_button("../../bin/pictures/new_level_button.png", { 0 , ((float)window.getSize().y / 9) }, { 0,0 }),
	load_game_button("../../bin/pictures/load_level_button.png", { 0, ((float)window.getSize().y / 9) + 60}, { 0,0 }),
	window(window)
{
	load_rectangles();
	load_tile_list();

	view1.setCenter(sf::Vector2f(levelsize.x / 2, levelsize.y / 2));
	view1.setSize(sf::Vector2f(levelsize.x, levelsize.y));
	view1.setViewport(sf::FloatRect(0, 0, 0.75f, 1));
	view1.zoom(1.5);

	view2.setCenter(sf::Vector2f(levelsize.x + 192, 256));
	view2.setSize(sf::Vector2f(256, 512));
	view2.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1));
	
	view3.setCenter(sf::Vector2f(200 , 250));
	view3.setSize(sf::Vector2f(400, 500));
	view3.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1));
	view3.zoom(1.5);

	view4.setCenter(sf::Vector2f(200, 250));
	view4.setSize(sf::Vector2f(400, 500));
	view4.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 1));
	view4.zoom(1.5);
}

void leveleditor::editor_loop() {
	while (window.isOpen()) {
		window.clear();

		window.setView(view1);
		get_actions();
		draw_rectangle_store();
		draw_background_store();
		draw_temporary_store();

		if (pressed_load_game == true) {
			window.setView(view4);
			std::vector<std::string>available_level_names = database.get_available_levels();
			level_ids = database.get_level_ids();
			std::map<std::string, std::string> id_with_name;
			level_buttons.clear();
			float posy = 0;
			int count = 0;
			int x = 0;
			std::string id = "";

			for (auto indexer : level_ids) {
				if (x < available_level_names.size()) {
					id_with_name[indexer] = available_level_names.at(x);
					x++;
				}
			}
			for (auto level : available_level_names) {
				level_buttons.push_back(new dialogbox("../../bin/pictures/button_background.png", "../../bin/pictures/button_font.ttf", { 0, posy }));
				posy += 70;
			}
			for (auto button : level_buttons) {
				if (count < available_level_names.size()){
					button->text_input(available_level_names.at(count), 40, sf::Color::White);
					button->draw(window);
					count++;
				}
			}
			for (auto button : level_buttons) {
				if (button_pressed(*button,view4)) {
					active_level = button->last_text;
					for (auto level_id : id_with_name) {
						if (level_id.second == active_level) {
							id = level_id.first;
						}
					}
					background_values_map = database.get_level_background_value(id);
					get_items_from_database(background_values_map);
					object_values_map = database.get_level_object_value(id);
					get_items_from_database(object_values_map);

					pressed_load_game = false;
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			pressed_esc = true;
		}

		if (pressed_esc == true) {
			bool out_of_loop = menu_options();
			if (out_of_loop) {
				break;
			}
		}
		else if(pressed_load_game == false && pressed_esc == false) {
			window.setView(view2);
			get_actions();
			draw_tile_store();
		}

		window.display();

		sf::sleep(sf::milliseconds(20));

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}
}

bool leveleditor::menu_options() {
	window.setView(view3);
	save_level_button.draw(window);
	back_to_menu_button.draw(window);
	new_game_button.draw(window);
	load_game_button.draw(window);

	if (is_button_pressed(new_game_button, view3)) {
		level_ids = database.get_level_ids();
		std::string level_name = "level" + std::to_string(level_ids.size() + 1);
		active_level = level_name;
		background_store.clear();
		temporary_store.clear();
		database.set_new_map(level_name, 1);
		pressed_esc = false;
	}
	if (is_button_pressed(load_game_button, view3)) {
		pressed_load_game = true;
		pressed_esc = false;
		background_store.clear();
		temporary_store.clear();
	}
	if (is_button_pressed(save_level_button, view3)) {
		pressed_load_game = false;
		for (auto tile : temporary_store) {
			std::string path = tile->picture_path;
			int pos_x = tile->position.x;
			int pos_y = tile->position.y;
			database.save_tiles(path, pos_x, pos_y, active_level);
		}
		temporary_store.clear();
		background_store.clear();
	}
	if (is_button_pressed(back_to_menu_button, view3)) {
		pressed_esc = true;
		pressed_load_game = false;
		background_store.clear();
		temporary_store.clear();
		return 1;
	}
	return 0;
}

void leveleditor::get_items_from_database(std::map<std::string, std::vector<std::string>> & item_values_map) {
	std::string path;
	float posx = 0;
	float posy = 0;
	for (auto map_indexer : item_values_map) {
		path = map_indexer.second.at(0);
		posx = std::stof(map_indexer.second.at(2));
		posy = std::stof(map_indexer.second.at(3));
		sf::Vector2f pos = { posx, posy };
		std::cout << "loaded: " << path << "\t" << pos.x << "\t" << pos.y << "\n";
		background_store.push_back(new picture(path, pos, { 0,0 }));
	}
}

bool leveleditor::is_button_pressed(picture & object, sf::View & view) {
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && object.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
}

bool leveleditor::button_pressed(dialogbox & object, sf::View & view) {
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && object.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
}

void leveleditor::load_rectangles(){
	for (float x = 0; x <= levelsize.x; x += rect_size.x) {
		for (float y = 0; y <= levelsize.y; y += rect_size.y) {
			sf::Vector2f position = {x, y};
			rectangle_store.push_back(new rectangle(position, rect_size, 3, sf::Color::Black, sf::Color::Red));
		}
	}
}

void leveleditor::create_object(sf::Vector2f pos) {
	for (auto tile : tile_store) {
		if (tile->selected) {
			temporary_store.push_back(new picture(tile->picture_path, pos , tile->tile_size));
			sf::sleep(sf::milliseconds(200));
		}
	}
}

void leveleditor::remove_last_object() {
	if (temporary_store.size() > 0) {
		temporary_store.pop_back();
	}
	sf::sleep(sf::milliseconds(200));
}

bool leveleditor::remove_object_under_mouse() {
	int index = 0;
	for (auto tile : temporary_store) {
		if (tile->getBounds().contains(convert_to_coords(view1))) {
			temporary_store.erase(temporary_store.begin() + index);
			return true;
		}
		index += 1;
	}
	return false;
}

void leveleditor::load_tile_list() {
	float start = levelsize.x + 64;
	float pos_x = start;
	float pos_y = 0;
	sf::Vector2f pre_size = { 0, 0 };
	std::string path;
	sf::Vector2f tile_size;
	float biggest_tile = 0;
	
	std::vector<std::string> tile_id;
	tile_id = database.get_object_sprite_ids();

	std::vector<std::string> tile;

	float tile_position_x_converted_as_int;
	float tile_position_y_converted_as_int;

	
	
	for (auto indexer : tile_id) {
		
		tile = database.get_object_sprite_value(indexer);

		std::istringstream buffer(tile.at(2));
		buffer >> tile_position_x_converted_as_int;
		std::istringstream buff(tile.at(3));
		buff >> tile_position_y_converted_as_int;
		

		sf::Vector2f tile_size = { tile_position_x_converted_as_int, tile_position_y_converted_as_int };
		
		if ((pos_x + tile_size.x) > (start + 256)) {
			pos_y += biggest_tile;
			pos_x = start;
			pre_size = { tile_size.x, tile_size.y };
			biggest_tile = 0;
		}
		if ((pos_x + tile_size.x) <= (start + 256)) {
			tile_store.push_back(new picture(tile.at(0), { pos_x, pos_y }, tile_size));
			pos_x += tile_size.x;
			pre_size = { tile_size.x, tile_size.y };
			if (pre_size.y > biggest_tile) {
				biggest_tile = pre_size.y;
			}
		}
	}
}

sf::Vector2f leveleditor::convert_to_coords(sf::View & view) {
	return window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
}

sf::Vector2f leveleditor::get_position_from_rectangle_under_mouse() {
	for (auto rectangle : rectangle_store) {
		if (rectangle->getBounds().contains(convert_to_coords(view1))) {
			return rectangle->position;
		}
	}
	return {0,0};
}

bool leveleditor::is_object_under_mouse(std::vector<figure*> & vector, sf::View & view) {
	for (auto tile : vector) {
		if (tile->getBounds().contains(convert_to_coords(view))) {
			return true;
		}
	}
	return false;
}

bool leveleditor::is_object_under_mouse(std::vector<picture*> & vector, sf::View & view) {
	for (auto tile : vector) {
		if (tile->getBounds().contains(convert_to_coords(view))) {
			return true;
		}
	}
	return false;
}

void leveleditor::set_selected() {
	for (auto tile : tile_store) {
		if (tile->getBounds().contains(convert_to_coords(view2))){
			tile->selected = 1;
		}
		else {
			tile->selected = 0;
		}
	}
}

void leveleditor::draw_rectangle_store() {
	for (auto rectangle : rectangle_store) {
		rectangle->draw(window);
	}
}

void leveleditor::draw_background_store() {
	for (auto background_tile : background_store) {
		background_tile->draw(window);
	}
}

void leveleditor::draw_temporary_store() {
	for (auto background_tile : temporary_store) {
		background_tile->draw(window);
	}
}

void leveleditor::draw_tile_store() {
	for (auto tile : tile_store) {
		tile->draw(window);
	}
}

void leveleditor::get_actions() {
	for (auto & action : actions) {
		action();
	}
}