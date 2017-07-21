#ifndef GAMEDATA_H
#define GAMEDATA_H

class GameData
{
public:
	int getScore();
	void changeScore(int value);
	int getCoinsCollected();
	void setCoinsCollected(int coinsCollected);
	void setTotalCoins(int totalCoins);
	int getTotalCoins();
	int getHealth();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	int getMaxHealth();
private:
	int mScore = 0;
	int mCoinsCollected = 0;
	int mTotalCoins = 0;
	int mHealth;
	int mMaxHealth;
};


#endif