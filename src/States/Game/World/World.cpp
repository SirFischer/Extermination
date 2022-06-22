/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 15th June 2022 4:33:01 pm
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
	mWindow = pWindow;
	mPlayer.reset(new Player());
	mPlayer->Init(pResourceManager);
	mPlayer->SetSize(38, 54);
	mPlayer->SetOrigin(12, 4);
	mEntities.push_back(mPlayer);
	mMap.Generate(mMapSize, 200, 3, 5, time(0));
	mCamera.SetView(pWindow->GetView());
	sf::IntRect mapBounds = mMap.GetGlobalBounds();
	mCamera.SetBoundries(sf::IntRect(mapBounds.left, -20000, mapBounds.width + mapBounds.left, 20000));
	mCamera.SetZoom(0.85);

	

	CrateItem *testItem = new CrateItem(pResourceManager);
	testItem->AddPrimaryAction([map = &mMap, pStatistics, pWindow, cam = &mCamera](){
		auto block = std::make_shared<Crate>();
		block->SetSize(sf::Vector2f(64, 64));
		pWindow->SetView(cam->GetView());
		block->SetPosition(sf::Vector2f(pWindow->GetViewMousePos()));
		pWindow->ResetView(true);
		map->AddBlock(block);
	});
	testItem->AddSecondaryAction([map = &mMap, pWindow, cam = &mCamera]() {
		pWindow->SetView(cam->GetView());
		map->RemoveBlock(pWindow->GetViewMousePos());
		pWindow->ResetView(true);
	});
	mPlayer->EquipItem(testItem);
	mCrateItem = testItem;

	InitBackgrounds(pResourceManager);
	InitConsoleCommands(pResourceManager);

}

void	World::InitBackgrounds(Yuna::Core::ResourceManager *pResourceManager)
{
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/background_1.png").get());

	// mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	// mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.02f, 0.0f));
	// mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/clouds_bg.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.03f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/Mountains.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.05f, 0.15f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/clouds_bg.png").get());
	
}

World::~World()
{
}

void	World::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	auto viewRect = sf::FloatRect(
		sf::Vector2f(mCamera.GetView().getCenter().x - ((mCamera.GetView().getSize().x / 2.f) + 64), 
		mCamera.GetView().getCenter().y - ((mCamera.GetView().getSize().y / 2.f) + 64)),
		sf::Vector2f(mCamera.GetView().getSize().x + (64 * 2.f),
		mCamera.GetView().getSize().y + (64 * 2.f)));
	mMap.Update(pDeltaTime, viewRect);
	for (auto &entity : mEntities)
	{
		mMap.UpdateEntity(entity.get());
		entity->Update(pEventHandler, pDeltaTime);
		if (entity->GetType() == EntityType::ENEMY && entity->GetPathRecalcTime() > sf::seconds(1)) {
			auto path = mMap.GetPath(entity->GetPosition(), mPlayer->GetPosition());
			entity->SetTarget(mPlayer->GetPosition());
			entity->SetPath(path);
		}
		//Resolve entity entity collision
		for (auto &entity2 : mEntities)
		{
			if (entity2 != entity)
			{
				entity->ResolveCollision(entity2.get());
			}
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
	mWindow->SetView(mCamera.GetView());
	mCrateItem->SetIsValid(mMap.CanBlockBePlacedAt(mWindow->GetViewMousePos()));
	mWindow->ResetView(true);
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