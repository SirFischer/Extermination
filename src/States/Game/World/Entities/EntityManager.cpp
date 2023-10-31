/*
 * File: EntityManager.cpp
 * File Created: Thursday, 29th December 2022 11:42:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:38:47 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "EntityManager.hpp"

EntityManager::EntityManager(Yuna::Core::ResourceManager *pResourceManager, Map *pMap)
{
	mMap = pMap;
	mResourceManager = pResourceManager;
}

EntityManager::~EntityManager()
{
}

void	EntityManager::AddEntity(std::shared_ptr<Entity> pEntity)
{
	mEntities.push_back(pEntity);
}

void	EntityManager::AddBase(std::shared_ptr<Entity> pEntity)
{
	mBase = pEntity;
	mEntities.push_back(pEntity);
}

void	EntityManager::AddPlayer(std::shared_ptr<Entity> pEntity)
{
	mPlayer = pEntity;
	mEntities.push_back(pEntity);
}

void	EntityManager::RemoveEntity(std::shared_ptr<Entity> pEntity)
{
	mEntities.remove(pEntity);
}


//forward declare SpawnEnemy<Dog>
template <>
void	EntityManager::SpawnEnemy<Dog>();

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

		if (entity->GetType() == EntityType::ENEMY && entity->GetPathRecalcTime() > sf::seconds(1)) {
			const auto target = (((Enemy *)entity.get())->GetEnemyState() == AIState::State::ATTACK) ? mBase : mPlayer;

			if (!target)
				break ;

			auto path = mMap->GetPath(entity->GetPosition(), target->GetPosition());
			entity->SetTarget(target);
			entity->SetPath(path);
		}

		if (entity.get() != mPlayer.get())
			ProjectileManager::HandleCollisions(entity.get());

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
