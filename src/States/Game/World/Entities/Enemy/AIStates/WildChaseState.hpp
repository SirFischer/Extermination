#pragma once

#include "AIState.hpp"
#include <SFML/System/Clock.hpp>

class WildChaseState : public AIState {
	private:
		sf::Clock			mJumpClock;
		sf::Clock			mChaseClock;
		sf::Time			mChaseTime = sf::seconds(5.f);

	public:
		WildChaseState();

		void Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime);

};
