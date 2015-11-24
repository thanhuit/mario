#pragma once

#include"rapidxml\rapidxml.hpp"
#include"rapidxml\rapidxml_utils.hpp"

#include<string>
#include<vector>
#include<utility>
#include<map>

#include"RecF.h"

#define VERSION "1.0"

class Parser{
private:
	char* fileName;
	int mapwidth;
	int mapheight;
	//bool fire_direct;

public:
	Parser(char* fileName);
	Parser();
	virtual ~Parser();

	rapidxml::xml_node<>* root_node;

	void ReadMap(int &_width, int &_height, int* &_mapArr, RecFList &_collisionRecs);
};