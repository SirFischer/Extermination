/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 29th October 2021 7:20:16 am
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
	mSprite.setTexture(*mResourceManager->LoadTexture("assets/textures/dirt400x400.png"));
	for (auto &a : mBlocks)
	{
		mSprite.setPosition(a.GetPosition());
		while (mSprite.getPosition().y + mGridSize < a.GetPosition().y + (mGridSize * 10))
		{
			mSprite.move(0, mGridSize);
			pWindow->Draw(mSprite);
		}
	}
}

