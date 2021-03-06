/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 8:54:32 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "World.hpp"

#include "Items/CrateItem.hpp"
#include "Map/Blocks/Crate.hpp"


World::World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow)
:mProjectileManager(pResourceManager)
,mStatistics(pStatistics)
,mMap(pResourceManager, pWindow)
{
	mWindow = pWindow;
	mPlayer.reset(new Player());
	mPlayer->Init(pResourceManager);
	mPlayer->SetSize(38, 54);
	mPlayer->SetOrigin(12, 4);
	mEntities.push_back(mPlayer);
	mMap.Generate(mMapSize, 200, 3, 4, time(0));
	mCamera.SetView(pWindow->GetView());
	sf::IntRect mapBounds = mMap.GetGlobalBounds();
	mCamera.SetBoundries(sf::IntRect(mapBounds.left, -20000, mapBounds.width + mapBounds.left, 20000));
	mCamera.SetZoom(0.85);

	Weapon *weapon = new Weapon(pResourceManager, &mProjectileManager);
	weapon->AddPrimaryAction([weapon, pWindow, cam = &mCamera, manager = &mProjectileManager, player = &mPlayer](){
		sf::Vector2f pos;
		sf::Vector2f playerPos = player->get()->GetPosition() + sf::Vector2f(35, 30);
		pWindow->SetView(cam->GetView());
		pos = sf::Vector2f(pWindow->GetViewMousePos());
		pWindow->ResetView(true);
		sf::Vector2f delta = playerPos - pos;
		float rotation = -((std::atan2(delta.x, delta.y) / M_PI) * 180.f) - 90.f;
		playerPos += sf::Vector2f(std::cos((rotation / 180.f) * M_PI) * 15.f, std::sin((rotation / 180.f) * M_PI) * 15.f);
		weapon->Shoot(rotation, playerPos);
		if (rotation < 90.f && rotation > -90.f)
		{
			if (player->get()->IsFacingLeft())
				player->get()->WalkRight(1.f/128.f);
		}
		else
		{
			if (!player->get()->IsFacingLeft())
				player->get()->WalkLeft(1.f/128.f);
		}
	});
	mPlayer->EquipItem(weapon);
	
	CrateItem *testItem = new CrateItem(pResourceManager);
	testItem->AddPrimaryAction([map = &mMap, pWindow, cam = &mCamera](){
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

	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.03f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/featherclouds.png").get());
	
	mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.06f, 0.0f));
	mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/Mountains.png").get());
	
	// mBackgrounds.push_back(Background(sf::Vector2i(mCamera.GetView().getSize())));
	// mBackgrounds.back().SetMoveFactor(sf::Vector2f(0.05f, 0.15f));
	// mBackgrounds.back().LoadBackground(pResourceManager->LoadTexture("assets/textures/clouds_bg.png").get());
	
}

World::~World()
{
}


void	World::HandleBulletCollisions(const sf::FloatRect &pRect)
{
	mMap.GetBlockTree()->get()->ForEach(pRect, [manager = &mProjectileManager](const std::shared_ptr<Block> &pBlock){
		manager->HandleCollisions(pBlock.get());
	});
}

void	World::HandleParticleCollisions(ParticleEffect *pEffect)
{
	sf::FloatRect rect(pEffect->GetInitialPosition() - sf::Vector2f(400, 400), sf::Vector2f(800, 800));

	mMap.GetBlockTree()->get()->ForEach(rect, [particleEffect = pEffect](const std::shared_ptr<Block> &pBlock){
		if (!pBlock->IsSolid())
			return ;
		particleEffect->HandleCollision(pBlock.get());
	});
}



void	World::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	auto viewRect = sf::FloatRect(
		sf::Vector2f(mCamera.GetView().getCenter().x - ((mCamera.GetView().getSize().x / 2.f) + 64), 
		mCamera.GetView().getCenter().y - ((mCamera.GetView().getSize().y / 2.f) + 64)),
		sf::Vector2f(mCamera.GetView().getSize().x + (64 * 2.f),
		mCamera.GetView().getSize().y + (64 * 2.f)));
	viewRect.left -= 500;
	viewRect.width += 1000;
	mMap.Update(pDeltaTime, viewRect);
	HandleBulletCollisions(viewRect);
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
		if (entity.get() != mPlayer.get())
			mProjectileManager.HandleCollisions(entity.get(), &mParticleEffects);
		if (!entity->IsAlive())
		{
			mEntities.remove(entity);
			break ;
		}
	}
	mProjectileManager.Update(pDeltaTime);
	mStatistics->SetPosition(mPlayer->GetPosition());
	mStatistics->SetVelocity(mPlayer->GetVelocity());
	mCamera.SetTargetPosition(sf::Vector2f(mPlayer->GetPosition().x + 150.f, mPlayer->GetPosition().y + 100.f));
	mCamera.Update(pDeltaTime);
	for (auto &background : mBackgrounds)
	{
		background.Update(mCamera.GetPosition());
	}
	for (auto &particles : mParticleEffects)
	{
		if (particles.IsActive())
		{
			particles.Update();
			HandleParticleCollisions(&particles);
			//collision check with map
		}
		else
		{
			mParticleEffects.remove(particles);
			break;
		}
	}
	//performance issues
	while (mParticleEffects.size() > 10)
		mParticleEffects.pop_back();
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
	mProjectileManager.Render(pWindow);
	for (auto &entity : mEntities)
		entity->Render(pWindow);
	for (auto &particles : mParticleEffects)
		particles.Render(pWindow);
	pWindow->ResetView(true);
}


void	World::InitItems()
{
	
}