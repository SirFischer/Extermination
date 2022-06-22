/*
 * File: Weapon.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:59:39 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 21st June 2022 5:52:41 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"

class Weapon : public Item
{
private:
	float	mDamage = 20.f;

public:
	Weapon(/* args */);
	~Weapon();

	void	Render(Yuna::Core::Window *pWindow);
};

