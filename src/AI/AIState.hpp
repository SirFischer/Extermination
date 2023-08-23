#pragma once
#include <memory>
#include <stack>

class Entity;

class AIState
{
protected:
	AIState(/* args */);
	
public:
	virtual ~AIState();

	virtual void	Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime) = 0;
};
