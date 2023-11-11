/*
 * File: Enemy.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:44:10 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 25th February 2023 4:22:57 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "../Entity.hpp"
#include "EnemyState.hpp"
#include "../../Map/Map.hpp"
#include <stack>

//AIStates
#include "ChaseState.hpp"
#include "WildChaseState.hpp"
#include "AttackState.hpp"

class Enemy : public Entity
{
protected:
	std::stack<std::unique_ptr<AIState>>	mAIStates;
	int										mCurrencyDrop = 10;

	void	LoadAnimations();


	
public:
	Enemy();
	~Enemy();

	void			TakeDamage(float pDamage);

	AIState::State	GetEnemyState(){return (mAIStates.top()->GetState());}


	void			Init(Yuna::Core::ResourceManager *pResourceManager);
	void			Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);

};

