/*
 * File: World.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 12th May 2022 4:09:25 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include "Entities/Player/Player.hpp"
#include "Entities/Enemy/Enemy.hpp"
#include "Map/Map.hpp"
#include "../Statistics.hpp"
#include "Camera.hpp"
#include <math.h>

class World
{
private:
	std::shared_ptr<Player>					mPlayer;
	std::vector<std::shared_ptr<Entity>>	mEntities;

	Camera									mCamera;

	Statistics 								*mStatistics = nullptr;
	Map										mMap;

	//Backgrounds
	std::vector<Background>				mBackgrounds;

	const uint32_t							mMapSize = 200;

	void	InitItems();
	void	InitBackgrounds(Yuna::Core::ResourceManager *pResourceManager);

public:
	World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow);
	~World();

	void	Update(Yuna::Core::EventHandler	*pEventHandler, float pDeltaTime);
	void	Render(Yuna::Core::Window		*pWindow);
};

