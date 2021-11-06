/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 12:59:55 pm
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
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/download.png"));
	mSprite.setPosition(100, -500);

}

void	Entity::Update(Yuna::Core::EventHandler *pEventHandler, float mDeltaTime)
{
	(void)mDeltaTime;
	(void)pEventHandler;
}

void	Entity::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mSprite);
}
