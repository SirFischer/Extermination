/*
 * File: Player.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:50 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 30th October 2021 8:47:09 pm
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
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_RIGHT))
		mVelocity.x += mSpeed * mDeltaTime;
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_LEFT))
		mVelocity.x -= mSpeed * mDeltaTime;
	mPosition += mVelocity;
	mSprite.setPosition(mPosition);
}
