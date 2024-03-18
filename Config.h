#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <map>


class Config {
public: 
	Config();
	std::vector<std::string> getMoveFolderPaths();
	std::vector<std::pair <std::string, int>> getDeleteFolderPathsAndDays();
	std::vector <std::string> getExcludeFileTypes();
	std::vector <std::pair<std::string, int>> getAmendFolderPathsAndDays();
	
private:
	std::vector<std::string> split(const std::string& string, char delimiter = ' ');
	std::vector <std::map <std::string, std::string >> moveInstructions;
	std::vector <std::map <std::string, std::string >> deleteInstructions;
	std::vector <std::map <std::string, std::string >> excludeInstructions;
	std::vector <std::map <std::string, std::string >> amendInstructions;
	void addInstruction(std::string line);
	void readFile();
	
};