/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 16th January 2022 8:31:45 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "World.hpp"


World::World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow)
:mStatistics(pStatistics)
,mMap(pResourceManager)
{
	mPlayer.reset(new Player());
	mPlayer->Init(pResourceManager);
	mPlayer->SetSize(38, 54);
	mPlayer->SetOrigin(12, 4);
	mEntities.push_back(mPlayer);
	mMap.Generate(mMapSize, 300, 3, 5, time(0));
	mCamera.SetView(pWindow->GetView());
	sf::IntRect mapBounds = mMap.GetGlobalBounds();
	mCamera.SetBoundries(sf::IntRect(mapBounds.left, -20000, mapBounds.width + mapBounds.left, 20000));

	Yuna::Core::Console::sCommand reGenMapCommand;
	reGenMapCommand.mHelpShort = "Regenerate map";
	reGenMapCommand.mHelpLong = "This command reapplies perlin noise to generate a brand new map.\nThe first param is the size of the map.\nThe second param is the amplitude\nThe third param is the number of octaves\n and the last param is the start number of segments";
	Map *map = &mMap;
	reGenMapCommand.mFunction = [map](std::vector<std::string> tParams){
		(void)tParams;
		if (tParams.size() != 4)
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		map->Generate(std::stoi(tParams.at(0)), std::stoi(tParams.at(1)), std::stoi(tParams.at(2)), std::stoi(tParams.at(3)), time(0));
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(reGenMapCommand, "regenerate_map");
}

World::~World()
{
}

void	World::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	for (auto &entity : mEntities)
	{
		mMap.UpdateEntity(entity.get());
		entity->Update(pEventHandler, pDeltaTime);
	}
	mStatistics->SetPosition(mPlayer->GetPosition());
	mStatistics->SetVelocity(mPlayer->GetVelocity());
	mCamera.SetTargetPosition(sf::Vector2f(mPlayer->GetPosition().x + mPlayer->GetGlobalBounds().width, mPlayer->GetPosition().y + mPlayer->GetGlobalBounds().height));
	mCamera.Update(pDeltaTime);
}

void	World::Render(Yuna::Core::Window *pWindow)
{
	pWindow->SetView(mCamera.GetView());
	mMap.Render(pWindow, mCamera.GetView());
	for (auto &entity : mEntities)
		entity->Render(pWindow);
	pWindow->ResetView(true);
}
