#ifndef TILE_H
#define TILE_H
namespace LevelGenerator
{
	enum TileType
	{
		EMPTY = -1,
		ROOM_FLOOR = 0,
		WALL = 1,
		MAZE_CORRIDOR = 2,
		DOOR = 3,
		DEBUG = 4,
		CHANGE_TO_EMPTY,
	};
	struct Tile
	{
		Tile() : region(0),tileType(EMPTY){}
		Tile(TileType tileType, int region) : region(region), tileType(tileType) {}
		TileType tileType;
		int region;
	};
}


#endif
