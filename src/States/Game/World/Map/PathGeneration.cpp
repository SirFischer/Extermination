/*
 * File: PathGeneration.cpp
 * Project: Extermination
 * File Created: Saturday, 26th February 2022 8:41:36 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 1st June 2022 4:54:39 pm
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
	auto node = std::make_shared<Yuna::AI::PathNode>();
	node->mPosition = tBlock->GetPosition();
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
		[topnode, &intersectsAbove, size = mGridSize](const Block &pBlock){
			//is there a block above?
			if (sf::FloatRect(pBlock.GetPosition(), pBlock.GetSize()).contains(topnode->mPosition + sf::Vector2f(size / 2.f, size / 2.f)))
				intersectsAbove = true;
		});

	if (!intersectsAbove)
		AddNode(topnode);
}

void	Map::AddNode(std::shared_ptr<Yuna::AI::PathNode> pNode)
{
	(void)pNode;
	auto rNode = mPathNodes->Insert(pNode, sf::FloatRect(pNode->mPosition, sf::Vector2f(mGridSize, mGridSize)));

	if (!rNode)
		return;
	//create paths
	if (!pNode->mIsBreakable)
	{
		mPathNodes->ForEach(sf::FloatRect(pNode->mPosition - sf::Vector2f(mGridSize * 3, mGridSize * 3),
		sf::Vector2f(mGridSize * 6, mGridSize * 6)),
		[pNode, size = mGridSize, blocks = &mBlockQTree](std::shared_ptr<Yuna::AI::PathNode> &node){
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
			if (!isColliding && !node->mIsBreakable &&
				Yuna::Math::Distance(node->mPosition, pNode->mPosition) < (size * 3.f) &&
				node.get() != pNode.get() &&
				std::find_if(node->mConnectedPaths.begin(), node->mConnectedPaths.end(), [pNode](const Yuna::AI::Path& path){
					return (path.mTarget.get() == pNode.get());
				}) == node->mConnectedPaths.end())
			{
				node->mConnectedPaths.push_back(Yuna::AI::Path());
			 	node->mConnectedPaths.back().mTarget = pNode;
				node->mConnectedPaths.back().cost = Yuna::Math::Distance(node->mPosition, pNode->mPosition) + ((node->mIsBreakable || pNode->mIsBreakable) ? 2000.f : 0.f);
			 	pNode->mConnectedPaths.push_back(Yuna::AI::Path());
			 	pNode->mConnectedPaths.back().mTarget = node;
				pNode->mConnectedPaths.back().cost = Yuna::Math::Distance(node->mPosition, pNode->mPosition) + ((node->mIsBreakable || pNode->mIsBreakable) ? 2000.f : 0.f);

				return ;
			}
		});
	}
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
}

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