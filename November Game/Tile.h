#ifndef TILE_H
#define TILE_H
namespace LevelGenerator
{
	enum TileType
	{
		EMPTY = 0,
		ROOM_FLOOR = 1,
		WALL = 2,
		MAZE_CORRIDOR = 3,
		DOOR = 4,
		CHANGE_TO_EMPTY
	};
	struct Tile
	{
		Tile() : region(0), tileType(EMPTY) {}
		Tile(TileType tileType, int region) : region(region), tileType(tileType) {}
		TileType tileType;
		int region;
	};
	struct GeneratorTile
	{
		Tile tile;
		int entity;
	};



}


#endif
