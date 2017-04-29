#include "LevelGenerator.h"
namespace LevelGenerator
{
	LevelGenerator::LevelGenerator()
	{
	}
	void LevelGenerator::generateAndSave(int width, int height, std::string outputFile)
	{
		tileMap.init(width, height);
		generateLevel(width, height);
		saveLevelToFile(outputFile);
	}

	void LevelGenerator::generateLevel(int width, int height)
	{
		roomGenerator.generateRooms(width, height, 5000);
		roomGenerator.insertRoomsIntoTilemap(tileMap);
		mazeGenerator.generateMaze(tileMap);
		mazeGenerator.createConnectors(tileMap, roomGenerator.rooms);
		mazeGenerator.removeDeadEnds(tileMap);

	}
	void LevelGenerator::saveLevelToFile(std::string outputFileName)
	{
		sf::Image image;
		image.create(tileMap.getWidth(), tileMap.getHeight());
		for (int y = 0; y < tileMap.tiles[0].size(); y++)
		{
			for (int x = 0; x < tileMap.tiles.size(); x++)
			{
				sf::Color color(tileMap.tiles[x][y].tile.tileType, tileMap.tiles[x][y].tile.tileType * 64, tileMap.tiles[x][y].tile.tileType * 64);
				image.setPixel(x, y, color);
			}
		}
		image.saveToFile(outputFileName);
	}
}