/*
 * File: EntityManager.cpp
 * File Created: Thursday, 29th December 2022 11:42:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 29th December 2022 11:53:35 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "EntityManager.hpp"

std::list<std::shared_ptr<Entity>>	EntityManager::mEntities = std::list<std::shared_ptr<Entity>>();

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
}

void	EntityManager::AddEntity(std::shared_ptr<Entity> pEntity)
{
	mEntities.push_back(pEntity);
}

void	EntityManager::RemoveEntity(std::shared_ptr<Entity> pEntity)
{
	mEntities.remove(pEntity);
}

void	EntityManager::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	for (auto entity : mEntities)
	{
		entity->Update(pEventHandler, pDeltaTime);
	}
}

void	EntityManager::Render(Yuna::Core::Window *pWindow)
{
	for (auto entity : mEntities)
	{
		entity->Render(pWindow);
	}
}
