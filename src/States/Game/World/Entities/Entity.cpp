/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 11th July 2022 9:33:26 pm
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
	pWindow->Draw(mSprite);

	if (Config::mRenderPathNodes && mPath.size())
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

void	Entity::TakeDamage(float pDamage)
{
	mHealth -= pDamage;
}

void	Entity::TakeDamage(float pDamage, float pAngle, float pPower)
{
	TakeDamage(pDamage);
	mVelocity += sf::Vector2f(std::cos((pAngle / 180.f) * M_PI) * pPower, std::sin((pAngle / 180.f) * M_PI) * pPower);
}



void	Entity::ResolveCollision(Entity *pEntity)
{
	if (pEntity == this)
		return ;
	if (sf::FloatRect(mPosition, mSize).intersects(sf::FloatRect(pEntity->mPosition, pEntity->mSize)))
	{
		float pushForce = 1.0f;
		sf::Vector2f delta = mPosition - pEntity->mPosition;
		float distance = Yuna::Math::Distance(mPosition, pEntity->mPosition);
		if (distance != 0)
		{
			mVelocity.x += pushForce * (delta.x / distance);
			mVelocity.y += (pushForce * (delta.y / distance)) / 4.f;
		}
	}
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

