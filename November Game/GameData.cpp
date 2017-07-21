#include "GameData.h"

int GameData::getScore()
{
	return mScore;
}

void GameData::changeScore(int value)
{
	mScore += value;
}

int GameData::getCoinsCollected()
{
	return mCoinsCollected;
}

void GameData::setCoinsCollected(int coinsCollected)
{
	mCoinsCollected = coinsCollected;
}

void GameData::setTotalCoins(int totalCoins)
{
	mTotalCoins = totalCoins;
}

int GameData::getTotalCoins()
{
	return mTotalCoins;
}

int GameData::getHealth()
{
	return mHealth;
}

void GameData::setHealth(int health)
{
	mHealth = health;
}

void GameData::setMaxHealth(int maxHealth)
{
	mMaxHealth = maxHealth;
}

int GameData::getMaxHealth()
{
	return mMaxHealth;
}

