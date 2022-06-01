/*
 * File: Enemy.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:44:10 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 1st June 2022 6:03:34 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "../Entity.hpp"
#include "../../Map/Map.hpp"

enum class EnemyState {
	IDLE,
	CHASE,
	ATTACK
};

class Enemy : public Entity
{
private:
	EnemyState							mState = EnemyState::IDLE;

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);
	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);

	
public:
	Enemy();
	~Enemy();
};

