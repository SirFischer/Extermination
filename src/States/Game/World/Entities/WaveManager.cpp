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
#include "Dog.hpp"


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
	mEnemyTypes.push_back((EnemyType){.mPrice = 15, .mPowerLevel = 1, .mType = "Dog"});
}

void	WaveManager::NextWave()
{
	int currentBuyingPower = mBuyingPower;
	mBuyingPower *= mBuyingPowerIncrease;
	mWaveNumber++;
	
	while (currentBuyingPower > 10)
	{
		int random = rand() % mEnemyTypes.size();
		if (mEnemyTypes[random].mPrice <= currentBuyingPower)
		{
			currentBuyingPower -= mEnemyTypes[random].mPrice;
			//add type and powerlevel to spawn queue TODO when adding more enemies
			if (mEnemyTypes[random].mType == "Enemy")
				mEntityManager->SpawnEnemy<Enemy>();
			else if (mEnemyTypes[random].mType == "Dog")
				mEntityManager->SpawnEnemy<Dog>();
		}
	}
}