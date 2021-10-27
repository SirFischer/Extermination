/*
 * File: MapGenerator.cpp
 * Project: Extermination
 * File Created: Wednesday, 27th October 2021 5:49:04 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 27th October 2021 5:56:14 pm
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
	float pA, pB = ((float)random() / (float)RAND_MAX);
	for (auto &block : mBlocks)
	{
		sf::Vector2f	pos = block.GetPosition();
		uint32_t		wl = mBlocks.size() / pSegments;
		if (!wl)
			wl = 1;
		if (!(segmentCounter % wl))
		{
			pA = pB;
			pB = (float)random() / (float)RAND_MAX;
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
		std::cout << pos.y << std::endl;
		pos.y = (uint32_t)(pos.y / mGridSize) * mGridSize;
		block.SetPosition(pos);
	}
}

void	Map::FillGaps()
{
	for (uint32_t i = 0; i < (mBlocks.size() + 1); i++)
	{
		int diff = (mBlocks[i].GetPosition().y - mBlocks[i + 1].GetPosition().y) / mGridSize;
		if (std::abs(mBlocks[i].GetPosition().x - mBlocks[i + 1].GetPosition().x) > mGridSize)
			break;
		for (uint32_t j = 1; j < std::abs(diff); j++)
		{
			Block block;
			sf::Vector2f pos = mBlocks[i + 1].GetPosition();
			if (diff > 0)
				pos.y += (mGridSize * j);
			else
				pos.y -= (mGridSize * j);
			block.SetPosition(pos);
			mBlocks.push_back(block);
		}
	}
}

void	Map::Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pSeed)
{
	mBlocks.clear();
	srand(pSeed);
	for (uint32_t i = 0; i < pLength; i++)
	{
		Block block;
		block.SetPosition(sf::Vector2f(i * mGridSize, 0));
		mBlocks.push_back(block);
	}
	uint32_t	segments = 1;
	uint32_t	amplitude = pAmplitude;
	for (size_t i = 0; i < pOctaves; i++)
	{
		segments *= 4;
		ApplyPerlin(segments, amplitude);
		amplitude /= 4;
	}
	FitToGrid();
	FillGaps();
	//perlin generation
}