/*
 * File: Enemy.cpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:45:02 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 4th June 2022 12:56:36 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Enemy/Enemy.hpp"


Enemy::Enemy()
{
	mType = EntityType::ENEMY;
	mSpeed = 60;
}

Enemy::~Enemy()
{
}

void	Enemy::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/enemy/Zombie.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);
	mPosition.x = random() % 500;
	mPosition.y = -random() % 500;
}

void	Enemy::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	Entity::Update(pEventHandler, mDeltaTime);

	/**
	 * Path-finding
	 **/
	if (mPath.size() && mState == EnemyState::CHASE)
	{
		//This is for recalcs so it doesn't move backwards if it's allready on the next node!
		if (mPath.size() > 2)
		{
			if (mSprite.getGlobalBounds().contains(mPath.at(1).mPosition + sf::Vector2f(32, 32)))
			{
				mPath.pop_back();
				mPath.pop_back();
			}
		}
		if (mSprite.getGlobalBounds().contains(mPath.back().mPosition + sf::Vector2f(32, 32)))
			mPath.pop_back();

		if (mPath.size())
		{
			if (mPath.back().mPosition.x > mPosition.x)
				WalkRight(mDeltaTime);
			if (mPath.back().mPosition.x < mPosition.x)
				WalkLeft(mDeltaTime);
			if (mPath.back().mPosition.y <= mPosition.y - 32 && mOnGround)
				Jump(mDeltaTime);
			if (mPath.back().mIsBreakable && mPath.back().mParentObject)
			{
				mPath.back().mParentObject->TakeDamage(1.f);
				if (mPath.back().mParentObject->GetHealth() <= 0)
					mPath.pop_back();
			}
		}
	}
	else if (mState == EnemyState::WILD_CHASE || mPath.size() <= 2)
	{
		if (mTarget.x > mPosition.x)
			WalkRight(mDeltaTime);
		if (mTarget.x < mPosition.x)
			WalkLeft(mDeltaTime);
		if (mTarget.y <= mPosition.y - 32 && mOnGround)
			Jump(mDeltaTime);
	}
	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}

