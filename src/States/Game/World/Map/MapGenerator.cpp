/*
 * File: MapGenerator.cpp
 * Project: Extermination
 * File Created: Wednesday, 27th October 2021 5:49:04 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 28th October 2021 9:40:03 pm
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
		pos.y = (int)(pos.y / (int)mGridSize) * (int)mGridSize;
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
			block.SetTexturePath("assets/textures/dirt400x400.png");
			sf::Vector2f pos = (diff > 0) ? mBlocks[i + 1].GetPosition() : mBlocks[i].GetPosition();
			pos.y += (mGridSize * j);
			block.SetPosition(pos);
			mBlocks.push_back(block);
		}
	}
}

void	Map::Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed)
{
	mBlocks.clear();
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
	FillGaps();
	//perlin generation
}