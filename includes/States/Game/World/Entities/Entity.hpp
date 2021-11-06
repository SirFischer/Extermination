/*
 * File: Entity.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:07 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 5:53:38 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"

class Entity
{
protected:
	sf::Sprite		mSprite;
	sf::Vector2f	mPosition = sf::Vector2f(100, -400);
	sf::Vector2f	mVelocity = sf::Vector2f(0, 0);
	float			mSpeed = 100;
	bool			mOnGround = false;
	
public:
	friend class Map;

	Entity(/* args */);
	~Entity();

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);

	virtual void	Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime);
	virtual void	Render(Yuna::Core::Window *pWindow);

	sf::Vector2f	GetPosition() {return (mPosition);}
	sf::Vector2f	GetVelocity() {return (mVelocity);}
	sf::FloatRect	GetGlobalBounds() {return (mSprite.getGlobalBounds());}
};

