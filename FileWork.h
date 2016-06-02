#ifndef FILEWORK_H
#define FILEWORK_H
#include <iostream>
#include <string>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <sstream>
#include <deque>

using namespace std;

// this class work with file

class FileWork {
	ofstream out;
	ifstream in;
	string path, buf, ret;
	sf::Text t;
	std::vector<int> info;
	std::vector<std::string> players_names;
	int count{ 0 };
	void read_information();
public:
	FileWork();
	std::string create_new_player(const string &name);
	void delete_player(const string &name);
	std::vector<int> load_player();

	void create_temporary_data(const std::string &s);
	void delete_temporary_data();
	std::string read_temporary_data();

	std::vector<std::string> load_players_names();
	int num_of_names();
	void change_info_player(const string &name, const vector<int> &info);
};

#endif 