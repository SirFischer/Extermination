/*
 * File: EntityManager.cpp
 * File Created: Thursday, 29th December 2022 11:42:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 19th February 2023 3:47:25 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "EntityManager.hpp"

EntityManager::EntityManager(Map *pMap)
{
	mMap = pMap;
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


void	EntityManager::ForEach(std::function<bool(std::shared_ptr<Entity>)> pFunction)
{
	for (auto entity : mEntities)
	{
		if (!pFunction(entity))
			break ;
	}
}

void	EntityManager::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	auto it = mEntities.begin();
	while (it != mEntities.end())
	{
		auto entity = *it;
		entity->Update(pEventHandler, pDeltaTime);

		ForEach([entity](std::shared_ptr<Entity> pEntity2){
			if (pEntity2 != entity)
				entity->ResolveCollision(pEntity2.get());
			return (true);
		});

		if (!entity->IsAlive()) {
			it++;
			RemoveEntity(entity);
			continue;
		}

		mMap->UpdateEntity(entity.get());

		it++;
	}
}

void	EntityManager::Render(Yuna::Core::Window *pWindow)
{
	for (auto entity : mEntities)
	{
		entity->Render(pWindow);
	}
}
