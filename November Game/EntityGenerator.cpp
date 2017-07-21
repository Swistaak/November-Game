#include "EntityGenerator.h"

LevelGenerator::EntityGenerator::EntityGenerator()
{
}

void LevelGenerator::EntityGenerator::generateEntities(gTileMap & gTileMap, std::vector<Room> rooms)
{
	
	std::mt19937 eng(rd());
	for (auto it = rooms.begin(); it < rooms.end(); it++)
	{
		if (!it->spawn)
		{
			std::uniform_int_distribution<> distrX(it->x+1, it->x + it->w-1);
			std::uniform_int_distribution<> distrY(it->y+1, it->y + it->h-1);
			std::uniform_int_distribution<> distrMaxItems(1, 6);
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
			coinsCount += itemsCount;
		}

	}
}

void LevelGenerator::EntityGenerator::generatePlayer(gTileMap & gTileMap, std::vector<Room> &rooms)
{
	std::mt19937 eng(rd());

	while (!generatedPlayer)
	{
		for (auto it = rooms.begin(); it < rooms.end(); it++)
		{
			if (it->x < gTileMap.getWidth() / 2 && it->y < gTileMap.getHeight() / 2)
			{
				std::uniform_int_distribution<> distrX(it->x+1, it->x + it->w-1);
				std::uniform_int_distribution<> distrY(it->y+1, it->y + it->h-1);
				int x = distrX(eng);
				int y = distrY(eng);
				
				if (gTileMap.tiles[x][y].entity == 0 && gTileMap.tiles[x][y].tile.tileType == ROOM_FLOOR)
				{
					
					gTileMap.tiles[x][y].entity = static_cast<int>(GameTag::PLAYER);
					generatedPlayer = true;
					it->spawn = true;
					break;
				}
			}
		}
		
	}
}

void LevelGenerator::EntityGenerator::generateEnemy(gTileMap & gTileMap, std::vector<Room> rooms)
{
	std::mt19937 eng(rd());
	for (auto it = rooms.begin(); it < rooms.end(); it++)
	{
		if (!it->spawn)
		{

			std::uniform_int_distribution<> distrX(it->x+1, it->x + it->w-1);
			std::uniform_int_distribution<> distrY(it->y+1, it->y + it->h-1);
			std::uniform_int_distribution<> distrMaxItems(1, 1);
			int maxItems = distrMaxItems(eng);
			int itemsCount = 0;

			while (itemsCount < maxItems)
			{
				int x = distrX(eng);
				int y = distrY(eng);
				if (gTileMap.tiles[x][y].entity == 0 && gTileMap.tiles[x][y].tile.tileType == ROOM_FLOOR)//&& gTileMap.numOfNeighbourTiletypes(x,y,WALL) == 1)
				{
					gTileMap.tiles[x][y].entity = static_cast<int>(GameTag::ENEMY);

					itemsCount++;
				}
			}
		}
	}
}

int LevelGenerator::EntityGenerator::getCoinsCount()
{
	return coinsCount;
}
