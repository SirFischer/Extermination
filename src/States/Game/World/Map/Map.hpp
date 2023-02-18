/*
 * File: Map.hpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:28 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 30th December 2022 12:00:53 am
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

#include "./Blocks/Block.hpp"
#include "Blocks/Foliage.hpp"
#include "../Entities/Entity.hpp"
#include "Background.hpp"
#include "../Projectiles/ProjectileManager.hpp"


class Map
{
private:

	Yuna::Core::ResourceManager			*mResourceManager;
	Yuna::Core::Window					*mWindow;
	
	std::vector<Block>					mBlocks;
	std::unique_ptr<Yuna::Utils::QTree<std::shared_ptr<Block>>>					mBlockQTree;
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
	void	AddPathNode(std::shared_ptr<Block> tBlock);
	void	AddNode(std::shared_ptr<Yuna::AI::PathNode> pNode);
	void	UpdatePathsInRange(const sf::FloatRect &pRect);

	void	RemovePathNode(const sf::Vector2f &pPos);
	Yuna::AI::PathNode *
			GetClosestNode(const sf::Vector2f &pPos);
	
public:
	Map(Yuna::Core::ResourceManager *mResourceManager, Yuna::Core::Window *pWindow);
	~Map();

	void	UpdateEntity(Entity *pEntity);
	void	Update(float pDeltaTime, const sf::FloatRect &pRect);

	void	AddBlock(std::shared_ptr<Block> pBlock);
	void	RemoveBlock(sf::Vector2f pPos);

	void	ApplyCollisionDetection(Entity *pEntity);
	void	LockPlayerToMap(Entity *pEntity);

	bool	CanBlockBePlacedAt(const sf::Vector2f &pPos);
	float	GetBaseVerticalPosition();
	std::vector<Yuna::AI::PathNode>
			GetPath(sf::Vector2f pP1, sf::Vector2f pP2);
	sf::IntRect
			GetGlobalBounds(){return (mGlobalBounds);}
	std::unique_ptr<Yuna::Utils::QTree<std::shared_ptr<Block>>> *
			GetBlockTree(){return (&mBlockQTree);}

	void	Generate(uint32_t pLength, uint32_t pAmplitude, uint32_t pOctaves, uint32_t pStartSegments, uint32_t pSeed);

	void	Render(Yuna::Core::Window *pWindow, const sf::View	&pView);
	void	RenderPathNodes(Yuna::Core::Window *pWindow, const sf::View &pView);


};

