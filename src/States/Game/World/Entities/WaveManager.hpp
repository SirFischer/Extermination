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
#include <string>
#include "EntityManager.hpp"
#include "Enemy.hpp"

class WaveManager
{
private:
	EntityManager *mEntityManager;

	uint16_t mWaveNumber = 0;
	uint16_t mBuyingPower = 20;
	float mBuyingPowerIncrease = 1.2;

	struct EnemyType {
		uint16_t	mPrice;
		uint16_t	mPowerLevel;
		std::string	mType;
	};

	std::vector<EnemyType> mEnemyTypes;

	void	initDictionary();
	
public:
	WaveManager(EntityManager *pEntityManager);
	~WaveManager();

	void NextWave();

};


