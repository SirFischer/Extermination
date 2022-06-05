/*
 * File: CrateItem.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:34:46 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 5th June 2022 7:41:00 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "CrateItem.hpp"


CrateItem::CrateItem(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/crate.png"));
	mSprite.setColor(sf::Color(150, 150, 150, 180));
}

CrateItem::~CrateItem()
{
}

void	CrateItem::Render(Yuna::Core::Window *pWindow)
{
	sf::Vector2f	pos = pWindow->GetViewMousePos();
	if (mIsValid)
		mSprite.setPosition(
			sf::Vector2f(std::floor(pos.x / 64.f) * 64.f,
			std::floor(pos.y / 64.f) * 64.f)
		);
	else
		mSprite.setPosition(pos - sf::Vector2f(32, 32));
	mSprite.setColor((mIsValid) ? sf::Color(0, 255, 0, 100) : sf::Color(255, 0, 0, 100));
	pWindow->Draw(mSprite);
}
