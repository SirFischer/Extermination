/*
 * File: WaveManager.cpp
 * File Created: Sunday, 26th February 2023 2:42:32 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:29:03 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2023 Deep Vertic
 */

#include "WaveManager.hpp"

WaveManager::WaveManager(EntityManager *pEntityManager)
: mEntityManager(pEntityManager)
{
	initDictionary();
}

WaveManager::~WaveManager()
{
}

void	WaveManager::initDictionary()
{
	//enemy types and powerlevels?
	mEnemyTypes.push_back((EnemyType){.mPrice = 10, .mPowerLevel = 1, .mType = "Enemy"});
	mEnemyTypes.push_back((EnemyType){.mPrice = 20, .mPowerLevel = 2, .mType = "Enemy"});
	mEnemyTypes.push_back((EnemyType){.mPrice = 30, .mPowerLevel = 3, .mType = "Enemy"});
	mEnemyTypes.push_back((EnemyType){.mPrice = 40, .mPowerLevel = 1, .mType = "Other Enemy"});
	mEnemyTypes.push_back((EnemyType){.mPrice = 50, .mPowerLevel = 2, .mType = "Other Enemy"});
	mEnemyTypes.push_back((EnemyType){.mPrice = 60, .mPowerLevel = 3, .mType = "Other Enemy"});
}

void	WaveManager::NextWave()
{
	int currentBuyingPower = mBuyingPower;
	mBuyingPower += mBuyingPowerIncrease;
	mWaveNumber++;
	
	while (currentBuyingPower > 10)
	{
		int random = rand() % mEnemyTypes.size();
		if (mEnemyTypes[random].mPrice <= currentBuyingPower)
		{
			currentBuyingPower -= mEnemyTypes[random].mPrice;
			//add type and powerlevel to spawn queue TODO when adding more enemies
			mEntityManager->SpawnEnemy();
		}
	}
}