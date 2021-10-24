/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th October 2021 8:34:39 am
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
	uint32_t last_signature = 0;
	for (auto &a : mBlocks)
	{
		if (a.mSignature != last_signature)
		{
			mSprite.setTexture(mSignatures[a.mSignature]);
			last_signature = a.mSignature;
		}
		mSprite.setPosition(a.mPos/1.565f);
		pWindow->Draw(mSprite);
	}
}

