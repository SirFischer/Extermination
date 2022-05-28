/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 28th May 2022 9:08:01 pm
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
	auto node = std::make_shared<PathNode>();
	node->mPosition = tBlock->GetPosition();
	//Delete block node at block position
	RemovePathNode(node->mPosition + sf::Vector2f(mGridSize / 2.f, mGridSize / 2.f));
	if (tBlock->IsBreakable())
	{
		node->mIsBreakable = true;
		AddNode(node);
	}

	auto topnode = std::make_shared<PathNode>();
	topnode->mPosition = node->mPosition;
	topnode->mIsBreakable = false;
	topnode->mPosition.y -= mGridSize;

	bool intersectsAbove = false;

	mBlockQTree->ForEach(sf::FloatRect(topnode->mPosition - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 3, mGridSize * 3)),
		[topnode, &intersectsAbove, size = mGridSize](const Block &pBlock){
			//is there a block above?
			if (sf::FloatRect(pBlock.GetPosition(), pBlock.GetSize()).contains(topnode->mPosition + sf::Vector2f(size / 2.f, size / 2.f)))
				intersectsAbove = true;
		});

	if (!intersectsAbove)
		AddNode(topnode);
}

void	Map::AddNode(std::shared_ptr<PathNode> pNode)
{
	(void)pNode;
	auto rNode = mPathNodes->Insert(pNode, sf::FloatRect(pNode->mPosition, sf::Vector2f(mGridSize, mGridSize)));

	if (!rNode)
		return;
	//create paths
	mPathNodes->ForEach(sf::FloatRect(pNode->mPosition - sf::Vector2f(mGridSize * 3, mGridSize * 3),
		sf::Vector2f(mGridSize * 6, mGridSize * 6)),
		[pNode, size = mGridSize, blocks = &mBlockQTree](std::shared_ptr<PathNode> &node){
			bool isColliding = false;
			(*blocks)->ForEach(sf::FloatRect(pNode->mPosition - sf::Vector2f(size * 3, size * 3),
				sf::Vector2f(size * 6, size * 6)),
				[pNode, node, size, &isColliding](const Block &pBlock){

					if (Yuna::Physics::LineRectCollision(
						pNode->mPosition + sf::Vector2f(size / 2.f, size / 2.f) + sf::Vector2f(0, -1), //I have absolutely zero shame for this...
						node->mPosition + sf::Vector2f(size / 2.f, size / 2.f) + sf::Vector2f(0, -1),
						sf::FloatRect(pBlock.GetPosition(), sf::Vector2f(size, size))))
					{
						isColliding = true;
					}
				});
			if (!isColliding &&
				Yuna::Math::Distance(node->mPosition, pNode->mPosition) < (size * 3.f) &&
				node.get() != pNode.get() &&
				std::find_if(node->mConnectedPaths.begin(), node->mConnectedPaths.end(), [pNode](const Path& path){
					return (path.mTarget.get() == pNode.get());
				}) == node->mConnectedPaths.end())
			{
				node->mConnectedPaths.push_back(Path());
			 	node->mConnectedPaths.back().mTarget = pNode;
			 	pNode->mConnectedPaths.push_back(Path());
			 	pNode->mConnectedPaths.back().mTarget = node;
			 	return ;
			}
		});
}


void	Map::RemovePathNode(const sf::Vector2f &pPos)
{
	//TODO: fix the deletion when shared_ptr...
	PathNode *tmpPtr = NULL;
	mPathNodes->ForEach(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)),
	[size = mGridSize, pPos, &tmpPtr](std::shared_ptr<PathNode> &pNode) {
		if (sf::FloatRect(pNode->mPosition, sf::Vector2f(size, size)).contains(pPos))
		{
			tmpPtr = pNode.get();
		}
	});

	if (mPathNodes->DeleteAt(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)), pPos))
	{
		mPathNodes->ForEach(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)),
		[size = mGridSize, pPos, tmpPtr](std::shared_ptr<PathNode> &pNode) {
			auto it = std::remove_if(pNode->mConnectedPaths.begin(), pNode->mConnectedPaths.end(), [tmpPtr](Path &data){
				return (data.mTarget.get() == tmpPtr);
			});
			pNode->mConnectedPaths.erase(it, pNode->mConnectedPaths.end());
		});
	}
}