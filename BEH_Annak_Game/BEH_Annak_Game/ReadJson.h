#pragma once
#include <iostream>
#include <fstream>
//#include <nlohmann/json.hpp>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;


class ReadJson
{
public:
	json config;
	ReadJson() {
		ifstream f("configuration.json");
		if (!f) {
			cerr << "Failed to open configuration.json" << endl;
		}
		try {
			f >> config;
		}
		catch (const json::parse_error& e) {
			cerr << "Error parsing JSON: " << e.what() << endl;
		}
	}
	unordered_map<string, int> getTiles() const {
		unordered_map<string, int> tiles;
		if (config.contains("Tiles")) {
			for (const auto& item : config["Tiles"].items()) {
				tiles[item.key()] = item.value().get<int>();
			}
		}
		return tiles;
	}

	template<typename T, typename U>
	unordered_map<T, U> getItems(string category) const;

	int* getTilsSize() const {
		int* tilesSize = new int[2];
		if (config.contains("Sizes")) {
			for (const auto& item : config["Sizes"].items()) {
				if (item.key() == "Tile") {
					tilesSize[0] = item.value()[0].get<int>();
					tilesSize[1] = item.value()[1].get<int>();
				}
			}
		}
		return tilesSize;
	}
};
template<typename T, typename U>
unordered_map<T, U> ReadJson::getItems(string category) const {
	unordered_map<T, U> items;
	if (config.contains(category)) {
		for (const auto& item : config[category].items()) {
			items[item.key()] = item.value().get<int>();
		}
	}
	return items;
}