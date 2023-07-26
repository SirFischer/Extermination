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
	mSprite.setPosition(0, 0);
	mBloodColor = sf::Color(100, 100, 100);
	mType = EntityType::BASE;
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width - 10, mSprite.getGlobalBounds().height - 10);
}

Base::~Base()
{
}

void	Base::SetPosition(const sf::Vector2f &pPos)
{
	mPosition = sf::Vector2f(pPos.x, pPos.y - mSprite.getGlobalBounds().height + 16);
}
