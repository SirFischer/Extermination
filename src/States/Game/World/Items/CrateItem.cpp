/*
 * File: CrateItem.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:34:46 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 29th June 2022 6:11:38 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "CrateItem.hpp"


CrateItem::CrateItem(Yuna::Core::ResourceManager *pResourceManager)
{
	mTexturePath = "assets/textures/crate.png";
	mSprite.setTexture(*pResourceManager->LoadTexture(mTexturePath));
	mSprite.setColor(sf::Color(150, 150, 150, 180));

	mIcon.setTexture(*pResourceManager->LoadTexture(mTexturePath));
	mIcon.setScale(0.8, 0.8);
}

CrateItem::~CrateItem()
{
}

void	CrateItem::Render(Yuna::Core::Window *pWindow)
{
	sf::Vector2f	pos = pWindow->GetViewMousePos();

	if (mIsValid && 
	std::abs((std::floor(pos.x / 64.f) * 64.f) - pos.x) < 48 &&
	std::abs((std::floor(pos.y / 64.f) * 64.f) - pos.y) < 48)
	{
		mSprite.setPosition(
			sf::Vector2f(std::floor(pos.x / 64.f) * 64.f,
			std::floor(pos.y / 64.f) * 64.f)
		);
	}
	else
	{
		mSprite.setPosition(pos - sf::Vector2f(32, 32));
	}

	mSprite.setColor((mIsValid) ? sf::Color(0, 255, 0, 100) : sf::Color(255, 0, 0, 100));
	pWindow->Draw(mSprite);
}
