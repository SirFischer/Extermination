/*
 * File: Enemy.cpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:45:02 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 1st June 2022 4:31:30 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Enemy/Enemy.hpp"


Enemy::Enemy()
{
	mType = EntityType::ENEMY;
	mSpeed = 70;
}

Enemy::~Enemy()
{
}

void	Enemy::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/enemy/Zombie.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
	mPosition.x = random() % 500;
	mPosition.y = -random() % 500;
}

void	Enemy::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	Entity::Update(pEventHandler, mDeltaTime);

	/**
	 * Path-finding
	 **/
	if (mPath.size())
	{
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
		}
	}
	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}

