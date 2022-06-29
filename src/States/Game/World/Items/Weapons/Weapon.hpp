/*
 * File: Weapon.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:59:39 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 23rd June 2022 8:05:37 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"

class Weapon : public Item
{
private:
	float		mDamage = 20.f;
	sf::Sprite	mSprite;

public:
	Weapon(Yuna::Core::ResourceManager *pResourceManager);
	~Weapon();

	void	Render(Yuna::Core::Window *pWindow);
};

