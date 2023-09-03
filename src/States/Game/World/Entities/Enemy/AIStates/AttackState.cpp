#include "AttackState.hpp"
#include "Entity.hpp"

AttackState::AttackState()
{
	mState = State::ATTACK;
}

void AttackState::Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime)
{
	(void)pStates;

	auto path = pEntity->GetCurrentPath();

	if (!path->size())
		return ; //No path, maybe make them IDLE? 

	auto position = pEntity->GetPosition();
	sf::FloatRect globalBounds = pEntity->GetGlobalBounds();

	//remove goal posts as you go to follow next node
	if (path->size() > 2)
	{
		if (globalBounds.contains(path->at(1).mPosition + sf::Vector2f(32, 32)))
		{
			path->pop_back();
			path->pop_back();
		}
	}

	if (globalBounds.contains(path->back().mPosition + sf::Vector2f(32, 32)))
	{
		path->pop_back();
	}

	//navigate to next node
	if (path->size())
	{
		if (path->back().mPosition.x > position.x)
			pEntity->WalkRight(pDeltaTime);
		if (path->back().mPosition.x < position.x)
			pEntity->WalkLeft(pDeltaTime);
		if (path->back().mPosition.y <= position.y - 32)
			pEntity->Jump(pDeltaTime);
		if (path->back().mIsBreakable && path->back().mParentObject)
		{
			path->back().mParentObject->TakeDamage(1.f);
			if (path->back().mParentObject->GetHealth() <= 0)
				path->pop_back();
		}
	}
}
