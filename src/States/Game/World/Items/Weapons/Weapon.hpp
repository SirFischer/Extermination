/*
 * File: Weapon.hpp
 * Project: Extermination
 * File Created: Monday, 24th January 2022 6:59:39 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 17th December 2022 10:17:12 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Item.hpp"
#include "ProjectileManager.hpp"

class Weapon : public Item
{
private:
	float				mDamage = 20.f;
	float				mBulletSpeed = 850.f;
	float				mShootingSpeed = 8.f;
	sf::Clock			mCooldownClock;
	sf::Sprite			mSprite;

public:
	Weapon(Yuna::Core::ResourceManager *pResourceManager);
	~Weapon();

	void	Shoot(float pAngle, sf::Vector2f pPos);

	void	Render(Yuna::Core::Window *pWindow);
};

