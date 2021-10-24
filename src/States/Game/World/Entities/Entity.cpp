/*
 * File: Entity.cpp
 * Project: Extermination
 * File Created: Saturday, 23rd October 2021 12:20:45 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 23rd October 2021 5:08:27 pm
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
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/images/logo_small_trans.png"));
	std::cout << (long long)pResourceManager->LoadTexture("assets/images/logo_small_trans.png").get() << std::endl;
	mSprite.setPosition(0, 0);
}

void	Entity::Update(Yuna::Core::EventHandler *pEventHandler)
{
	(void)pEventHandler;
}

void	Entity::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mSprite);
}
