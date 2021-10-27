/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 27th October 2021 5:49:17 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Map.hpp"

Map::Map(Yuna::Core::ResourceManager *pResourceManager)
{
	mResourceManager = pResourceManager;
}

Map::~Map()
{
}


void	Map::Render(Yuna::Core::Window *pWindow)
{
	std::string		lastPath = "";
	mSprite.setScale(1, 1);
	for (auto &a : mBlocks)
	{
		if (a.GetTexturePath() != lastPath)
		{
			mSprite.setTexture(*mResourceManager->LoadTexture(a.GetTexturePath()));
			mSprite.setScale(sf::Vector2f(100.f / mSprite.getGlobalBounds().width, 100.f / mSprite.getGlobalBounds().height));
			lastPath = a.GetTexturePath();
		}
		mSprite.setPosition(a.GetPosition());
		pWindow->Draw(mSprite);
	}
}

