/*
 * File: World.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th October 2021 7:50:34 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Player.hpp"
#include "Map.hpp"

class World
{
private:
	std::shared_ptr<Player>					mPlayer;
	std::vector<std::shared_ptr<Entity>>	mEntities;

	Map										mMap;

public:
	World(Yuna::Core::ResourceManager *pResourceManager);
	~World();

	void	Update(Yuna::Core::EventHandler	*pEventHandler);
	void	Render(Yuna::Core::Window		*pWindow);
};

