/*
 * File: Entity.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:07 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 28th February 2022 4:01:59 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"
#include "Animation.hpp"
#include "../Items/Item.hpp"

class Entity
{
protected:
	enum class				eAnimationAction
	{
		IDLE,
		WALK,
		FALL
	};

	sf::Sprite				mSprite;
	sf::Vector2f			mPosition = sf::Vector2f(100, -400);
	sf::Vector2f			mSize = sf::Vector2f(48, 64);
	sf::Vector2f			mOrigin = sf::Vector2f(0, 0);
	sf::Vector2f			mVelocity = sf::Vector2f(0, 0);
	float					mSpeed = 100;
	float					mJumpForce = 650;
	bool					mFacingLeft = false;
	bool					mOnGround = false;
	sf::Clock				mFallClock;
	std::shared_ptr<Item>	mEquipedItem;

	std::map<eAnimationAction, Animation>	mAnimations;
	eAnimationAction						mCurrentAnimation = eAnimationAction::IDLE;
	
public:
	friend class Map;

	Entity(/* args */);
	~Entity();

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);

	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	virtual void	Render(Yuna::Core::Window *pWindow);

	virtual void	Attack(Entity *pTarget);

	void			SetSize(float pX, float pY) {mSize = sf::Vector2f(pX, pY);}
	void			SetOrigin(float pX, float pY) {mOrigin = sf::Vector2f(pX, pY);}

	sf::Vector2f	GetPosition() {return (mPosition);}
	sf::Vector2f	GetVelocity() {return (mVelocity);}
	sf::FloatRect	GetGlobalBounds() {return (sf::FloatRect(mPosition + mOrigin, mSize));}
};

