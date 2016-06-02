#include "FileWork.h"

void FileWork::read_information()
{
	in.open(path);
	buf.clear();
	char ch;
	while (!in.eof()) {
		in.get(ch);
		buf.push_back(ch);
	}
	in.clear();
	in.close();
}

FileWork::FileWork()
{
	path = "Match3_safe.txt";
}

std::string FileWork::create_new_player(const string &name) {
	read_information();
	if (buf.find(name) != std::string::npos) {
		cout << "This name exist!"; buf.clear();
		ret = "This name is exist";
	}
	else {
		out.open(path, ios::app);
		out << "[" << name << "]\n";
		out << "safe_10000" << endl;
		out << "scores:" << 0 << endl;
		out << name <<"#\n";
		out.close();
		ret = "Success";
	}
	return ret;
	
}

void FileWork::delete_player(const string & name)
{
	read_information();

	if (buf.find("[" + name + "]") != std::string::npos) {
		std::size_t pos = buf.find("[" + name);
		std::size_t size = buf.find(name + "#\n") - pos+name.size()+2;
		
		buf.erase(pos, size);
		buf.pop_back();
		out.open(path);
		out << buf;
		out.close();
	}

}

std::vector<int> FileWork::load_player()
{
	read_information();

	std::size_t pos = buf.find("*");
	ret.clear();
	info.clear();
	pos++;
	while (isalpha(buf[pos])) {	
		ret.push_back(buf[pos]);
		pos++;
	}

	if (buf.find("[" + ret + "]") != std::string::npos && info.empty()) {
		std::string fstr = ret + "]\nsafe_";
		pos = buf.find(fstr)+fstr.size();
		
		while (isdigit(buf[pos])) {
			info.push_back(static_cast<int>(buf[pos])-48);
			pos++;
		}
		pos += 8; 
		fstr.clear();
		while (isdigit(buf[pos])) {
			fstr.push_back(buf[pos]); 
			pos++;
		}
		info.push_back(atoi(fstr.c_str()));
	}
	return info;



}

void FileWork::create_temporary_data(const std::string & s)
{
	out.open(path, ios::app);
	out << "*" << s << endl;
	out.close();
	
}



void FileWork::delete_temporary_data()
{
	read_information();
	std::size_t pos = buf.find("*");
	buf.erase(pos, ret.size() + 1);
	buf.pop_back(); buf.pop_back();
	out.open(path);
	out << buf;
	out.close();
	ret.clear();
}

std::string FileWork::read_temporary_data()
{
	return ret;
}

std::vector<std::string> FileWork::load_players_names()
{
	read_information();

	std::size_t pos = 0;
	std::string localstr;
	players_names.clear();
	while (pos != buf.size()) {
		if (buf[pos] == '[') {
			++pos;
			while (buf[pos] != ']')
				localstr.push_back(buf[pos++]);
			players_names.push_back(localstr);
		}
		
		localstr.clear();
		pos++;
	}
	return players_names;
}

int FileWork::num_of_names()
{
	count = 0;
	in.open(path);
	char ch;
	info.clear();
	while (!in.eof()) {
		in.get(ch);
		if (ch == '[')
			count++;
	}
	in.close();
	return count;
}

void FileWork::change_info_player(const string & name, const vector<int> &inf)
{
	read_information();

	if (buf.find("[" + name + "]") != std::string::npos) {
		std::string fstr = name + "]\nsafe_";
		std::size_t pos = buf.find(fstr) + fstr.size();
		std::size_t pos2;
		int i = 0;
		while (isdigit(buf[pos])) {
			buf[pos] = static_cast<char>(inf[i] + 48);
			pos++; i++;
		}
		pos += 8;
		pos2 = pos;

		fstr.clear(); 
		while (buf[pos2] != '\n'){
			fstr.push_back(buf[pos2]);
			pos2++;
		}
		buf.erase(pos, fstr.size());
		fstr.clear();
		fstr = to_string(inf[5]);
		buf.insert(pos, fstr);
		buf.pop_back();
		out.open(path);
		out << buf;
		out.close();
		
	}
}
