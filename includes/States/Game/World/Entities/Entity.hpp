/*
 * File: Entity.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:07 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 23rd October 2021 5:06:45 pm
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
	
public:
	Entity(/* args */);
	~Entity();

	virtual void	Init(Yuna::Core::ResourceManager *pResourceManager);

	virtual void	Update(Yuna::Core::EventHandler *pEventHandler);
	virtual void	Render(Yuna::Core::Window *pWindow);
};

