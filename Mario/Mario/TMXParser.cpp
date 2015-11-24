#include"TMXParser.h"
#include<cstdlib>
#include<iostream>
#include<sstream>


Parser::Parser(char* filename)
{
	fileName = filename;
	//fire_direct = true;
}

Parser::Parser()
{
}

Parser::~Parser()
{
}

void Parser::ReadMap(int &_width, int &_height, int* &arr, RecFList &_collisionRecs)
{
	std::string version = VERSION;
	rapidxml::xml_document<> doc;
	rapidxml::file<> file(fileName);
	doc.parse<0>(file.data());
	//get root nodes
	root_node = doc.first_node("map");

	mapwidth = std::atoi(root_node->first_attribute("width")->value());
	mapheight = std::atoi(root_node->first_attribute("height")->value());
	int count = mapwidth*mapheight;
	arr = new int[count];
	RecFList recList;

	for (rapidxml::xml_node<>* layer_node = root_node->first_node("layer"); layer_node; layer_node = layer_node->next_sibling("layer")) {
		std::string layername = layer_node->first_attribute("name")->value();
		if (layername.compare("Map") == 0)
		{
			int i = 0;
			rapidxml::xml_node<>* data_node = layer_node->first_node("data");
			for (rapidxml::xml_node<>* tile_node = data_node->first_node("tile"); tile_node; tile_node = tile_node->next_sibling("tile")){
				int gid = std::atoi(tile_node->first_attribute("gid")->value());
				arr[i] = gid;
				i++;
			}
		}
	}

	for (rapidxml::xml_node<>* oGroup_node = root_node->first_node("objectgroup"); oGroup_node; oGroup_node = oGroup_node->next_sibling("objectgroup")) {
		std::string name = oGroup_node->first_attribute("name")->value();
		if (name.compare("Collision") == 0)
		{
			for (rapidxml::xml_node<>* object_node = oGroup_node->first_node("object"); object_node; object_node = object_node->next_sibling("object")){
				int x, y, width, height;
				bool blocked = false;
				x = std::atoi(object_node->first_attribute("x")->value());
				y = std::atoi(object_node->first_attribute("y")->value());
				width = std::atoi(object_node->first_attribute("width")->value());
				height = std::atoi(object_node->first_attribute("height")->value());
				char* s = object_node->first_attribute("blocked")->value();
				if (strcmp(s, "True") == 0) blocked = true;
				RecF rec(x, mapheight*32 - y, width, height, blocked);
				recList.push_back(rec);
			}
		}
	}
	_width = mapwidth;
	_height = mapheight;
	_collisionRecs = recList;
}
