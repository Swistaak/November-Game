#ifndef GENERATORTILEMAP_H
#define GENERATORTILEMAP_H
#include "Tile.h"
#include <vector>
namespace LevelGenerator
{
	class gTileMap
	{
	public:
		gTileMap();
		void init(int width, int height);
		std::vector<std::vector<GeneratorTile>> tiles;
		int numOfNeighbourTiletypes(int xPos, int yPos, TileType tileType);
		int numOfNeighbourTiletypes(int xPos, int yPos, TileType tileType, int regionId);
		int numOfNearbyTiles(int xPos, int yPos, TileType tileType);
		int getWidth();
		int getHeight();
	private:

		int levelWidth;
		int levelHeight;
	};
}

#endif