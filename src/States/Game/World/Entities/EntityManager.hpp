/*
 * File: EntityManager.hpp
 * File Created: Thursday, 29th December 2022 11:32:03 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 25th February 2023 4:16:15 pm
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

class EntityManager
{
	private:
	std::shared_ptr<Entity>					mPlayer = nullptr;
	std::list<std::shared_ptr<Entity>>		mEntities = std::list<std::shared_ptr<Entity>>();
	Map										*mMap = nullptr;

	public:

	EntityManager(Map *pMap);
	~EntityManager();

	void	AddEntity(std::shared_ptr<Entity> pEntity);
	void	AddPlayer(std::shared_ptr<Entity> pEntity);
	void	RemoveEntity(std::shared_ptr<Entity> pEntity);

	void	ForEach(std::function<bool(std::shared_ptr<Entity>)> pFunction);

	void	Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime);
	void	Render(Yuna::Core::Window *pWindow);
};