/*
 * File: Player.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:12:50 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 9th January 2022 12:02:32 pm
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

void	Player::LoadAnimations()
{
	//Frame 1
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 0, 64, 64), .mDuration = sf::seconds(0.2f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 0, 64, 64), .mDuration = sf::seconds(0.2f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 0, 64, 64), .mDuration = sf::seconds(0.2f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 0, 64, 64), .mDuration = sf::seconds(0.2f), .mAction = nullptr});
}

void	Player::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01_idle.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	LoadAnimations();
}

void	Player::Update(Yuna::Core::EventHandler *pEventhandler, float mDeltaTime)
{
	Entity::Update(pEventhandler, mDeltaTime);
	mPosition += mVelocity;
	mSprite.setPosition(mPosition);
	
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_RIGHT))
		mVelocity.x += mSpeed * mDeltaTime  * ((mOnGround) ? 1.0f : 0.5f);
	if (pEventhandler->GetEventState((uint32_t)eAction::MOVE_LEFT))
		mVelocity.x -= mSpeed * mDeltaTime * ((mOnGround) ? 1.0f : 0.5f);
	if (pEventhandler->GetEventState((uint32_t)eAction::JUMP) && mOnGround)
		mVelocity.y = -(mSpeed * mDeltaTime) * 10.f;
	if (pEventhandler->GetEventState((uint32_t)eAction::CROUCH))
		mVelocity.y += mSpeed * mDeltaTime;
	mVelocity.y += 0.2f;
	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}
