/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 4th June 2022 9:55:49 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Entities/Entity.hpp"


Entity::Entity(/* args */)
{
	
}

Entity::~Entity()
{
}

void	Entity::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01.png"));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

void	Entity::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	(void)mDeltaTime;
	(void)pEventHandler;
	mPosition += mVelocity;
	mSprite.setPosition(mPosition);
	if (mAnimations.size())
	{
		mAnimations[mCurrentAnimation].Update();
		sf::IntRect rect = mAnimations[mCurrentAnimation].GetCurrentFrame();
		mSprite.setTextureRect((mFacingLeft) ? sf::IntRect(rect.left + 64, rect.top, -rect.width, rect.height) : rect);
	}
	mVelocity.y += (25.f * mDeltaTime);
	mCurrentAnimation = eAnimationAction::IDLE;
	if (mOnGround)
		mFallClock.restart();
}

void	Entity::Render(Yuna::Core::Window *pWindow)
{
	if (mEquipedItem)
		mEquipedItem->Render(pWindow);
	pWindow->Draw(mSprite);

	if (mPath.size())
	{
		sf::CircleShape shape(10.f);
		shape.setPosition(mPath.back().mPosition + sf::Vector2f(22, 22));
		shape.setFillColor(sf::Color::Yellow);
		pWindow->Draw(shape);

	}
}

void	Entity::Attack(Entity *pTarget)
{
	(void)pTarget;
}

/**
 * Controls
 **/
void	Entity::WalkLeft(float mDeltaTime)
{
	mVelocity.x -= mSpeed * mDeltaTime * ((mOnGround) ? 1.0f : 0.5f);
	mFacingLeft = true;
	mCurrentAnimation = eAnimationAction::WALK;
}

void	Entity::WalkRight(float mDeltaTime)
{
	mVelocity.x += mSpeed * mDeltaTime * ((mOnGround) ? 1.0f : 0.5f);
	mFacingLeft = false;
	mCurrentAnimation = eAnimationAction::WALK;
}

void	Entity::Jump(float mDeltaTime)
{
	mVelocity.y = -(mJumpForce * mDeltaTime);
}

