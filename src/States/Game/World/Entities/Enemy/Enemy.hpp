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
#include "../../Map/Map.hpp"
#include <stack>

//AIStates
#include "ChaseState.hpp"
#include "WildChaseState.hpp"

enum class EnemyState {
	IDLE,
	CHASE,
	WILD_CHASE,
	ATTACK
};

class Enemy : public Entity
{
private:
	EnemyState								mState = EnemyState::ATTACK;
	std::stack<std::unique_ptr<AIState>>	mAIStates;

	void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	void	LoadAnimations();


	
public:
	Enemy();
	~Enemy();

	void			TakeDamage(float pDamage);

	void			SetEnemyState(const EnemyState& pState){mState = pState;}

	EnemyState		GetEnemyState(){return (mState);}


	void			Init(Yuna::Core::ResourceManager *pResourceManager);

};

