/*
 * File: Player.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:50 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 2nd November 2021 9:19:13 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Player.hpp"


Player::Player(/* args */)
{
}

Player::~Player()
{
}

void	Player::Update(Yuna::Core::EventHandler *pEventhandler, float mDeltaTime)
{
	
	mPosition += mVelocity;
	mSprite.setPosition(mPosition);
	
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_RIGHT))
		mVelocity.x += mSpeed * mDeltaTime;
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_LEFT))
		mVelocity.x -= mSpeed * mDeltaTime;
	if (pEventhandler->GetEventState((uint32_t)eAction::JUMP))
		mVelocity.y -= mSpeed * mDeltaTime;
	if (pEventhandler->GetEventState((uint32_t)eAction::CROUCH))
		mVelocity.y += mSpeed * mDeltaTime;
	//mVelocity.y += 0.2f;
	mVelocity *= 0.9f;
}
