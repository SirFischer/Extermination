/*
 * File: Weapon.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:35:05 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 17th December 2022 10:17:23 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Weapon.hpp"

Weapon::Weapon(Yuna::Core::ResourceManager *pResourceManager)
{
	mTexturePath = "assets/images/player/gun.png";
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/crosshair.png"));
	
	mIcon.setTexture(*pResourceManager->LoadTexture(mTexturePath));
	mIcon.setScale(0.8f, 0.8f);
}

Weapon::~Weapon()
{
	
}

void	Weapon::Shoot(float pAngle, sf::Vector2f pPos)
{
	if ((1.f / mShootingSpeed) > mCooldownClock.getElapsedTime().asSeconds())
		return ;
	mCooldownClock.restart();
	auto bullet = new Projectile;
	bullet->mAngle = pAngle;
	bullet->mPos = pPos;
	bullet->mVelocity = sf::Vector2f(
		std::cos((pAngle / 180.f) * M_PI) * mBulletSpeed,
		std::sin((pAngle / 180.f) * M_PI) * mBulletSpeed);
	ProjectileManager::AddProjectile(bullet);
}

void	Weapon::Render(Yuna::Core::Window *pWindow)
{
	sf::Vector2f	pos = pWindow->GetViewMousePos();
	mSprite.setPosition(pos - sf::Vector2f(32, 32));
	pWindow->Draw(mSprite);
}
