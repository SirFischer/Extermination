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

#include <algorithm>
#include <limits>


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
	mBuyingPower = (uint16_t)std::min((float)std::numeric_limits<uint16_t>::max(), mBuyingPower * mBuyingPowerIncrease);
	mWaveNumber++;
	mAutoLaunchTimer = mAutoLaunchDelay;
	
	while (currentBuyingPower > 10)
	{
		// Only consider affordable types: picking blindly among all types can
		// spin forever once an unaffordable type exists in the dictionary.
		std::vector<size_t> affordable;
		for (size_t i = 0; i < mEnemyTypes.size(); i++)
			if (mEnemyTypes[i].mPrice <= currentBuyingPower)
				affordable.push_back(i);
		if (affordable.empty())
			break ;
		size_t random = affordable[rand() % affordable.size()];
		currentBuyingPower -= mEnemyTypes[random].mPrice;
		//add type and powerlevel to spawn queue TODO when adding more enemies
		if (mEnemyTypes[random].mType == "Enemy")
			mEntityManager->SpawnEnemy<Enemy>();
		else if (mEnemyTypes[random].mType == "Dog")
			mEntityManager->SpawnEnemy<Dog>();
	}
}

void	WaveManager::Update(float pDeltaTime)
{
	//The countdown only runs between waves: while enemies are alive a wave is
	//still in progress, so the timer stays parked at its full value.
	if (mEntityManager->GetEnemyCount() > 0)
	{
		mAutoLaunchTimer = mAutoLaunchDelay;
		return ;
	}

	mAutoLaunchTimer -= pDeltaTime;
	if (mAutoLaunchTimer <= 0.f)
		NextWave();
}
