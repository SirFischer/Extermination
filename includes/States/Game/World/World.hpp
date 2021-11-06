/*
 * File: World.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 6th November 2021 12:19:15 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Player.hpp"
#include "Map.hpp"
#include <math.h>

class World
{
private:
	std::shared_ptr<Player>					mPlayer;
	std::vector<std::shared_ptr<Entity>>	mEntities;

	Map										mMap;

public:
	World(Yuna::Core::ResourceManager *pResourceManager);
	~World();

	void	Update(Yuna::Core::EventHandler	*pEventHandler, float mDeltaTime);
	void	Render(Yuna::Core::Window		*pWindow);
};

