#include "RoomGenerator.h"
namespace LevelGenerator
{
	void RoomGenerator::generateRooms(int levelWidth, int levelHeight, int maxTries)
	{
		generateEmptyRooms(levelWidth, levelHeight,maxTries);
	}

	void RoomGenerator::insertRoomsIntoTilemap(gTileMap& gTileMap)
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			for (int x = it->x; x != it->x + it->w; x++)
			{
				for (int y = it->y; y != it->y + it->h; y++)
				{
					gTileMap.tiles[x][y].tile = Tile(WALL, 0);
				}
			}
			for (int x = it->x + 1; x != it->x + it->w - 1; x++)
			{
				for (int y = it->y + 1; y != it->y + it->h - 1; y++)
				{
					gTileMap.tiles[x][y].tile = Tile(ROOM_FLOOR, 0);
				}
			}
		}
	}

	void RoomGenerator::removeRoomsWithoutConnectors(gTileMap &gTileMap)
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it->connectors.size() == 0)
			{
				for (int x = it->x; x != it->x + it->w; x++)
				{
					for (int y = it->y; y != it->y + it->h; y++)
					{
						gTileMap.tiles[x][y].tile = Tile(WALL, 0);
					}
				}
				it->deleted = true;
			}
			
		}
		for (int i = 0; i < rooms.size(); i++)
		{
			if (rooms[i].deleted)
			{
				rooms[i] =  std::move(rooms.back());
				rooms.pop_back();
			}
		}
	}

	bool RoomGenerator::overlapsOtherRoom(Room room)
	{
		for (auto it = rooms.begin(); it != rooms.end(); it++)
		{
			if (it->intersects(room))
				return true;
		}
		return false;
	}

	void RoomGenerator::generateEmptyRooms(int levelWidth, int levelHeight, int maxTries)
	{
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(2, (maxRoomSize/2)-1);
		std::uniform_int_distribution<> distrLeft(0, (levelWidth - (maxRoomSize+2)) / 2);
		std::uniform_int_distribution<> distrTop(0, (levelHeight - (maxRoomSize+2)) / 2);

		int roomIndex = 0;
		int tries = 0;
		while (tries < maxTries)
		{
			Room room(distrLeft(eng) * 2 + 1, distrTop(eng) * 2 + 1, distr(eng) * 2 + 1, distr(eng) * 2 + 1);
			if (!overlapsOtherRoom(room))
			{
				room.setIndex(roomIndex);
				rooms.push_back(room);
				roomIndex++;
			}
			tries++;
		}
	}
}