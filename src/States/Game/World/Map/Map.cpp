/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 8:21:55 am
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


void	Map::UpdateEntity(Entity *pEntity)
{
	auto list = mBlockQTree->RangeSearch(sf::FloatRect(sf::Vector2f(pEntity->GetPosition().x - (mGridSize * 1.f), pEntity->GetPosition().y - (mGridSize * 1.f)), sf::Vector2f(mGridSize * 4.f, mGridSize * 4.f)));
	// sf::Vector2f	futurePos = pEntity->mPosition + pEntity->mVelocity;
	// sf::Vector2f	currPos = pEntity->mPosition;
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			if (b.mRect.intersects(pEntity->GetGlobalBounds()))
				b.mData.SetColor(sf::Color(255, 0, 0, 250));
			else
				b.mData.SetColor(sf::Color(255, 255, 255, 255));
		}
	}
}

void	Map::UpdateLine(const sf::Vector2f &pLineStart, const sf::Vector2f &pLineEnd)
{
	auto list = mBlockQTree->RangeSearch(sf::FloatRect(sf::Vector2f(pLineStart.x - (mGridSize * 5.f), pLineStart.y - (mGridSize * 5.f)), sf::Vector2f(mGridSize * 15.f, mGridSize * 15.f)));
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			if (Yuna::Physics::LineRectCollision(pLineStart, pLineEnd, b.mRect))
			{
				b.mData.SetColor(sf::Color(255, 0, 0, 250));
			}
			else
			{
				b.mData.SetColor(sf::Color(255, 255, 255, 255));
			}
		}
	}
}


void	Map::Render(Yuna::Core::Window *pWindow, const sf::View	&pView)
{
	std::string		lastPath = "";
	mSprite.setScale(1, 1);
	auto list = mBlockQTree->RangeSearch(sf::FloatRect(
					sf::Vector2f(pView.getCenter().x - ((pView.getSize().x / 2.f) + mGridSize), 
					pView.getCenter().y - ((pView.getSize().y / 2.f) + mGridSize)),
					sf::Vector2f(pView.getSize().x + (mGridSize * 2.f),
					pView.getSize().y + (mGridSize * 2.f))));
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			mSprite.setColor(b.mData.GetColor());
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

