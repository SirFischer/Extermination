/*
 * File: Projectile.hpp
 * Project: Extermination
 * File Created: Thursday, 7th July 2022 9:19:37 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 8:56:10 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include <SFML/Graphics.hpp>

#include "ProjectileTypes.hpp"


struct Projectile
{
	ProjectileType	mType = ProjectileType::BULLET;
	sf::Vector2f	mPos = sf::Vector2f(0.f, 0.f);
	sf::Vector2f	mVelocity = sf::Vector2f(1.0f, 0.f);
	sf::Clock		mLifeClock;
	float			mAngle = 0.f;
	float			mDamage = 20.f;
	float			mKnockback = 10.f;
};

