#pragma once

#include "AIState.hpp"

class ChaseState : public AIState {
	private:

	public:
		ChaseState();

		void Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime);



};