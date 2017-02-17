#ifndef DEBUG_H
#define DEBUG_H
#include <SFML\System.hpp>
class Debug
{
public:

	Debug();
	bool grid{ false };
	void delay(float seconds);
};
extern Debug* debug;
#endif