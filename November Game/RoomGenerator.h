#ifndef ROOM_GENERATOR_H
#define ROOM_GENERATOR_H
#include "Room.h"
#include <vector>
#include <random>
#include "gTileMap.h"
namespace LevelGenerator
{

class RoomGenerator
{
public:
	void generateRooms(int levelWidth, int levelHeight, int maxTries);
	void insertRoomsIntoTilemap(gTileMap &gTileMap);
	std::vector<Room> rooms;
private:
	bool overlapsOtherRoom(Room room);
	void generateEmptyRooms(int levelWidth, int levelHeight, int numOfTries);
	int maxRoomSize = 14;
};


}
#endif