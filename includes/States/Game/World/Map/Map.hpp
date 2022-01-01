/*
 * File: Map.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:28 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 10:10:02 am
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
#include "Entities/Entity.hpp"


class Map
{
private:

	Yuna::Core::ResourceManager			*mResourceManager;
	
	std::vector<Block>					mBlocks;
	std::unique_ptr<Yuna::Utils::QTree<Block>>		mBlockQTree;
	sf::Sprite							mSprite;
	uint32_t							mGridSize = 64;
	sf::Vector2f						mSize;
	uint32_t							mLength;
	uint32_t							mAmplitude;

	void	ApplyPerlin(uint32_t pSegments, float pAmplitude);
	void	FitToGrid();
	void	GenerateGround();
	void	GenerateQTree();
	
public:
	Map(Yuna::Core::ResourceManager *mResourceManager);
	~Map();

	void	UpdateEntity(Entity *pEntity);

	void	ApplyCollisionDetection(Entity *pEntity);
	void	LockPlayerToMap(Entity *pEntity);

	void	Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed);

	void	Render(Yuna::Core::Window *pWindow, const sf::View	&pView);

};

