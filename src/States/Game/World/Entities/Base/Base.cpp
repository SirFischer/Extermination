/*
 * File: Base.cpp
 * Project: Extermination
 * File Created: Friday, 4th November 2022 3:03:11 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 4th November 2022 3:19:04 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Base.hpp"

Base::Base(Yuna::Core::ResourceManager *pResourceManager)
{
	mPhysicsEnabled = false;
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/Base_00.png"));
	mBloodColor = sf::Color(100, 100, 100);
	mMaxHealth = 2000.f;
	mHealth = mMaxHealth;
	mType = EntityType::BASE;
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);

	//healthbar
	mHealthBar.AddFrame(0, 20, pResourceManager->LoadTexture("assets/textures/Base/Base-health-10%.png").get());
	mHealthBar.AddFrame(20, 35, pResourceManager->LoadTexture("assets/textures/Base/Base-health-20%.png").get());
	mHealthBar.AddFrame(35, 50, pResourceManager->LoadTexture("assets/textures/Base/Base-health-30%.png").get());
	mHealthBar.AddFrame(50, 60, pResourceManager->LoadTexture("assets/textures/Base/Base-health-40%.png").get());
	mHealthBar.AddFrame(60, 70, pResourceManager->LoadTexture("assets/textures/Base/Base-health-60%.png").get());
	mHealthBar.AddFrame(70, 80, pResourceManager->LoadTexture("assets/textures/Base/Base-health-80%.png").get());
	mHealthBar.AddFrame(80, 90, pResourceManager->LoadTexture("assets/textures/Base/Base-health-90%.png").get());
	mHealthBar.AddFrame(90, 100, pResourceManager->LoadTexture("assets/textures/Base/Base-health-100%.png").get());
	mHealthBar.SetScale(sf::Vector2f(0.45f, 0.45f));
	mHealthBarOffset = sf::Vector2f(156, 70);
}

Base::~Base()
{
}

void	Base::SetPosition(const sf::Vector2f &pPos)
{
	mPosition = sf::Vector2f(pPos.x, pPos.y - mSprite.getGlobalBounds().height + 16);
}
