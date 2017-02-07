#include "sql.hpp"




sql::sql() {
	
	//Checking if the given database exists and not locked.
	std::ifstream database_existance(database_path);
	if (!database_existance.good()) {
		std::cout	<< "Error: Could not open database."				//error definition
					<< "Probbably incorrect path or locked file.\n";	//error explanation
		while (1);
	}
	else { 
		std::cout << "Database correctly opened.\n";					//database found
	}
	database_existance.close();

	//Opening the database
	connection = sqlite3_open(database_path.c_str(), &database);
}	

sql::~sql() {
	sqlite3_close(database);
}


int sql::callback(void *NotUsed, int argc, char **argv, char **azColName) {
	for (int i = 0; i < argc; i++) {
		set_result(argv[0]);
	}
	return 0;
}

void sql::check_query_request() {
	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE << "\tLine: " << __LINE__ << std::endl;
		sqlite3_free(_ERROR_MESSAGE);
	}
}

void sql::execute_query_without_return(const char* to_be_executed) {
	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0);
	check_query_request();
}

std::vector<std::string> sql::execute_query_with_return(const char* to_be_executed) {

	while (rc = sqlite3_exec(database, to_be_executed, callback, 0, &_ERROR_MESSAGE) != 0);
	check_query_request();

	return get_result();
}


std::vector<std::string> sql::get_data(char* table, char* columnname, char* condition1, char* condition2) {
	std::ostringstream query;
	query << "SELECT " << columnname << " FROM " << table << " WHERE " << condition1 << " == " << condition2 << ";";
	
	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_data(char* table, char* columnname) {
	std::ostringstream query;
	query << "SELECT " << columnname << " FROM " << table << ";";
	
	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}

void sql::add_data(char* table, const char* values) {
	std::ostringstream query;
	query << "INSERT INTO " << table << " VALUES( NULL, " << values << ");";

	std::string query_string = query.str();
	execute_query_without_return(query_string.c_str());
}


void sql::add_item_to_inventory(std::string item_id) {
	std::ostringstream query;
	query << "INSERT INTO inventory VALUES( " << item_id << ", 1, 0);";

	std::string query_string = query.str();
	std::cout << "Going to update" << std::endl;
	execute_query_without_return(query_string.c_str());
	std::cout << "Updated" << std::endl;
}

void sql::change_data(char* table, char* condition1, char* condition2, char* columnname, char* new_value) {
	std::ostringstream query;
	query	<< "UPDATE "	<< table 
			<< " SET "		<< columnname << " = '"	<< new_value
			<< "' WHERE "	<< condition1	<< " = "	<< condition2 << ";";
	
	std::string query_string = query.str();
	execute_query_without_return(query_string.c_str());
}

std::vector<std::string> sql::get_result() {
	std::vector<std::string>temp_result_save;
	temp_result_save = result;
	while (result.size() > 0) {
		result.pop_back();
	}
	return temp_result_save;

}


std::vector<std::string> sql::get_inventory() {
	std::ostringstream query;
	query << "SELECT item_id "
		<< " FROM inventory;";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());

}

std::vector<std::string> sql::get_name_from_id_inventory(std::string item_id) {
	std::ostringstream query;
	query << "SELECT name "
		<< " FROM item"
		<< " WHERE id = " << item_id << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}

std::vector<std::string> sql::get_sprite_inventory(std::string item_id) {
	std::ostringstream query;
	query << "SELECT sprite "
		<< " FROM item"
		<< " WHERE id = " << item_id << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}

