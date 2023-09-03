#pragma once

#include "AIState.hpp"

class AttackState : public AIState {
	private:

	public:
		AttackState();

		void Update(Entity *pEntity, std::stack<std::unique_ptr<AIState>> *pStates, float pDeltaTime);



};