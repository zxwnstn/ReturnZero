﻿#pragma once
#include "Game/GameObject/Map/Map.h"

class MapManager
{
public:
	void init();
	void release();

public:
	void addMap(std::string mapKey, std::string fileName);
	std::shared_ptr<class Map> findMap(std::string mapKey);
	std::shared_ptr<Map> getCurMap() { return curMap; }
	Tile& getNextMapKey(int _x, int _y) { return curMap->getSpecifyTile(_x, _y); }

public:
	TileType getTileTypeFromIndex(int _x, int _y);
	std::string getObjectNameFromIndex(int _x, int _y);

private:
	std::map<std::string, std::shared_ptr<Map>> MapList;
	std::shared_ptr<Map> curMap;

private:
	DECLARE_SINGLE(MapManager)
};

#define MAPMANGER MapManager::GetInst()
