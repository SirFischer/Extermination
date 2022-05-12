/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 1st May 2022 3:26:00 pm
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
	//Delete block node at block position
	mPathNodes->DeleteAt(
		sf::FloatRect(node.mPosition - sf::Vector2f(mGridSize, mGridSize),
		sf::Vector2f(mGridSize * 3, mGridSize * 3)), node.mPosition + sf::Vector2f(mGridSize / 2.f, mGridSize / 2.f));
	if (tBlock->IsBreakable())
	{
		node.mIsBreakable = true;
		mPathNodes->Insert(node, sf::FloatRect(node.mPosition, sf::Vector2f(mGridSize, mGridSize)));
	}

	node.mIsBreakable = false;
	node.mPosition.y -= mGridSize;

	bool intersectsAbove = false;
	bool intersectsCenter = false;

	mBlockQTree->ForEach(sf::FloatRect(node.mPosition - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 3, mGridSize * 3)),
		[node, &intersectsAbove, &intersectsCenter, size = mGridSize](const Block &pBlock){
			//is there a block above?
			if (sf::FloatRect(pBlock.GetPosition(), pBlock.GetSize()).contains(node.mPosition + sf::Vector2f(size / 2.f, size / 2.f)))
				intersectsAbove = true;
		});

	if (!intersectsAbove)
		mPathNodes->Insert(node, sf::FloatRect(node.mPosition, sf::Vector2f(mGridSize, mGridSize)));
}

void	Map::AddNode(PathNode *pNode)
{
	(void)pNode;
	mPathNodes->Insert(*pNode, sf::FloatRect(pNode->mPosition, sf::Vector2f(mGridSize, mGridSize)));
}


void	Map::RemovePathNode(const sf::Vector2f &pPos)
{
	if (mPathNodes->DeleteAt(sf::FloatRect(pPos - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 3, mGridSize * 3)), pPos))
	{
		//deleted
	}
}