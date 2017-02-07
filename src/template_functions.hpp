#pragma once

#include <sstream>
#include <string>
template<typename T>
T string_to_number(const std::string& numberAsString){
	T valor;

	std::stringstream stream(numberAsString);
	stream >> valor;
	if (stream.fail()) {
		std::runtime_error e(numberAsString);
		throw e;
	}
	return valor;
}