#include "main_menu.hpp"

main_menu::main_menu(sf::RenderWindow & window) :
	window(window),
	background("../../bin/pictures/main_background.jpg", { 0,0 }, { 0,0 }),
	level_editor_button("../../bin/pictures/level_editor_button.png", { 2150,630 }, { 0,0 }),
	play_game_button("../../bin/pictures/play_game_button.png", { 1950,650 }, { 0,0 }),
	load_screen_pic("../../bin/pictures/loading.png", { 0, 0 }, { 0,0 }),
	gid_gud("../../bin/pictures/gid_gud_splash_screen.png", { 0, 0 }, { 0,0 })
{
	view1.setCenter({1280,800});
	view1.setSize({2560,1600});
	level_editor_button.rotate(270);
	play_game_button.rotate(270);
}

void main_menu::show_menu() {
	window.setView(view1);
	draw_main_menu();
	button_pressed(level_editor_button, view1);
}

void main_menu::draw_main_menu() {
	background.draw(window);
	level_editor_button.draw(window);
	play_game_button.draw(window);
}

bool main_menu::button_pressed(picture & object, sf::View & view) {
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && object.getBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window), view));
}

void main_menu::load_screen() {
	for (int i = 0; i < 50; i++) {
		window.clear();
		show_menu();
		view1.rotate(i);
		view1.zoom(0.94);
		view1.move({ -6,0 });
		background.set_transpirantie(-i*5.3);
		window.display();
		sf::sleep(sf::milliseconds(50));
	}
	view2.setCenter({ 960,540 });
	view2.setSize({ 1920,1080 });

	load_screen_pic.set_transpirantie(0);
	window.setView(view2);
	for (int i = 0; i <= 50; i++) {
		window.clear();
		load_screen_pic.draw(window);
		load_screen_pic.set_transpirantie(i*5.2);
		window.display();
		sf::sleep(sf::milliseconds(20));
	}
	view1.setCenter({ 1280,800 });
	view1.setSize({ 2560,1600 });
	view1.rotate(215);
}
void main_menu::gid_gud_splash() {
	view2.move({0,-200});

	window.setView(view2);
	for (int i = 0; i <= 200; i+=2) {
		window.clear();
		gid_gud.set_transpirantie(i);
		gid_gud.draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
	}

	for (int i = 200; i >= 150; i -=2) {
		window.clear();
		gid_gud.set_transpirantie(i);
		gid_gud.draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
	}
}

void main_menu::loading() {
	view2.setCenter({ 960,540 });
	view2.setSize({ 1920,1080 });

	window.setView(view2);
	for (int i = 0; i <= 150; i += 2) {
		window.clear();
		load_screen_pic.set_transpirantie(i);
		load_screen_pic.draw(window);
		window.display();
		sf::sleep(sf::milliseconds(20));
	}
}