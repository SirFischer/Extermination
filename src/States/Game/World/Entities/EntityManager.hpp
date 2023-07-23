/*
 * File: EntityManager.hpp
 * File Created: Thursday, 29th December 2022 11:32:03 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:37:40 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include <list>

#include "Entity.hpp"
#include "Enemy/Enemy.hpp"
#include "Map.hpp"
#include "ProjectileManager.hpp"
#include "Yuna.hpp"

class EntityManager
{
	private:
	std::shared_ptr<Entity>					mPlayer = nullptr;
	std::shared_ptr<Entity>					mBase = nullptr;
	std::list<std::shared_ptr<Entity>>		mEntities = std::list<std::shared_ptr<Entity>>();
	Map										*mMap = nullptr;
	Yuna::Core::ResourceManager				*mResourceManager = nullptr;

	public:

	EntityManager(Yuna::Core::ResourceManager *pResourceManager, Map *pMap);
	~EntityManager();

	uint16_t	GetEntityCount() {return (mEntities.size());}
	uint16_t	GetEnemyCount() {
		uint16_t count = 0;
		for (auto &entity : mEntities)
			if (entity->GetType() == EntityType::ENEMY)
				count++;
		return (count);
	}

	void	AddEntity(std::shared_ptr<Entity> pEntity);
	void	AddPlayer(std::shared_ptr<Entity> pEntity);
	void	AddBase(std::shared_ptr<Entity> pEntity);
	void	RemoveEntity(std::shared_ptr<Entity> pEntity);

	void	SpawnEnemy();

	void	ForEach(std::function<bool(std::shared_ptr<Entity>)> pFunction);

	void	Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime);
	void	Render(Yuna::Core::Window *pWindow);
};