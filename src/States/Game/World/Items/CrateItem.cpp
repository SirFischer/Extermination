/*
 * File: CrateItem.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:34:46 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 25th April 2022 9:01:33 pm
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
	mSprite.setPosition(
		sf::Vector2f(std::floor(pos.x / 64.f) * 64.f,
		std::floor(pos.y / 64.f) * 64.f)
	);
	pWindow->Draw(mSprite);
}
