/*
 * File: CollisionDetection.cpp
 * Project: Extermination
 * File Created: Saturday, 1st January 2022 9:42:55 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 11:09:30 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Map.hpp"

void	Map::ApplyCollisionDetection(Entity *pEntity)
{
	auto list = mBlockQTree->Query(sf::FloatRect(sf::Vector2f(pEntity->GetPosition().x - (mGridSize * 3.f), pEntity->GetPosition().y - (mGridSize * 3.f)), sf::Vector2f(mGridSize * 6.f, mGridSize * 6.f)));
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

void	Map::LockPlayerToMap(Entity *pEntity)
{
	if (pEntity->mPosition.x < 0)
		pEntity->mPosition.x = 0;
	if (pEntity->mPosition.x + pEntity->GetGlobalBounds().width > ((mLength - 1) * mGridSize))
		pEntity->mPosition.x = ((mLength - 1) * mGridSize) - pEntity->GetGlobalBounds().width;
}