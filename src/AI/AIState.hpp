#pragma once
#include <memory>
#include <stack>

class Entity;

class AIState
{
public:
	enum class State
	{
		CHASE,
		WILD_CHASE,
		ATTACK,
		DEAD
	};

protected:
	AIState(/* args */);

	State	mState;
	
public:
	virtual ~AIState();

	virtual void	Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime) = 0;

	State			GetState(){return (mState);}
};
