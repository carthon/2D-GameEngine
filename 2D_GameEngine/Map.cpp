#include "Map.h"
#include "Engine.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;

Map::Map(std::string id, int mscale, int tsize) : tilesetFile(id), mapScale(mscale), tileSize(tsize) {
	scaledSize = mapScale * tileSize;
}

Map::~Map() {
}

void Map::LoadMap(std::string path) {
	char tile;
	std::string info;
	std::fstream mapFile;
	bool endLine = false;

	mapFile.open(path);
	int sizeX, sizeY, srcX, srcY, tileHeight, tileWidth;

	std::cout << "Loading Map:" << std::endl;
	for (int y = 0; y < 6; y++) {
		for (int x = 0; !endLine; x++) {
			mapFile.get(tile);
			if (tile == '\n') {
				endLine = true;
			} else if (tile >= '0' && tile <= '9') {
				info += tile;
			}
		}
		switch (y)
		{
		case 0:
			sizeX = std::stoi(info);
			std::cout << "Map X size: " << sizeX << std::endl;
			info.clear();
			break;
		case 1:
			sizeY = std::stoi(info);
			std::cout << "Map Y size: " << sizeY << std::endl;
			info.clear();
			break;
		case 2:
			tileWidth = std::stoi(info);
			std::cout << "Tile Width: " << tileWidth << std::endl;
			info.clear();
			break;
		case 3:
			tileHeight = std::stoi(info);
			std::cout << "Tile Height: " << tileHeight << std::endl;
			info.clear();
			break;
		}
		endLine = false;
	}

	info.clear();

	std::cout << "Adding Tile info..." << std::endl;
	int coordenadas, x = 0, y = 0;
	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; !endLine; j++) {
			mapFile.get(tile);
			std::cout << tile;
			if (tile >= '0' && tile <= '9') {
				info += tile;
			}
			else if (tile == ',') {
				coordenadas = std::stoi(info);
				srcX = coordenadas % 20;
				srcY = (coordenadas - srcX) / 20;
				//Al ser la textura por píxeles hay que multilicarlo por los numeros de pixeles de altura y anchura
				srcX *= tileSize;
				srcY *= tileSize;
				AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
				x++;
				info.clear();
			}
			else if (tile == '\n') {
				endLine = true;
				x = 0;
				y++;
			}
		}
		endLine = false;
	}
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	mapFile.ignore();
	mapFile.ignore(100, '\n');
	std::cout << "Adding colliders..." << std::endl;
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(tile);
			if (tile == '1') {
				auto& tcol(manager.AddEntity());
				tcol.AddComponent<Collider>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.AddGroup(Engine::groupColliders);
			}
			mapFile.ignore();
		}
		mapFile.ignore();
	}
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.AddEntity());
	tile.AddComponent<Tile>(srcX, srcY, xpos, ypos, tileSize, mapScale, tilesetFile);
	tile.AddGroup(Engine::groupMap);
}

int Map::GetSizeX() { return sizeX * scaledSize; }
int Map::GetSizeY() { return sizeY * scaledSize; }