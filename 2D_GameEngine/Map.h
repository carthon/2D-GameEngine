#pragma once
#include <string>

class Map {
public:
	Map(std::string id, int mapscale, int tilesize);
	~Map();

	void LoadMap(std::string path);
	void AddTile(int srcX, int srcY, int xpos, int ypos);
	int GetSizeX();
	int GetSizeY();
private:
	std::string tilesetFile;
	int mapScale, tileSize, scaledSize, sizeX, sizeY;
};