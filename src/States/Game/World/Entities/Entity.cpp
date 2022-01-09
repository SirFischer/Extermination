/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 9th January 2022 7:50:19 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Entities/Entity.hpp"


Entity::Entity(/* args */)
{
	
}

Entity::~Entity()
{
}

void	Entity::Init(Yuna::Core::ResourceManager *pResourceManager)
{
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/player/Soldier_01.png"));
	mSize = sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
}

void	Entity::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	(void)mDeltaTime;
	(void)pEventHandler;
	mAnimations[mCurrentAnimation].Update();
	sf::IntRect rect = mAnimations[mCurrentAnimation].GetCurrentFrame();
	mSprite.setTextureRect((mFacingLeft) ? sf::IntRect(rect.left + 64, rect.top, -rect.width, rect.height) : rect);
}

void	Entity::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mSprite);
}
