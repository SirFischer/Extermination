/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 5:47:14 pm
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
	sf::Vector2f collisionPoint;
	sf::Vector2f collisionNormal;
	sf::Vector2f rayDir = pEntity->mVelocity;
	float collisionTime;
	std::vector<std::pair<sf::FloatRect, float>>	collisionTimes;
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			if (Yuna::Physics::DynamicRectCollision(pEntity->GetGlobalBounds(), rayDir, b.mRect, collisionPoint, collisionNormal, collisionTime))
			{
				collisionTimes.push_back(std::pair<sf::FloatRect, float>(b.mRect, collisionTime));
			}
		}
	}
	std::sort(collisionTimes.begin(), collisionTimes.end(), [](const std::pair<sf::FloatRect, float> &a, const std::pair<sf::FloatRect, float> &b) { return a.second < b.second; });

	for (auto &collision : collisionTimes)
	{
		rayDir = pEntity->mVelocity;
		if (Yuna::Physics::DynamicRectCollision(pEntity->GetGlobalBounds(), rayDir, collision.first, collisionPoint, collisionNormal, collisionTime))
		{
			pEntity->mVelocity.x += collisionNormal.x * std::abs(pEntity->mVelocity.x) * (1.f - collisionTime);
			pEntity->mVelocity.y += collisionNormal.y * std::abs(pEntity->mVelocity.y) * (1.f - collisionTime);
			if (collisionNormal.y < 0.f)
				pEntity->mOnGround = true;
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

