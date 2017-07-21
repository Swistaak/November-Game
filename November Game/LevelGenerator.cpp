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
		generateEntities();
		saveLevelToFile(outputFile);
	}

	int LevelGenerator::getCoinsCount()
	{
		return coinsCount;
	}

	void LevelGenerator::generateLevel(int width, int height)
	{
		roomGenerator.generateRooms(width, height, 2000);
		roomGenerator.insertRoomsIntoTilemap(tileMap);
		mazeGenerator.generateMaze(tileMap);
		mazeGenerator.createConnectors(tileMap, roomGenerator.rooms);
		mazeGenerator.removeDeadEnds(tileMap);
		roomGenerator.removeRoomsWithoutConnectors(tileMap);

	}
	void LevelGenerator::generateEntities()
	{
		entityGenerator.generatePlayer(tileMap, roomGenerator.rooms);
		entityGenerator.generateEntities(tileMap,roomGenerator.rooms);
		entityGenerator.generateEnemy(tileMap, roomGenerator.rooms);
		coinsCount = entityGenerator.getCoinsCount();
	}
	void LevelGenerator::saveLevelToFile(std::string outputFileName)
	{
		sf::Image image;
		image.create(2*tileMap.getWidth(), 2*tileMap.getHeight());
		for (int y = 0; y < tileMap.tiles[0].size(); y++)
		{
			for (int x = 0; x < tileMap.tiles.size(); x++)
			{
				sf::Color color(tileMap.tiles[x][y].tile.tileType,0, tileMap.tiles[x][y].tile.tileType * 64);
				sf::Color colorWithEntity(tileMap.tiles[x][y].tile.tileType, tileMap.tiles[x][y].entity, tileMap.tiles[x][y].tile.tileType * 64);
				if (tileMap.tiles[x][y].entity == static_cast<int>(GameTag::PLAYER))
				{
					colorWithEntity.b = 0;
					std::cout << "Player spawn pos : " << 2 * x * 64 << "," << (2 * y + 1) * 64 << std::endl;
				}

				image.setPixel(2*x, 2*y, color);
				image.setPixel(2*x, 2*y+1, colorWithEntity);
				image.setPixel(2*x+1, 2*y, color);
				image.setPixel(2*x+1, 2*y+1, color);
			}
		}
		image.saveToFile(outputFileName);
	}
}