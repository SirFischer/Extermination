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
}

WaveManager::~WaveManager()
{
}

void	WaveManager::NextWave()
{
	mWaveNumber++;
	
	for (uint16_t i = 0; i < mWaveSize; i++)
	{
		mEntityManager->SpawnEnemy();
	}
}