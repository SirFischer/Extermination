/*
 * File: EntityManager.hpp
 * File Created: Thursday, 29th December 2022 11:32:03 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 29th December 2022 11:53:07 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include <list>

#include "Entity.hpp"

class EntityManager
{
	private:
	static std::list<std::shared_ptr<Entity>>		mEntities;
	
	EntityManager();

	public:
	~EntityManager();

	static void	AddEntity(std::shared_ptr<Entity> pEntity);
	static void	RemoveEntity(std::shared_ptr<Entity> pEntity);

	static void	Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime);
	static void	Render(Yuna::Core::Window *pWindow);
};