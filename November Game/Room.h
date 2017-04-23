#ifndef ROOM_H
#define ROOM_H
#include <SFML\Graphics.hpp>
namespace LevelGenerator
{
	class Room
	{
	public:
		Room(int x,int y,int w,int h) : x(x), y(y), w(w), h(h) {}
		bool intersects(Room room)
		{
			sf::IntRect rectA(x+1, y+1, w-1, h-1);
			sf::IntRect rectB(room.x+1, room.y+1, room.w-1, room.h-1);
			if (rectA.intersects(rectB))
				return true;
			return false;
			
		}
		void setIndex(int newIndex)
		{
			roomIndex = newIndex;
		}
		int getIndex()
		{
			return roomIndex;
		}
		int x;
		int y;
		int w;
		int h;
		bool hasConnectorWith(int mazeRegionIndex)
		{
			for (auto it = connectors.begin(); it != connectors.end(); it++)
			{
				if ((*it) == mazeRegionIndex) return true;
			}
			return false;
		}
		std::vector<int> connectors;

	private:
		int roomIndex;

	};
}

#endif