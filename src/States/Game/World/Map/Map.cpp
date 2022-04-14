/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 14th April 2022 9:52:06 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Map.hpp"

#include "Config.hpp"

Map::Map(Yuna::Core::ResourceManager *pResourceManager)
{
	mResourceManager = pResourceManager;
}

Map::~Map()
{
}


void	Map::UpdateEntity(Entity *pEntity)
{
	ApplyCollisionDetection(pEntity);
	LockPlayerToMap(pEntity);
}

void	Map::Update(float pDeltaTime)
{
	(void)pDeltaTime;
}

void	Map::AddBlock(Block *pBlock)
{
	if (!pBlock)
		return ;
	pBlock->SetPosition(sf::Vector2f(std::floor(pBlock->GetPosition().x / mGridSize) * mGridSize, std::floor(pBlock->GetPosition().y / mGridSize) * mGridSize));
	auto list = mBlockQTree->RangeSearch(sf::FloatRect(pBlock->GetPosition() - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 4, mGridSize * 4)));
	for (auto &sublist : list) {
		for (auto &block : *sublist)
		{
			if (sf::FloatRect(block.mData.GetPosition(), sf::Vector2f(mGridSize, mGridSize)).intersects(sf::FloatRect(pBlock->GetPosition(), sf::Vector2f(mGridSize, mGridSize))))
				return ;
		}
	}
	mBlockQTree->Insert(*pBlock, sf::FloatRect(pBlock->GetPosition(), sf::Vector2f(mGridSize, mGridSize)));
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
	if (Config::mRenderPathNodes)
		RenderPathNodes(pWindow, pView);
	if (Config::mRenderQTree)
		mBlockQTree->Render(pWindow->GetRenderWindow(), Config::mRenderQTree);
}

void	Map::RenderPathNodes(Yuna::Core::Window *pWindow, const sf::View &pView)
{
	sf::CircleShape node(32);
	node.setFillColor(sf::Color::Red);
	auto list = mPathNodes->RangeSearch(sf::FloatRect(
					sf::Vector2f(pView.getCenter().x - ((pView.getSize().x / 2.f) + mGridSize), 
					pView.getCenter().y - ((pView.getSize().y / 2.f) + mGridSize)),
					sf::Vector2f(pView.getSize().x + (mGridSize * 2.f),
					pView.getSize().y + (mGridSize * 2.f))));
	for (auto &a : list)
	{
		for (auto &b : *a)
		{
			node.setPosition(b.mData.mPosition);
			pWindow->Draw(node);
		}
	}
}


