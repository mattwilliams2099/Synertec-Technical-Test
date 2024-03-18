#include "pch.h"
#include "Config.h"
#include <sstream>

Config::Config() {
	readFile();
}

void Config::readFile() {
	std::ifstream input;
	input.open("C:\\Temp\\Configuration.ini");
	if (input.is_open()) {
		std::string line;
		while (std::getline(input, line))
		{
			if (line[0] != '[') {
				addInstruction(line);
			}
		}
	}
}

void Config::addInstruction(std::string line) {
	std::vector<std::string> result = split(line);
	std::map<std::string, std::string> map;
	for (std::string line : result) {
		std::vector<std::string> instruction = split(line, '=');
		if (instruction[1][0] == '"' && instruction[1][instruction[1].size() - 1] == '"') {
			instruction[1].erase(0, 1);
			instruction[1].pop_back();
		}
		map[instruction[0]] = instruction[1];
	}	
	
	if (map["Action"] == "Move") {
		moveInstructions.push_back(map);
	}
	else if (map["Action"] == "Delete") {
		deleteInstructions.push_back(map);
	} 
	else if (map["Action"] == "Exclude") {
		excludeInstructions.push_back(map);
	}
	else if (map["Action"] == "Amend") {
		amendInstructions.push_back(map);
	}
}

std::vector<std::string> Config::split(const std::string& string, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream stream(string);
	std::string word;
	while (std::getline(stream, word, delimiter))
	{
		result.push_back(word);
	}
	return result;
}

std::vector<std::string> Config::getMoveFolderPaths()
{
	std::vector<std::string> folderPath;
	for (int i = 0; i < moveInstructions.size(); i++) {
		if (moveInstructions[i].count("FolderPath")) {
			if (moveInstructions[i].count("FileExtensions")) {
				folderPath.push_back(moveInstructions[i]["FolderPath"].append(moveInstructions[i]["FileExtensions"]));
			}
			else {
				folderPath.push_back(moveInstructions[i]["FolderPath"]);
			}
		}
	}
	return folderPath;
}

std::vector <std::pair<std::string, int>> Config::getDeleteFolderPathsAndDays()
{
	std::vector <std::pair<std::string, int>> vector;
	for (int i = 0; i < deleteInstructions.size(); i++) {
		if (deleteInstructions[i].count("FolderPath")) {
			std::pair<std::string, int> pair;
			pair.first = deleteInstructions[i]["FolderPath"];
			if (deleteInstructions[i].count("FileExtensions")) {
				pair.first.append(deleteInstructions[i]["FileExtensions"]);
			}
			if (deleteInstructions[i].count("RetentionDays")) {
				pair.second = stoi(deleteInstructions[i]["RetentionDays"]);
			}
			else {
				pair.second = 0;
			}
			vector.push_back(pair);
		}
	}
	return vector;
}


std::vector <std::string> Config::getExcludeFileTypes()
{
	std::vector <std::string> vector;
	for (int i = 0; i < excludeInstructions.size(); i++) {
		if (excludeInstructions[i].count("FileType")) {
			vector.push_back(excludeInstructions[i]["FileType"]);
		}
	}
	return vector;
}

std::vector <std::pair<std::string, int>> Config::getAmendFolderPathsAndDays()
{
	std::vector <std::pair<std::string, int>> vector;
	for (int i = 0; i < amendInstructions.size(); i++) {
		if (amendInstructions[i].count("FolderPath")) {
			std::pair<std::string, int> pair;
			pair.first = amendInstructions[i]["FolderPath"];
			if (amendInstructions[i].count("RetentionDays")) {
				pair.second = stoi(amendInstructions[i]["RetentionDays"]);
			}
			vector.push_back(pair);
		}
	}
	return vector;
}


