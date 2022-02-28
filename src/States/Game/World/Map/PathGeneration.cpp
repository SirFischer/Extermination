/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 28th February 2022 3:34:19 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Map.hpp"

void	Map::GeneratePathNodes()
{
	mPathNodes = std::make_unique<Yuna::Utils::QTree<PathNode>>(sf::FloatRect(0, -(int)mAmplitude * 2, mLength * mGridSize, mLength * mGridSize));
	for (auto &block : mBlocks)
	{
		AddPathNode(&block);
	}
}

void	Map::AddPathNode(Block *tBlock)
{
	PathNode node;
	node.mPosition = tBlock->GetPosition();
	node.mPosition.y -= mGridSize;
	mPathNodes->Insert(node, sf::FloatRect(node.mPosition, sf::Vector2f(mGridSize, mGridSize)));
}

void	Map::RemovePathNode(PathNode *tNode)
{
	(void)tNode;
}