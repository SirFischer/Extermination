/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 18th April 2022 7:16:06 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Map.hpp"

#include <iostream>

void	Map::AddPathNode(Block *tBlock)
{
	if (!tBlock)
		return ;
	PathNode node;
	node.mPosition = tBlock->GetPosition();
	if (tBlock->IsBreakable())
	{
		node.mIsBreakable = true;
		mPathNodes->Insert(node, sf::FloatRect(node.mPosition, sf::Vector2f(mGridSize, mGridSize)));
	}
	node.mIsBreakable = false;

	node.mPosition.y -= mGridSize;

	auto lists = mBlockQTree->Query(sf::FloatRect(tBlock->GetPosition() - sf::Vector2f(mGridSize, mGridSize), tBlock->GetSize() + sf::Vector2f(mGridSize * 2, mGridSize * 2)));
	bool intersects = false;
	for (auto &list : lists)
	{
		for (auto &block : *list)
		{
			if (block.mRect.contains(node.mPosition + sf::Vector2f(32, 32)) && !block.mData.IsBreakable())
				intersects = true;
		}
	}
	if (!intersects)
		mPathNodes->Insert(node, sf::FloatRect(node.mPosition, sf::Vector2f(mGridSize, mGridSize)));
	
}

void	Map::AddNode(PathNode *pNode)
{
	(void)pNode;
}


void	Map::RemovePathNode(PathNode *tNode)
{
	(void)tNode;
}