#include <iostream>
#include "sqlite3.h"
#include "sql.hpp"
#include <SFML\Graphics.hpp>
#include "button_actions.hpp"
#include "player.hpp"
#include "music.hpp"
#include "main_menu.hpp"
#include "game.hpp"
#include "leveleditor.hpp"


#define start_up 1
#define shut_down 2
#define loading_screen 3
#define level_editor 4
#define playing_game 5
#define main_menu_state 6
#define menu_to_level_editor 7
#define menu_to_game 8


void intro(sf::Music & m, std::string path) {
	if (!m.openFromFile("../../bin/music/boot.ogg")) {
		std::cout << "Error: Music not found or corrupted file.\n";
	}
	m.play();
}

void intro_stop(sf::Music & m) {
	m.stop();
}

int main(int argc, char* argv[]) {
	int game_state = start_up;
	sf::Music m;
	sf::SoundBuffer buffer;
	sf::Sound sound;



	sf::RenderWindow window{ sf::VideoMode{ 1024, 512 }, "SFML window" };
	main_menu menu(window);

	intro(m, "../../bin/music/boot.ogg");
	menu.gid_gud_splash();
	window.display();

	window.clear();
	menu.loading();
	window.display();

	game_state = loading_screen;

	sql database;

	music audio(database, buffer, sound);


	leveleditor editor({ 2048, 2048 }, { 32, 32 }, window, database);
	game main_game(window, database, { 2048, 2048 });

	if (!database.get_level_ids().empty()) {
		//audio.play_music_from_map(database.get_level_ids().at(0));
	}
	intro_stop(m);

	game_state = main_menu_state;

	while (window.isOpen()) {

		window.clear();

		switch (game_state) {
		case main_menu_state:
			menu.show_menu();

			if (menu.button_pressed(menu.level_editor_button, menu.view1)) {
				game_state = menu_to_level_editor;
			}
			if (menu.button_pressed(menu.play_game_button, menu.view1)) {
				game_state = menu_to_game;
			}

			break;
		case level_editor:
			editor.editor_loop();
			break;
		case menu_to_level_editor:
			menu.load_screen();
			game_state = level_editor;
			break;
		case menu_to_game:
			menu.load_screen();
			game_state = playing_game;
			break;
		case playing_game:
			main_game.game_loop();
			break;
		default:
			std::cout << game_state << "\n";
			break;
		}


		


		window.display();

		sf::Event event;
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			//sf::sleep(sf::milliseconds(1));
		}
	}
}
