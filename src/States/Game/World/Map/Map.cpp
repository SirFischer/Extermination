/*
 * File: Map.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 7:33:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 1st June 2022 4:50:15 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Map.hpp"

#include "../../Config.hpp"

Map::Map(Yuna::Core::ResourceManager *pResourceManager, Yuna::Core::Window *pWindow)
{
	mResourceManager = pResourceManager;
	mWindow = pWindow;

}

Map::~Map()
{
}


void	Map::UpdateEntity(Entity *pEntity)
{
	ApplyCollisionDetection(pEntity);
	LockPlayerToMap(pEntity);
}

void	Map::Update(float pDeltaTime)
{
	(void)pDeltaTime;
}

void	Map::AddBlock(Block *pBlock)
{
	if (!pBlock)
		return ;

	pBlock->SetPosition(sf::Vector2f(std::floor(pBlock->GetPosition().x / mGridSize) * mGridSize, std::floor(pBlock->GetPosition().y / mGridSize) * mGridSize));
	pBlock->SetSize(sf::Vector2f(mGridSize, mGridSize));
	const sf::FloatRect range = sf::FloatRect(pBlock->GetPosition() - sf::Vector2f(mGridSize, mGridSize), sf::Vector2f(mGridSize * 3, mGridSize * 3));
	bool	collides = false;
	mBlockQTree->ForEach(range, [&collides, pos = pBlock->GetPosition()] (const Block &pBlock) {
		if (sf::FloatRect(
			pBlock.GetPosition(),
			pBlock.GetSize()).contains(
				sf::Vector2f(pos.x + (pBlock.GetSize().x / 2), pos.y + (pBlock.GetSize().y / 2))
				)
			)
			collides = true;
	});
	if (!collides)
	{
		mBlockQTree->Insert(*pBlock, sf::FloatRect(pBlock->GetPosition(), sf::Vector2f(mGridSize, mGridSize)));
		AddPathNode(pBlock);
	}
}

void	Map::RemoveBlock(sf::Vector2f pPos)
{
	pPos.x = (std::floor(pPos.x / mGridSize) * mGridSize) + 32;
	pPos.y = (std::floor(pPos.y / mGridSize) * mGridSize) + 32;
	const sf::FloatRect range = sf::FloatRect(pPos - sf::Vector2f(mGridSize * 2, mGridSize * 2), sf::Vector2f(mGridSize * 4, mGridSize * 4));
	if (mBlockQTree->DeleteAt(range, pPos))
	{
		//Delete path nodes...
		RemovePathNode(pPos);
		bool replaceNode = false;
		bool blockAbove = false;
		sf::Vector2f pos;
		mBlockQTree->ForEach(range, [gridSize = mGridSize, pPos, &replaceNode, &blockAbove, &pos](const Block &pBlock) {
			if (sf::FloatRect(pBlock.GetPosition(), sf::Vector2f(gridSize, gridSize)).contains(pPos + sf::Vector2f(0, gridSize))) {
				replaceNode = true;
				pos = pBlock.GetPosition();
			}
			if (sf::FloatRect(pBlock.GetPosition(), sf::Vector2f(gridSize, gridSize)).contains(pPos - sf::Vector2f(0, gridSize)))
				blockAbove = true;
		});

		if (!blockAbove)
			RemovePathNode(pPos - sf::Vector2f(0, mGridSize));

		if (replaceNode) {
			auto node = std::make_shared<Yuna::AI::PathNode>();
			node->mPosition = pos - sf::Vector2f(0, mGridSize);
			AddNode(node);
		}
	}
}


void	Map::Render(Yuna::Core::Window *pWindow, const sf::View	&pView)
{
	std::string		lastPath = "";
	mSprite.setScale(1, 1);

	mBlockQTree->ForEach(sf::FloatRect(
		sf::Vector2f(pView.getCenter().x - ((pView.getSize().x / 2.f) + mGridSize), 
		pView.getCenter().y - ((pView.getSize().y / 2.f) + mGridSize)),
		sf::Vector2f(pView.getSize().x + (mGridSize * 2.f),
		pView.getSize().y + (mGridSize * 2.f))),
		[&lastPath, sprite = &mSprite, resourceManager = mResourceManager, gridSize = mGridSize, pWindow](const Block &pBlock){
			sprite->setColor(pBlock.GetColor());
			if (pBlock.GetTexturePath() != lastPath)
			{
				sf::Texture	*texture = resourceManager->LoadTexture(pBlock.GetTexturePath()).get();
				sprite->setTexture(*texture);
				sprite->setScale(sf::Vector2f((float)gridSize / texture->getSize().x, (float)gridSize / texture->getSize().y));
				lastPath = pBlock.GetTexturePath();
			}
			sprite->setPosition(pBlock.GetPosition());
			pWindow->Draw(*sprite);
		});
	if (Config::mRenderPathNodes)
		RenderPathNodes(pWindow, pView);
	if (Config::mRenderQTree)
		mBlockQTree->Render(pWindow->GetRenderWindow(), Config::mRenderQTree);
}

void	Map::RenderPathNodes(Yuna::Core::Window *pWindow, const sf::View &pView)
{
	sf::CircleShape node(32);
	node.setFillColor(sf::Color::Red);
	mPathNodes->ForEach(sf::FloatRect(
		sf::Vector2f(pView.getCenter().x - ((pView.getSize().x / 2.f) + mGridSize), 
		pView.getCenter().y - ((pView.getSize().y / 2.f) + mGridSize)),
		sf::Vector2f(pView.getSize().x + (mGridSize * 2.f),
		pView.getSize().y + (mGridSize * 2.f))), [&node, pWindow, size = mGridSize](const std::shared_ptr<Yuna::AI::PathNode> &pNode){
			sf::VertexArray line(sf::Lines, 2);
			line[0].position = pNode->mPosition + sf::Vector2f(size / 2.f, size / 2.f);

			node.setPosition(pNode->mPosition);
			node.setFillColor((pNode->mIsBreakable) ? sf::Color::Red : sf::Color::Green);
			pWindow->Draw(node);
		});

		//render lines
		mPathNodes->ForEach(sf::FloatRect(
		sf::Vector2f(pView.getCenter().x - ((pView.getSize().x / 2.f) + mGridSize), 
		pView.getCenter().y - ((pView.getSize().y / 2.f) + mGridSize)),
		sf::Vector2f(pView.getSize().x + (mGridSize * 2.f),
		pView.getSize().y + (mGridSize * 2.f))), [&node, pWindow, size = mGridSize](const std::shared_ptr<Yuna::AI::PathNode> &pNode){
			sf::VertexArray line(sf::Lines, 2);
			line[0].position = pNode->mPosition + sf::Vector2f(size / 2.f, size / 2.f);

			for (auto &path : pNode->mConnectedPaths)
			{
				line[1] = path.mTarget->mPosition + sf::Vector2f(size / 2.f, size / 2.f);
				//TODO: change color of path based on action needed
				pWindow->Draw(line);

			}
		});
}