std::vector<std::string> sql::get_in_game_name_from_id_inventory(std::string item_id) {
	std::ostringstream query;
	query << "SELECT in_game_name "
		<< " FROM item"
		<< " WHERE id = " << item_id << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_player_value(int save, std::string variable_name) {
	std::ostringstream query;
	query	<< "SELECT " << variable_name
			<< " FROM player "
			<< "WHERE id == " << save << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_player_sprite(int save) {
	std::ostringstream query;
	query	<< "SELECT sprites.path "
			<< "FROM sprites, player "
			<< "WHERE sprites.id = player.sprite_id "
			<< "AND name = " << save << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_number_of_npcs() {
	std::vector<std::string>total = get_data("NPC", "id");
	return total;
}

std::vector<std::string> sql::get_npc_value(std::string npc_id) {

	std::vector<std::string>temp_npc_value;
	std::vector<std::string>npc_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;

	ostring_query 
	<< "SELECT "<< "name"			
	<< " FROM "	<< "NPC"		
	<< " WHERE "<< "id"	<< " == " << npc_id << ";"
	
	<< "SELECT "<< "sprites.path"	
	<< " FROM "	<< "sprites, NPC"
	<< " WHERE "<< "sprites.name"	<< " == " << "NPC.name" 
	<< " AND "	<< "NPC.id"		<< " == " << npc_id << ";"
	
	<< "SELECT " << "class_id"		
	<< " FROM "	 << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"

	<< "SELECT " << "position_x"	
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"
	
	<< "SELECT " << "position_y"	
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";"
	
	<< "SELECT " << "quest_id"		
	<< " FROM "  << "NPC"		
	<< " WHERE " << "id" << " == " << npc_id << ";";

	temp_query_string = ostring_query.str();
	temp_npc_value = execute_query_with_return(temp_query_string.c_str());
	for (auto indexer : temp_npc_value) {
		npc_values.push_back(indexer);
	}
	
	return npc_values;
}


std::vector<std::string> sql::get_object_sprite_ids() {
	
	std::vector<std::string>sprite_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;
	
	ostring_query << "SELECT id FROM sprites WHERE path LIKE '../../bin/tiles%' OR path LIKE '../../bin/objects%';";
	temp_query_string = ostring_query.str();
	
	return execute_query_with_return(temp_query_string.c_str());
}


std::vector<std::string> sql::get_object_sprite_value(std::string object_id) {

	std::vector<std::string>temp_sprite_values;
	std::vector<std::string>sprite_values;
	std::string temp_query_string;
	std::ostringstream ostring_query;
	
	ostring_query
		<< "SELECT " << "path"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "name"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "size_x"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "size_y"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";"

		<< "SELECT " << "walkable"
		<< " FROM " << "sprites"
		<< " WHERE " << "id" << " == " << object_id << ";";


	temp_query_string = ostring_query.str();
	temp_sprite_values = execute_query_with_return(temp_query_string.c_str());
	for (auto indexer : temp_sprite_values) {
		sprite_values.push_back(indexer);
	}

	return sprite_values;
}



void sql::set_new_map(std::string map_name, int background_music){
	std::ostringstream ostring_query;

	ostring_query 
		<< "INSERT INTO maps "
		<< "VALUES( " 
			<< "NULL,"
			<<" '" << map_name << "'," 
			<< std::to_string(background_music) 
		<< ");";
	execute_query_without_return(ostring_query.str().c_str());
}


void sql::save_tiles(std::string tile_path, int pos_x, int pos_y, std::string map_name){
	//checks
	std::vector<std::string>tile_paths = get_data("sprites", "path");
	std::vector<std::string>map_names = get_data("maps", "name");
	bool incorrect_path = false;
	bool incorrect_map = false;
	for (auto path : tile_paths) { if (path == tile_path) { incorrect_path = true; } }
	for (auto name : map_names) { if (name == map_name) { incorrect_map = true; } }



	if (incorrect_path && incorrect_map) {
		//saving
		std::vector<std::string>searched_values;
		
		std::string temp_query_string;

		std::size_t found = tile_path.find("/objects/");

		std::ostringstream sprite_name_from_path_query;
		std::ostringstream sprite_id_from_path_query;
		std::ostringstream map_id_from_map_name_query;
		std::ostringstream ostring_query;


		sprite_name_from_path_query
			<< "SELECT " << "name"
			<< " FROM " << "sprites"
			<< " WHERE " << "path" << " == '" << tile_path << "';";

		sprite_id_from_path_query
			<< "SELECT " << "id"
			<< " FROM " << "sprites"
			<< " WHERE " << "path" << " == '" << tile_path << "';";


		map_id_from_map_name_query
			<< "SELECT " << "id"
			<< " FROM " << "maps"
			<< " WHERE " << "name" << " == '" << map_name << "';";

		std::string temp_sprite_name_from_path_query = sprite_name_from_path_query.str();
		std::string temp_sprite_id_from_path_query = sprite_id_from_path_query.str();
		std::string temp_map_id_from_map_name = map_id_from_map_name_query.str();

		searched_values.push_back(execute_query_with_return(temp_sprite_name_from_path_query.c_str()).at(0));
		searched_values.push_back(execute_query_with_return(temp_sprite_id_from_path_query.c_str()).at(0));
		searched_values.push_back(execute_query_with_return(temp_map_id_from_map_name.c_str()).at(0));

		
		if (found != std::string::npos) {
			std::cout << "Word opgeslagen in objects.\n";
			ostring_query
				<< "INSERT INTO objects "
				<< "VALUES( "
				<< "NULL," << " '"
				<< searched_values.at(0) << "', "
				<< searched_values.at(1) << ", "
				<< std::to_string(pos_x) << ", "
				<< std::to_string(pos_y) << ", "
				<< searched_values.at(2)
				<< ");";
			execute_query_without_return(ostring_query.str().c_str());
		}
		else if ((found = tile_path.find("/tiles/")) != std::string::npos) {
			std::cout << "Word opgeslagen in background.\n";
			ostring_query
				<< "INSERT INTO background "
				<< "VALUES( "
				<< "NULL," << " '"
				<< searched_values.at(0) << "', "
				<< searched_values.at(1) << ", "
				<< std::to_string(pos_x) << ", "
				<< std::to_string(pos_y) << ", "
				<< searched_values.at(2)
				<< ");";
			execute_query_without_return(ostring_query.str().c_str());
		}
		else {
			std::cout << "Error: Tile not found.\t" //declaration
				<< "The map can not be saved due an incorrect or non-existing path."; //definition
		}
	}
	
	
	if(!incorrect_path){
		std::cout << "Error: Incorrect path.\t" //definition
			<< "The map can not be saved due an incorrect or non-existing tile path."; //declaration
	}
	if (!incorrect_map) {
		std::cout << "Error: Incorrect map name.\t"	//definition
			<< "The map can not be saved due an incorrect or non-existing level name."; //declaration
	}
}


std::vector<std::string> sql::get_available_levels() {
	std::vector<std::string>total = get_data("maps", "name");
	return total;
}

std::vector<std::string> sql::get_level_ids() {
	std::vector<std::string>total = get_data("maps", "id");
	return total;
}



std::map<std::string, std::vector<std::string>> sql::get_level_object_value(std::string level_id) {

	std::string temp_query_string;
	
	std::map<std::string, std::vector<std::string>>object_values_map;
	std::vector<std::string>object_ids = get_data("objects", "id");

	for(auto id : object_ids){
		std::vector<std::string>object_values;
		std::ostringstream ostring_query;
		ostring_query
			<< "SELECT " << "sprites.path"
			<< " FROM " << "sprites, objects"
			<< " WHERE " << "sprites.id" << " == " << "objects.sprite_id" 
			<< " AND " << "objects.id" << " == " << id
			<< " AND " << "objects.map_id" << " == " << level_id << ";"

			<< "SELECT " << "name"
			<< " FROM " << "objects"
			<< " WHERE " << "map_id" << " == " << level_id 
			<< " AND " << "objects.id" << " == " << id << ";"

			<< "SELECT " << "position_x"
			<< " FROM " << "objects"
			<< " WHERE " << "map_id" << " == " << level_id 
			<< " AND " << "objects.id" << " == " << id << ";"

			<< "SELECT " << "position_y"
			<< " FROM " << "objects"
			<< " WHERE " << "map_id" << " == " << level_id 
			<< " AND " << "objects.id" << " == " << id << ";"

			<< "SELECT " << "sprites.walkable"
			<< " FROM " << "sprites, objects"
			<< " WHERE " << "sprites.id" << " == " << "objects.sprite_id"
			<< " AND " << "objects.map_id" << " == " << level_id 
			<< " AND " << "objects.id" << " == " << id << ";";

		temp_query_string = ostring_query.str();
		object_values = execute_query_with_return(temp_query_string.c_str());
		if (object_values.empty() == false) {
			object_values_map[id] = object_values;
		}

	}

	return object_values_map;

}


std::map<std::string, std::vector<std::string>> sql::get_level_background_value(std::string level_id) {
	
	std::string temp_query_string;
	std::vector<std::string>background_ids = get_data("background", "id");
	std::map<std::string, std::vector<std::string>>object_values_map;
	
	for (auto id : background_ids) {
		std::ostringstream ostring_query;
		std::vector<std::string>background_values;
		ostring_query
			<< "SELECT " << "sprites.path"
			<< " FROM " << "sprites, background"
			<< " WHERE " << "sprites.id" << " == " << "background.sprite_id"
			<< " AND " << "background.map_id" << " == " << level_id 
			<< " AND " << "background.id" << " == " << id << ";"

			<< "SELECT " << "name"
			<< " FROM " << "background"
			<< " WHERE " << "map_id" << " == " << level_id
			<< " AND " << "background.id" << " == " << id << ";"

			<< "SELECT " << "position_x"
			<< " FROM " << "background"
			<< " WHERE " << "map_id" << " == " << level_id
			<< " AND " << "background.id" << " == " << id << ";"

			<< "SELECT " << "position_y"
			<< " FROM " << "background"
			<< " WHERE " << "map_id" << " == " << level_id
			<< " AND " << "background.id" << " == " << id << ";"

			<< "SELECT " << "sprites.walkable"
			<< " FROM " << "sprites, background"
			<< " WHERE " << "sprites.id" << " == " << "background.sprite_id"
			<< " AND " << "background.map_id" << " == " << level_id
			<< " AND " << "background.id" << " == " << id << ";";

		temp_query_string = ostring_query.str();
		object_values_map[id] = execute_query_with_return(temp_query_string.c_str());
		if (background_values.empty() == false) {
			object_values_map[id] = background_values;
		}
	}
	

	return object_values_map;

}


sf::IntRect sql::get_collision_objects(std::vector<std::string> objects) {
	std::vector<std::string>not_walkable = get_data("sprites", "name", "walkable", "0");
	std::vector<sf::IntRect>collision_rects;
	std::string temp_query_string;
	std::ostringstream ostring_query;

	ostring_query
		<< "SELECT " << "size_x"
		<< " FROM " << "sprites"
		<< " WHERE " << "name" << " == '" << objects.at(1) << "';"

		<< "SELECT " << "size_y"
		<< " FROM " << "sprites"
		<< " WHERE " << "name" << " == '" << objects.at(1) << "';";


	temp_query_string = ostring_query.str();
	std::vector<std::string>values = execute_query_with_return(temp_query_string.c_str());

	for (auto indexer : not_walkable) {
		if (indexer == objects.at(1)) {
			//std::cout << objects.at(1) << "\t";
			return 
				sf::IntRect(
					std::stoi(objects.at(2)),
					std::stoi(objects.at(3)), 
					std::stoi(values.at(0)),
					std::stoi(values.at(1))
				)
			;
		}
	}
	
	
	


}


std::vector<std::string> sql::get_player_value(std::string player_id) {
	/*
	name
	sprite_id
	map
	level
	pos_x
	pos_y
	faction_id
	*/
	std::string temp_query_string;
	std::ostringstream ostring_query;

	ostring_query
		<< "SELECT " << "name"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";"

		<< "SELECT " << "sprites.path"
		<< " FROM " << "sprites, player"
		<< " WHERE " << "sprites.id" << " == " << "player.sprite_id"
		<< " AND " << "player.id" << " == " << player_id << ";"

		<< "SELECT " << "map"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";"

		<< "SELECT " << "level"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";"

		<< "SELECT " << "position_x"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";"

		<< "SELECT " << "position_y"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";"

		<< "SELECT " << "faction_id"
		<< " FROM " << "player"
		<< " WHERE " << "id" << " == " << player_id << ";";

	temp_query_string = ostring_query.str();

	return execute_query_with_return(temp_query_string.c_str());
}


std::vector<std::string> sql::get_music(std::string map_id) {
	std::ostringstream query;
	query << "SELECT music.path"
		<< " FROM maps, music"
		<< " WHERE maps.id == " << map_id
		<< " AND maps.music_id == music.id;";

	std::string query_string = query.str();

	std::cout << "Buffering music" << std::endl;

	return execute_query_with_return(query_string.c_str());
}



std::vector<std::string> sql::get_quest_text(std::string quest_id, std::string part) {

	std::ostringstream query;
	query << "SELECT text"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id
		<< " AND part == " << part << ";"
		<< "SELECT text1"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id
		<< " AND part == " << part << ";"
		<< "SELECT text2"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id
		<< " AND part == " << part << ";"
		<< "SELECT text3"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id
		<< " AND part == " << part << ";"
		<< "SELECT text4"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id
		<< " AND part == " << part << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}


std::vector<std::string> sql::get_quest_parts(std::string quest_id) {
	std::ostringstream query;
	query << "SELECT part"
		<< " FROM quest_stories"
		<< " WHERE quest_id == " << quest_id << ";";

	std::string query_string = query.str();
	return execute_query_with_return(query_string.c_str());
}





