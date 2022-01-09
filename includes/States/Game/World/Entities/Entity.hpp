/*
 * File: Entity.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:07 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 9th January 2022 11:35:04 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"
#include "Animation.hpp"

class Entity
{
protected:
	enum class				eAnimationAction
	{
		IDLE,
		WALK
	};

	sf::Sprite				mSprite;
	sf::Vector2f			mPosition = sf::Vector2f(100, -400);
	sf::Vector2f			mSize = sf::Vector2f(48, 64);
	sf::Vector2f			mOrigin = sf::Vector2f(0, 0);
	sf::Vector2f			mVelocity = sf::Vector2f(0, 0);
	float					mSpeed = 100;
	bool					mOnGround = false;

	std::map<eAnimationAction, Animation>	mAnimations;
	eAnimationAction						mCurrentAnimation = eAnimationAction::IDLE;
	
public:
	friend class Map;

	Entity(/* args */);
	~Entity();

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);

	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	virtual void	Render(Yuna::Core::Window *pWindow);

	void			SetSize(float pX, float pY) {mSize = sf::Vector2f(pX, pY);}
	void			SetOrigin(float pX, float pY) {mOrigin = sf::Vector2f(pX, pY);}

	sf::Vector2f	GetPosition() {return (mPosition);}
	sf::Vector2f	GetVelocity() {return (mVelocity);}
	sf::FloatRect	GetGlobalBounds() {return (sf::FloatRect(mPosition + mOrigin, mSize));}
};

