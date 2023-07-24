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
	mBaseSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/Base_00.png"));
	mBaseSprite.setPosition(0, 0);
	mBloodColor = sf::Color(100, 100, 100);
}

Base::~Base()
{
}

void	Base::Update(float pDeltaTime)
{
	(void)pDeltaTime;
}


void	Base::SetPosition(const sf::Vector2f &pPos)
{
	mBaseSprite.setPosition(pPos.x, pPos.y - mBaseSprite.getGlobalBounds().height + 16);
}

void	Base::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mBaseSprite);
}