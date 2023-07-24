/*
 * File: Enemy.cpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:45:02 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 25th February 2023 4:24:05 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Enemy/Enemy.hpp"


Enemy::Enemy()
{
	mType = EntityType::ENEMY;
	mSpeed = 60;
	mBloodColor = sf::Color::Green;
}

Enemy::~Enemy()
{
}

void	Enemy::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/enemy/Soldier_01_tiles-enemy.png"));
	mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);
	mPosition.x = random() % 500 + 20000;
	mPosition.y = -random() % 500 - 200;
	mSpeed = 55.f;
	LoadAnimations();
}

void	Enemy::TakeDamage(float pDamage)
{
	Entity::TakeDamage(pDamage);
	const bool gotEnraged = random() % 100 < 50;
	if (gotEnraged)
		mState = EnemyState::WILD_CHASE;

}

void	Enemy::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	Entity::Update(pEventHandler, mDeltaTime);
	const sf::Vector2f targetPos = mTarget ? mTarget->GetPosition() : sf::Vector2f(0, 0);

	/**
	 * Path-finding
	 **/
	if (mPath.size() && (mState == EnemyState::CHASE || mState == EnemyState::ATTACK))
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
		if (targetPos.x > mPosition.x)
			WalkRight(mDeltaTime);
		if (targetPos.x < mPosition.x)
			WalkLeft(mDeltaTime);
		if (targetPos.y <= mPosition.y - 32 && mOnGround)
			Jump(mDeltaTime);
		if (mJumpClock.getElapsedTime().asSeconds() > 2.f)
		{
			Jump(mDeltaTime);
			mJumpClock.restart();
		}
	}

	//check if enemy is within range of target and attack
	if (mTarget && mTarget->GetType() != EntityType::ENEMY)
	{
		const float distance = sqrt(pow(mPosition.x - mTarget->GetPosition().x, 2) + pow(mPosition.y - mTarget->GetPosition().y, 2));
		if (distance < mRange)
		{
			Attack(mTarget);
		}
	}


	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}

void	Enemy::LoadAnimations()
{
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::IDLE].AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::WALK].AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::FALL].AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	mAnimations[eAnimationAction::FALL].AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
}