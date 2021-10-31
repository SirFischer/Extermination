/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 31st October 2021 10:56:35 am
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


void	Map::ResolveCollisions(Entity *pEntity)
{
	//Implement bnp tree for collision detection
	for (auto &a : mBlocks)
	{
		if (a.GetPosition().x < pEntity->GetPosition().x - 500)
			continue ;
		if (a.GetPosition().x > pEntity->GetPosition().x + 500)
			continue ;
	}
}

//TODO: Refactor this horribleness
void	Map::Render(Yuna::Core::Window *pWindow, const sf::View	&pView)
{
	std::string		lastPath = "";
	mSprite.setScale(1, 1);
	auto list = mBlockQTree->RangeSearch(sf::FloatRect(sf::Vector2f(pView.getCenter().x - 1000.f, pView.getCenter().y - 1000.f), sf::Vector2f(2000, 2000)));
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			if (b.mData.GetTexturePath() != lastPath)
			{
				sf::Texture	*texture = mResourceManager->LoadTexture(b.mData.GetTexturePath()).get();
				mSprite.setTexture(*texture);
				mSprite.setScale(sf::Vector2f((float)mGridSize / texture->getSize().x, (float)mGridSize / texture->getSize().y));
				lastPath = b.mData.GetTexturePath();
			}
			mSprite.setPosition(b.mData.GetPosition());
			pWindow->Draw(mSprite);
		}
	}
}

