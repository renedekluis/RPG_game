#pragma once
#include "sql.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

class music {
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music intro;
	sql database;
	std::string path;

public:


	/// Constructor
	//
	/// This method will crate an object of class music.\n
	///
	/// 
	/// Parameters:
	/// -----------
	/// database : sql& \n
	///	-> refference to the sqlite database.\n
	///
	/// buffer : sf::SoundBuffer \n
	///	-> a sf::SoundBuffer.\n
	///
	/// sound : sf::Sound \n
	///	-> a sf::sound.\n
	/// 
	///
	/// Example:
	/// --------
	/// music m(database, buffer, sound)\n
	///
	music(sql & database, sf::SoundBuffer buffer, sf::Sound sound);


	/// Set music volume
	//
	/// This function changes the volume of the played music \n
	/// 
	/// Parameters:
	/// -----------
	/// i : int \n
	///	-> The volume strength \n
	///
	/// Example:
	/// --------
	/// set_volume(100) \n
	/// -> Volume has been set to 100 \n
	///
	void set_volume(int i);


	/// Play map music
	//
	/// Play the music that belongs to a specific map \n
	/// 
	/// Parameters:
	/// -----------
	/// map_id : std::string \n
	///	-> The map of which the music has to be played \n
	///
	/// Example:
	/// --------
	/// play_music_from_map("1") \n
	/// -> Play the music from map 1 \n
	///
	void play_music_from_map(std::string map_id);


	/// Stop the music
	//
	/// This function stops the music \n
	/// 
	/// Example:
	/// --------
	/// stop_music() \n
	/// -> Music has been stopped \n
	///
	void stop_music();

};