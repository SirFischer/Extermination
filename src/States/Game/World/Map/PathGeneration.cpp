/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 4th June 2022 12:33:58 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Map.hpp"

#include <iostream>

void	Map::AddPathNode(std::shared_ptr<Block> tBlock)
{
	if (!tBlock)
		return ;
	auto node = std::make_shared<Yuna::AI::PathNode>();
	node->mPosition = tBlock->GetPosition();
	node->mParentObject = tBlock;
	//Delete block node at block position
	RemovePathNode(node->mPosition + sf::Vector2f(mGridSize / 2.f, mGridSize / 2.f));
	if (tBlock->IsBreakable())
	{
		node->mIsBreakable = true;
		AddNode(node);
	}

	auto topnode = std::make_shared<Yuna::AI::PathNode>();
	topnode->mPosition = node->mPosition;
	topnode->mIsBreakable = false;
	topnode->mPosition.y -= mGridSize;

	bool intersectsAbove = false;

	mBlockQTree->ForEach(sf::FloatRect(topnode->mPosition - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 3, mGridSize * 3)),
		[topnode, &intersectsAbove, size = mGridSize](const std::shared_ptr<Block> &pBlock){
			//is there a block above?
			if (sf::FloatRect(pBlock->GetPosition(), pBlock->GetSize()).contains(topnode->mPosition + sf::Vector2f(size / 2.f, size / 2.f)))
				intersectsAbove = true;
		});

	if (!intersectsAbove)
		AddNode(topnode);
}

void	Map::AddNode(std::shared_ptr<Yuna::AI::PathNode> pNode)
{
	mPathNodes->Insert(pNode, sf::FloatRect(pNode->mPosition, sf::Vector2f(mGridSize, mGridSize)));
	UpdatePathsInRange(sf::FloatRect(pNode->mPosition - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)));
}


void	Map::RemovePathNode(const sf::Vector2f &pPos)
{
	Yuna::AI::PathNode *tmpPtr = NULL;
	mPathNodes->ForEach(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)),
	[size = mGridSize, pPos, &tmpPtr](std::shared_ptr<Yuna::AI::PathNode> &pNode) {
		if (sf::FloatRect(pNode->mPosition, sf::Vector2f(size, size)).contains(pPos))
		{
			tmpPtr = pNode.get();
		}
	});

	if (mPathNodes->DeleteAt(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)), pPos))
	{
		mPathNodes->ForEach(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)),
		[size = mGridSize, pPos, tmpPtr](std::shared_ptr<Yuna::AI::PathNode> &pNode) {
			pNode->mConnectedPaths.remove_if([tmpPtr](Yuna::AI::Path &data){
				return (data.mTarget.get() == tmpPtr);
			});
		});
	}
	UpdatePathsInRange(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)));
}

//pDirection -> -1 ignored, 0 left, 1 right
Yuna::AI::PathNode *Map::GetClosestNode(const sf::Vector2f &pPos)
{
	Yuna::AI::PathNode *current = nullptr;
	mPathNodes->ForEach(sf::FloatRect(pPos - sf::Vector2f(mGridSize * 3, mGridSize * 3), sf::Vector2f(mGridSize * 6, mGridSize * 6)),
		[size = mGridSize, pPos, &current](std::shared_ptr<Yuna::AI::PathNode> &pNode) {
			if (!current)
			{
				current = pNode.get();
				return ;
			}
			float distance = std::pow(current->mPosition.x - pPos.x, 2) + std::pow(current->mPosition.y - pPos.y, 2);
			float newdistance = std::pow(pNode->mPosition.x - pPos.x, 2) + std::pow(pNode->mPosition.y - pPos.y, 2);
			if (newdistance < distance)
				current = pNode.get();
		});
	return (current);
}

std::vector<Yuna::AI::PathNode>	Map::GetPath(sf::Vector2f pP1, sf::Vector2f pP2)
{
	auto node1 = GetClosestNode(pP1);
	auto node2 = GetClosestNode(pP2);
	if (node1 && node2)
		return (Yuna::AI::createPath(node1, node2));
	return (std::vector<Yuna::AI::PathNode>());
}

void	Map::UpdatePathsInRange(const sf::FloatRect &pRect)
{
	//loop through nodes
	mPathNodes->ForEach(pRect,
	[&nodeList = mPathNodes, &blockList = mBlockQTree, pRect, size = mGridSize](std::shared_ptr<Yuna::AI::PathNode> &pNode){
		//for every node, check with every other node in range
		nodeList->ForEach(sf::FloatRect(pNode->mPosition - sf::Vector2f(size * 3.f, size * 3.f), sf::Vector2f(size * 6.f, size * 6.f)),
			[pNode, pRect, &blockList, size](std::shared_ptr<Yuna::AI::PathNode> &pNode2){
				//if same node, do nothing
				if (pNode.get() == pNode2.get() || Yuna::Math::Distance(pNode2->mPosition, pNode->mPosition) >= (size * 3.f))
					return ;
				bool colliding = false;
				//if path between two nodes collide with a block
				blockList->ForEach(sf::FloatRect(pNode->mPosition - sf::Vector2f(size * 3.f, size * 3.f), sf::Vector2f(size * 6.f, size * 6.f))
					, [&colliding, pNode, pNode2, size](const std::shared_ptr<Block> &pBlock){
					if (Yuna::Physics::LineRectCollision(
						pNode->mPosition + sf::Vector2f(size / 2.f, size / 2.f) + sf::Vector2f(0, -1), //I have absolutely zero shame for this...
						pNode2->mPosition + sf::Vector2f(size / 2.f, size / 2.f) + sf::Vector2f(0, -1),
						sf::FloatRect(pBlock->GetPosition(), sf::Vector2f(size, size))))
					{
						colliding = true;
					}
				});
				//check if possible path allready exists
				if (std::count_if(pNode->mConnectedPaths.begin(), pNode->mConnectedPaths.end(),
					[pNode2](const Yuna::AI::Path &path){
						return (path.mTarget.get() == pNode2.get());
					}))
				{
					//path exists but is colliding with block -> remove path from both nodes
					if (colliding && !pNode2->mIsBreakable && !pNode->mIsBreakable) {
						pNode->mConnectedPaths.remove_if([pNode2](Yuna::AI::Path &data){
							return (data.mTarget.get() == pNode2.get());
						});
						pNode2->mConnectedPaths.remove_if([pNode](Yuna::AI::Path &data){
							return (data.mTarget.get() == pNode.get());
						});
					}
					return ;
				}
				//no collision and none of the blocks are breakable and distance is less than x, create nodes
				if (!colliding || ((pNode2->mIsBreakable || pNode->mIsBreakable) && Yuna::Math::Distance(pNode2->mPosition, pNode->mPosition) <= size))
				{
					pNode2->mConnectedPaths.push_back(Yuna::AI::Path());
					pNode2->mConnectedPaths.back().mTarget = pNode;
					pNode2->mConnectedPaths.back().cost = Yuna::Math::Distance(pNode2->mPosition, pNode->mPosition);
					pNode->mConnectedPaths.push_back(Yuna::AI::Path());
					pNode->mConnectedPaths.back().mTarget = pNode2;
					pNode->mConnectedPaths.back().cost = Yuna::Math::Distance(pNode2->mPosition, pNode->mPosition);
					if (pNode2->mIsBreakable || pNode->mIsBreakable)
					{
						pNode2->mConnectedPaths.back().cost += 2000.f;
						pNode->mConnectedPaths.back().cost += 2000.f;
					}
					return ;
				}
			});
	});
};

