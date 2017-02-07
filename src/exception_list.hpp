#pragma once

#include <iostream>

class end_of_file : public std::exception {};



class database_not_found : public std::exception{
private:
	std::string s;
public:
	database_not_found() :
		s(std::string("Error: Database could not be opend.\n"))
	{}
	const char * what() const override {
		return s.c_str();
	}

};


class invalid_position : public std::exception {
private:
	std::string s;
public:
	invalid_position(char c):
		s(std::string("invalid position character [") + c + "]\n")
	{}
	const char * what() const override {
		return s.c_str();
	}

};

class unknown_shape : public std::exception {
private:
	std::string s;
public:
	unknown_shape(const std::string & name):
		s(std::string( "unknown shape [" ) + name + "]\n")
	{}

	const char * what() const override {
		return s.c_str();
	}

};

class unknown_tile : public std::exception {
private:
	std::string s;
public:
	unknown_tile(const std::string & name) :
		s(std::string("unknown color [") + name + "]\n")
	{}

	const char * what() const override {
		return s.c_str();
	}

};


