/*
 * File: WaveManager.hpp
 * File Created: Sunday, 26th February 2023 2:42:00 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 2:47:31 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2023 Deep Vertic
 */

#pragma once
#include <stdint.h>
#include "EntityManager.hpp"
#include "Enemy.hpp"

class WaveManager
{
private:
	EntityManager *mEntityManager;

	uint16_t mWaveNumber = 0;
	uint16_t mWaveSize = 5;
	
public:
	WaveManager(EntityManager *pEntityManager);
	~WaveManager();

	void NextWave();

};


