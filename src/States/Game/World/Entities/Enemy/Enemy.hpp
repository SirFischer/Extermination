/*
 * File: Enemy.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:44:10 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 11th July 2022 7:43:57 am
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
	WILD_CHASE,
	ATTACK
};

class Enemy : public Entity
{
private:
	EnemyState							mState = EnemyState::CHASE;
	sf::Clock							mJumpClock;

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);
	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	void			LoadAnimations();

	
public:
	Enemy();
	~Enemy();
};

