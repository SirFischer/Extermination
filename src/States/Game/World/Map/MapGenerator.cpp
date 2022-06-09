/*
 * File: MapGenerator.cpp
 * Project: Extermination
 * File Created: Wednesday, 27th October 2021 5:49:04 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 9th June 2022 9:54:52 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#define MAX_QUADTREE_NODES 18
#include "Map.hpp"
#include <math.h>
#include <random>

float	interpolate(float pA, float pB, float pX)
{
	float ft = pX * M_PI;
	float f = (1.f - std::cos(ft)) * 0.5f;
	return (pA * (1.f - f) + pB * f);
}

void	Map::ApplyPerlin(uint32_t pSegments, float pAmplitude)
{
	int segmentCounter = 0;
	float pA = 0, pB = (((float)random() / (float)RAND_MAX) * 2.0f) - 1.0f;
	for (auto &block : mBlocks)
	{
		sf::Vector2f	pos = block.GetPosition();
		uint32_t		wl = mBlocks.size() / pSegments;
		if (!wl)
			wl = 1;
		if (!(segmentCounter % wl))
		{
			pA = pB;
			pB = (((float)random() / (float)RAND_MAX) * 2.0f) - 1.0f;
			pos.y += (pA * pAmplitude);
			block.SetPosition(pos);
		}
		else
		{
			pos.y += (interpolate(pA, pB, ((float)(segmentCounter % wl) / (float)wl)) * pAmplitude);
			block.SetPosition(pos);
		}
		segmentCounter++;
	}
}

void	Map::FitToGrid()
{
	for (auto &block : mBlocks)
	{
		sf::Vector2f	pos = block.GetPosition();
		pos.y = (int)(pos.y / (int)mGridSize) * (int)mGridSize;
		block.SetPosition(pos);
		int foliage = random() % 100;
		if (foliage < 10)
		{
			mBlocks.push_back(Foliage((eFoliageType)(random() % 4)));
			mBlocks.back().SetPosition(pos - sf::Vector2f(0, mGridSize));
		} 
	}
}

void	Map::GenerateGround()
{
	for (uint32_t i = 0; i < mBlocks.size(); i++)
	{
		if (mBlocks[i].GetPosition().x == mBlocks[i + 1].GetPosition().x)
			break;
		uint32_t length = (mAmplitude / mGridSize);
		for (uint32_t j = 1; j < ((length > 15) ? length : 15); j++)
		{
			if (!mBlocks[i].IsSolid())
				continue;
			Block block;
			bool cornerBlock = (j == 1) && ((i > 0 && mBlocks[i - 1].GetPosition().y > mBlocks[i].GetPosition().y) || (i < mBlocks.size() - 1 && mBlocks[i + 1].GetPosition().y > mBlocks[i].GetPosition().y));
			block.SetTexturePath((cornerBlock) ? "assets/textures/Sandstone.png" : "assets/textures/Sandstone.png");
			block.SetSize(sf::Vector2f(mGridSize, mGridSize));
			sf::Vector2f pos = mBlocks[i].GetPosition();
			pos.y += (mGridSize * j);
			block.SetPosition(pos);
			mBlocks.push_back(block);
		}
	}
}


void	Map::GenerateQTree()
{
	sf::Vector2f min = sf::Vector2f(0, 0), max = min;
	for (auto &i : mBlocks)
	{
		if (i.GetPosition().x < min.x)
			min.x = i.GetPosition().x;
		if (i.GetPosition().y < min.y)
			min.y = i.GetPosition().y;
		if (i.GetPosition().x > max.x)
			max.x = i.GetPosition().x;
		if (i.GetPosition().y > max.y)
			max.y = i.GetPosition().y;
	}
	mGlobalBounds.left = min.x;
	mGlobalBounds.top = min.y;
	mGlobalBounds.width = max.x - min.x;
	mGlobalBounds.height = max.y - min.y;
	mBlockQTree = std::make_unique<Yuna::Utils::QTree<std::shared_ptr<Block>>>(
		sf::FloatRect(min.x, min.y - mMaxBuildHeight, max.x - min.x + mMaxBuildHeight, std::max(max.x - min.x, max.y - min.y) + mMaxBuildHeight));
	mPathNodes = std::make_unique<Yuna::Utils::QTree<std::shared_ptr<Yuna::AI::PathNode>>>(mBlockQTree->GetGlobalBounds());
	for (auto &i : mBlocks)
		AddBlock(std::make_shared<Block>(i));
}


void	Map::Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed)
{
	mBlocks.clear();
	mAmplitude = pAmplitude;
	mLength = pLength;
	mSize = sf::Vector2f(pLength * mGridSize, pAmplitude * 2.f);
	srand(pSeed);
	for (uint32_t i = 0; i < pLength; i++)
	{
		Block block;
		block.SetTexturePath("assets/textures/Sandstone-top.png");
		block.SetPosition(sf::Vector2f(i * mGridSize, pAmplitude));
		mBlocks.push_back(block);
	}
	uint32_t	segments = pStartSegments;
	uint32_t	amplitude = pAmplitude;
	for (size_t i = 0; i < pOctaves; i++)
	{
		segments *= 2;
		ApplyPerlin(segments, amplitude);
		amplitude /= 2;
	}
	FitToGrid();
	GenerateGround();
	GenerateQTree();
}