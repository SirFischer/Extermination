/*
 * File: MapGenerator.cpp
 * Project: Extermination
 * File Created: Wednesday, 27th October 2021 5:49:04 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 24th January 2022 6:20:40 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#define MAX_QUADTREE_NODES 9
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
	float pA, pB = (((float)random() / (float)RAND_MAX) * 2.0f) - 1.0f;
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
			Block block;
			block.SetTexturePath("assets/textures/Sandstone.jpg");
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
	mBlockQTree = std::make_unique<Yuna::Utils::QTree<Block>>(sf::FloatRect(min.x, min.y, max.x - min.x, max.y - min.y));
	for (auto &i : mBlocks)
		mBlockQTree->Insert(i, sf::FloatRect(i.GetPosition(), sf::Vector2f(mGridSize, mGridSize)));
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
		block.SetTexturePath("assets/textures/Sandstone-top.jpg");
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