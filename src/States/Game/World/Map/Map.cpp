/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 28th October 2021 9:35:38 pm
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
			sf::Texture	*texture = mResourceManager->LoadTexture(a.GetTexturePath()).get();
			mSprite.setTexture(*texture);
			mSprite.setScale(sf::Vector2f((float)mGridSize / texture->getSize().x, (float)mGridSize / texture->getSize().y));
			lastPath = a.GetTexturePath();
		}
		mSprite.setPosition(a.GetPosition());
		pWindow->Draw(mSprite);
	}
}

