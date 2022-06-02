/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 2nd June 2022 10:24:08 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "World.hpp"

#include "Items/CrateItem.hpp"
#include "Map/Blocks/Crate.hpp"


World::World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow)
:mStatistics(pStatistics)
,mMap(pResourceManager, pWindow)
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
	mCamera.SetZoom(0.85);

	mEntities.push_back(std::make_shared<Enemy>());
	mEntities.back()->Init(pResourceManager);
	mEntities.back()->SetSize(38, 54);

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
	CrateItem *testItem = new CrateItem(pResourceManager);
	testItem->AddPrimaryAction([map, pStatistics, pWindow, cam = &mCamera](){
		Crate block;
		block.SetSize(sf::Vector2f(64, 64));
		pWindow->SetView(cam->GetView());
		block.SetPosition(sf::Vector2f(pWindow->GetViewMousePos()));
		pWindow->ResetView(true);
		map->AddBlock(&block);
	});
	testItem->AddSecondaryAction([map, pWindow, cam = &mCamera]() {
		pWindow->SetView(cam->GetView());
		map->RemoveBlock(pWindow->GetViewMousePos());
		pWindow->ResetView(true);
	});
	mPlayer->EquipItem(testItem);

	InitBackgrounds(pResourceManager);

}

void	World::InitBackgrounds(Yuna::Core::ResourceManager *pResourceManager)
{
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/sky_lightened.png").get());

	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.01f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/clouds_bg.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.03f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/glacial_mountains_lightened.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.04f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/cloud_lonely.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.04f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/clouds_mg_2.png").get());

}

World::~World()
{
}

void	World::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	mMap.Update(pDeltaTime);
	for (auto &entity : mEntities)
	{
		mMap.UpdateEntity(entity.get());
		entity->Update(pEventHandler, pDeltaTime);
		if (entity->GetType() == EntityType::ENEMY && entity->GetPathRecalcTime() > sf::seconds(1)) {
			auto path = mMap.GetPath(entity->GetPosition(), mPlayer->GetPosition());
			if (path.size())
				path.pop_back();
			entity->SetTarget(mPlayer->GetPosition());
			entity->SetPath(path);
		}
	}
	mStatistics->SetPosition(mPlayer->GetPosition());
	mStatistics->SetVelocity(mPlayer->GetVelocity());
	mCamera.SetTargetPosition(sf::Vector2f(mPlayer->GetPosition().x + mPlayer->GetGlobalBounds().width, mPlayer->GetPosition().y + mPlayer->GetGlobalBounds().height));
	mCamera.Update(pDeltaTime);
	for (auto &background : mBackgrounds)
	{
		background.Update(mCamera.GetPosition());
	}

}

void	World::Render(Yuna::Core::Window *pWindow)
{
	for (auto &background : mBackgrounds)
	{
		background.Render(pWindow);
	}
	pWindow->SetView(mCamera.GetView());
	mMap.Render(pWindow, mCamera.GetView());
	for (auto &entity : mEntities)
		entity->Render(pWindow);
	pWindow->ResetView(true);
}


void	World::InitItems()
{
	
}