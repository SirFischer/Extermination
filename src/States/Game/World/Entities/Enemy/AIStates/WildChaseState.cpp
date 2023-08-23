#include "WildChaseState.hpp"
#include "Entity.hpp"

WildChaseState::WildChaseState()
{

}

void WildChaseState::Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime)
{
	if (mChaseClock.getElapsedTime() > mChaseTime)
	{
		pStates->pop();
		return ;
	}
	sf::Vector2f position = pEntity->GetPosition();
	auto target = pEntity->GetTarget();
	const sf::Vector2f targetPos = target ? target->GetPosition() : sf::Vector2f(0, 0);

	if (targetPos.x > position.x)
		pEntity->WalkRight(pDeltaTime);
	if (targetPos.x < position.x)
		pEntity->WalkLeft(pDeltaTime);
	if (targetPos.y <= position.y - 32)
		pEntity->Jump(pDeltaTime);
	if (mJumpClock.getElapsedTime().asSeconds() > 2.f)
	{
		pEntity->Jump(pDeltaTime);
		mJumpClock.restart();
	}

}
