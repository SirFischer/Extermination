/*
 * File: Map.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:28 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 1st June 2022 4:03:10 pm
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

#include "Blocks/Block.hpp"
#include "../Entities/Entity.hpp"
#include "Background.hpp"


class Map
{
private:

	Yuna::Core::ResourceManager			*mResourceManager;
	Yuna::Core::Window					*mWindow;
	
	std::vector<Block>					mBlocks;
	std::unique_ptr<Yuna::Utils::QTree<Block>>						mBlockQTree;
	std::unique_ptr<Yuna::Utils::QTree<std::shared_ptr<Yuna::AI::PathNode>>>	mPathNodes;
	sf::Sprite							mSprite;
	uint32_t							mGridSize = 64;
	uint32_t							mMaxBuildHeight = 1024;
	sf::Vector2f						mSize;
	uint32_t							mLength;
	uint32_t							mAmplitude;
	sf::IntRect							mGlobalBounds = sf::IntRect(0, 0, 0, 0);

	void	ApplyPerlin(uint32_t pSegments, float pAmplitude);
	void	FitToGrid();
	void	GenerateGround();
	void	GenerateQTree();
	void	GeneratePathNodes();
	void	AddPathNode(Block *tBlock);
	void	AddNode(std::shared_ptr<Yuna::AI::PathNode> pNode);
	void	RemovePathNode(const sf::Vector2f &pPos);
	Yuna::AI::PathNode *
			GetClosestNode(const sf::Vector2f &pPos);
	
public:
	Map(Yuna::Core::ResourceManager *mResourceManager, Yuna::Core::Window *pWindow);
	~Map();

	void	UpdateEntity(Entity *pEntity);
	void	Update(float pDeltaTime);

	void	AddBlock(Block *pBlock);
	void	RemoveBlock(sf::Vector2f pPos);

	void	ApplyCollisionDetection(Entity *pEntity);
	void	LockPlayerToMap(Entity *pEntity);

	sf::IntRect
			GetGlobalBounds(){return (mGlobalBounds);}

	void	Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed);

	void	Render(Yuna::Core::Window *pWindow, const sf::View	&pView);

	void	RenderPathNodes(Yuna::Core::Window *pWindow, const sf::View &pView);

	std::vector<Yuna::AI::PathNode>
			GetPath(sf::Vector2f pP1, sf::Vector2f pP2);

};

