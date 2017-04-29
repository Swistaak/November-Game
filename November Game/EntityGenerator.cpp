#include "EntityGenerator.h"

LevelGenerator::EntityGenerator::EntityGenerator()
{
}

void LevelGenerator::EntityGenerator::generateEntities(gTileMap & gTileMap, std::vector<Room> rooms)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	
	for (auto it = rooms.begin(); it < rooms.end(); it++)
	{
		std::uniform_int_distribution<> distrX(it->x,it->x+it->w);
		std::uniform_int_distribution<> distrY(it->y, it->y + it->h);
		std::uniform_int_distribution<> distrMaxItems(1,6);
		int maxItems = distrMaxItems(eng);
		int itemsCount = 0;
		while (itemsCount < maxItems)
		{
			int x = distrX(eng);
			int y = distrY(eng);
			if (gTileMap.tiles[x][y].entity == 0 && gTileMap.tiles[x][y].tile.tileType == ROOM_FLOOR)
			{
				gTileMap.tiles[x][y].entity = static_cast<int>(GameTag::PICKUP);
				itemsCount++;
			}
		}
	}
}
