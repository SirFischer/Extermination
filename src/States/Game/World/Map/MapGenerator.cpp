/*
 * File: MapGenerator.cpp
 * Project: Extermination
 * File Created: Wednesday, 27th October 2021 5:49:04 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 31st October 2021 10:48:23 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
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
	std::cout << pB << std::endl;
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

void	Map::FillGaps(uint32_t pAmplitude)
{
	for (uint32_t i = 0; i < mBlocks.size(); i++)
	{
		if (mBlocks[i].GetPosition().x == mBlocks[i + 1].GetPosition().x)
			break;
		for (uint32_t j = 1; j < pAmplitude; j++)
		{
			Block block;
			block.SetTexturePath("assets/textures/dirt400x400.png");
			sf::Vector2f pos = mBlocks[i].GetPosition();
			pos.y += (mGridSize * j);
			block.SetPosition(pos);
			mBlocks.push_back(block);
		}
	}
}

void	Map::GenerateQTree()
{
	mBlockQTree = std::make_unique<Yuna::Utils::QTree<Block>>(sf::FloatRect(0, -mSize.y / 2.f, mSize.x, mSize.y));
	for (auto &i : mBlocks)
		mBlockQTree->Insert(i, sf::FloatRect(i.GetPosition(), sf::Vector2f(mGridSize, mGridSize)));
}


void	Map::Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed)
{
	mBlocks.clear();
	mAmplitude = pAmplitude;
	mSize = sf::Vector2f(pLength * mGridSize, pAmplitude * 2.f);
	srand(pSeed);
	for (uint32_t i = 0; i < pLength; i++)
	{
		Block block;
		block.SetPosition(sf::Vector2f(i * mGridSize, 0));
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
	FillGaps(pAmplitude);
	GenerateQTree();
}