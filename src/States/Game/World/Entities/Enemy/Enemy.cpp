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
	const bool randomState = (random() % 100) < 30;
	if (randomState)
		mAIStates.push(std::make_unique<ChaseState>());
	else
		mAIStates.push(std::make_unique<AttackState>());
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
	if (gotEnraged) {
		mAIStates.push(std::make_unique<ChaseState>());
		mAIStates.push(std::make_unique<WildChaseState>());
	}
	mAnimations.SetCurrentAnimation(eAnimationAction::HURT);

}

void	Enemy::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	Entity::Update(pEventHandler, mDeltaTime);

	mAIStates.top()->Update(this, &mAIStates, mDeltaTime);

	//check if enemy is within range of target and attack

	mVelocity.x *= ((mOnGround) ? 0.9f : 0.93f);
	mOnGround = false;
}

void	Enemy::LoadAnimations()
{
	Animation idleAnimation;
	idleAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	idleAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 0, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	
	Animation walkAnimation;
	walkAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	walkAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	walkAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(128, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	walkAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(192, 64, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	
	Animation fallAnimation;
	fallAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(0, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});
	fallAnimation.AddFrame((AnimationFrame){.mRect = sf::IntRect(64, 128, 64, 64), .mDuration = sf::seconds(0.15f), .mAction = nullptr});

	mAnimations.AddAnimation(eAnimationAction::IDLE, idleAnimation);
	mAnimations.AddAnimation(eAnimationAction::WALK, walkAnimation);
	mAnimations.AddAnimation(eAnimationAction::FALL, fallAnimation);
}