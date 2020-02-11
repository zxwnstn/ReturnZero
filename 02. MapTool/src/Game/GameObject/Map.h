﻿#pragma once

#include "Tile.h"

class Map
{
public:
	Map() {};
	Map(std::vector<Tile> _tiles, int _width, int _height);
	~Map() {};

public:
	void init(std::string _fileName);
	TileType getTileTypeFromIdex(int _x, int _y);
	std::vector<class Tile>& getTiles() { return m_tiles; }

public:
	void render(HDC hdc);
	void update(float _deltaTime);
	void debugRender(HDC hdc);
	void afterRender(HDC hdc);

private:
	int m_width;
	int m_height;

	std::vector<Tile> m_tiles;
};