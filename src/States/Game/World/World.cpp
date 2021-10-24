/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 24th October 2021 7:57:12 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "World.hpp"


World::World(Yuna::Core::ResourceManager *pResourceManager)
:mMap(pResourceManager)
{
	mPlayer.reset(new Player());
	mPlayer->Init(pResourceManager);
	mEntities.push_back(mPlayer);
	mMap.Load("assets/maps/163501584986.map");
}

World::~World()
{
}

void	World::Update(Yuna::Core::EventHandler *pEventHandler)
{
	for (auto &entity : mEntities)
		entity->Update(pEventHandler);
}

void	World::Render(Yuna::Core::Window *pWindow)
{
	mMap.Render(pWindow);
	for (auto &entity : mEntities)
		entity->Render(pWindow);
}
