/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 19th February 2023 3:15:28 pm
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
	if (mOnGround) {
		mFallClock.restart();
		mVelocity.y = std::min(mVelocity.y, 0.f);
	}
	mPosition += mVelocity;
	mSprite.setPosition(mPosition.x, mPosition.y);
	if (mAnimations.size())
	{
		mAnimations[mCurrentAnimation].Update();
		sf::IntRect rect = mAnimations[mCurrentAnimation].GetCurrentFrame();
		mSprite.setTextureRect((mFacingLeft) ? sf::IntRect(rect.left + 64, rect.top, -rect.width, rect.height) : rect);
	}
	mVelocity.y += (25.f * mDeltaTime);
	mCurrentAnimation = eAnimationAction::IDLE;
	
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

void	Entity::Attack(std::shared_ptr<Entity> pTarget)
{
	if (!pTarget)
		return ;
	
	if (mAttackClock.getElapsedTime().asSeconds() > mAttackSpeed)
	{
		mAttackClock.restart();
		//calculate angle
		sf::Vector2f delta = pTarget->GetPosition() - mPosition;
		float rotation = -((std::atan2(delta.x, delta.y) / M_PI) * 180.f) - 90.f;
		pTarget->TakeDamage(20.f, pTarget->GetPosition(), rotation, 10);
	}
}

void	Entity::TakeDamage(float pDamage)
{
	mHealth -= pDamage;
}

void	Entity::TakeDamage(float pDamage, sf::Vector2f pPos, float pAngle, float pPower)
{
	TakeDamage(pDamage);
	mVelocity += sf::Vector2f(std::cos((pAngle / 180.f) * M_PI) * pPower, std::sin((pAngle / 180.f) * M_PI) * pPower);
	ParticleManager::AddParticleEffect(
				ParticleEffect(pPos, pPower * 40.f, 2.f, 50.f, (pAngle / 180.f) * M_PI, M_PI / 4.f,
				sf::Color::Red));
}



void	Entity::ResolveCollision(Entity *pEntity)
{
	if (pEntity == this)
		return ;
	if (sf::FloatRect(mPosition, mSize).intersects(sf::FloatRect(pEntity->mPosition, pEntity->mSize)))
	{
		if (pEntity->GetPosition() == mPosition)
		{
			mPosition.x += 1;
			mPosition.y -= 1;
		}
		float pushForce = 1.0f;
		sf::Vector2f delta = mPosition - pEntity->mPosition;
		float distance = Yuna::Math::Distance(mPosition, pEntity->mPosition);
		if (distance != 0)
		{
			mVelocity.x += pushForce * (delta.x / distance);
			//mVelocity.y += -std::abs((pushForce * (delta.y / distance)) / 4.f);
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

