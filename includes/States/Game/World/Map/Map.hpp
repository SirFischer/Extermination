/*
 * File: Map.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:28 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 27th October 2021 5:33:39 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Yuna.hpp"

#include "Block.hpp"

class Map
{
private:

	Yuna::Core::ResourceManager			*mResourceManager;
	
	std::vector<Block>					mBlocks;
	sf::Sprite							mSprite;
	uint32_t							mGridSize = 100;

	void	ApplyPerlin(uint32_t pSegments, float pAmplitude);
	void	FitToGrid();
	void	FillGaps();
	
public:
	Map(Yuna::Core::ResourceManager *mResourceManager);
	~Map();

	void	Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pSeed);

	void	Render(Yuna::Core::Window *pWindow);

};

