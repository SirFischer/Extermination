/*
 * File: World.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:49 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:38:09 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "World.hpp"

#include "Items/CrateItem.hpp"
#include "Map/Blocks/Crate.hpp"
#include "Map/Blocks/Grate.hpp"


World::World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow)
:mStatistics(pStatistics)
,mMap(pResourceManager, pWindow)
,mEntityManager(pResourceManager, &mMap, &mPickableManager)
,mWaveManager(&mEntityManager)
{
	ProjectileManager::Init(pResourceManager);
	mWindow = pWindow;
	mInventory = std::make_shared<Inventory>();
	mPlayer = std::make_shared<Player>(mInventory);
	mPlayer->Init(pResourceManager);
	mPlayer->SetSize(38, 54);
	mPlayer->SetOrigin(12, 4);
	mEntityManager.AddPlayer(mPlayer);
	mMap.Generate(MAP_SIZE, 200, 3, 4, time(0));
	mCamera.SetView(pWindow->GetView());
	sf::IntRect mapBounds = mMap.GetGlobalBounds();
	mCamera.SetBoundries(sf::IntRect(mapBounds.left, -20000, mapBounds.width + mapBounds.left, 20000));
	mCamera.SetZoom(0.85);

	// TEST ITEMS
	Weapon *weapon = new Weapon(pResourceManager);
	weapon->AddPrimaryAction([weapon, pWindow, cam = &mCamera, player = &mPlayer](){
		sf::Vector2f pos;
		sf::Vector2f playerPos = player->get()->GetPosition() + sf::Vector2f(35, 30);
		pWindow->SetView(cam->GetView());
		pos = sf::Vector2f(pWindow->GetViewMousePos());
		pWindow->ResetView(true);
		float rotation = ((Yuna::Math::Angle(playerPos, pos) / M_PI) * 180.f);
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
		block->SetParticleColor(sf::Color(78, 53, 36));
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


	//GRATE
	GrateItem *testItem2 = new GrateItem(pResourceManager);
	testItem2->AddPrimaryAction([map = &mMap, pWindow, cam = &mCamera](){
		auto block = std::make_shared<Grate>();
		block->SetParticleColor(sf::Color(78, 53, 36));
		block->SetSize(sf::Vector2f(64, 64));
		pWindow->SetView(cam->GetView());
		block->SetPosition(sf::Vector2f(pWindow->GetViewMousePos()));
		pWindow->ResetView(true);
		map->AddBlock(block);
	});
	testItem2->AddSecondaryAction([map = &mMap, pWindow, cam = &mCamera]() {
		pWindow->SetView(cam->GetView());
		map->RemoveBlock(pWindow->GetViewMousePos());
		pWindow->ResetView(true);
	});
	mPlayer->EquipItem(testItem2);
	mGrateItem = testItem2;

	//COINS
	Pickable testPickable(pResourceManager, sf::Vector2f(100, 100));
	mPickableManager.addPickable(testPickable);

	Pickable testPickable2(pResourceManager, sf::Vector2f(300, 100));
	mPickableManager.addPickable(testPickable2);

	////////////

	InitBackgrounds(pResourceManager);
	InitConsoleCommands(pResourceManager);
	InitBase(pResourceManager);

}

World::~World()
{
}

void	World::UpdateViewRect()
{
	auto viewRect = sf::FloatRect(
		sf::Vector2f(mCamera.GetView().getCenter().x - ((mCamera.GetView().getSize().x / 2.f) + 64), 
		mCamera.GetView().getCenter().y - ((mCamera.GetView().getSize().y / 2.f) + 64)),
		sf::Vector2f(mCamera.GetView().getSize().x + (64 * 2.f),
		mCamera.GetView().getSize().y + (64 * 2.f)));
	viewRect.left -= 500;
	viewRect.width += 1000;
	mViewRect = viewRect;
}

void	World::HandleBulletCollisions(const sf::FloatRect &pRect)
{
	mMap.GetBlockTree()->get()->ForEach(pRect, [](const std::shared_ptr<Block> &pBlock){
		ProjectileManager::HandleCollisions(pBlock.get());
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

void	World::NextWave()
{
	mWaveManager.NextWave();
}


void	World::Update(Yuna::Core::EventHandler *pEventHandler, float pDeltaTime)
{
	UpdateViewRect();
	
	HandleBulletCollisions(mViewRect);

	mPickableManager.update(pDeltaTime);

	mEntityManager.Update(pEventHandler, pDeltaTime);

	auto pickable = mPickableManager.checkCollision(mPlayer->GetGlobalBounds());
	if (pickable)
	{
		mPickableManager.removePickable(*pickable);

		if (pickable->getType() == PickableType::COIN)
			mStatistics->SetCoins(mStatistics->GetCoins() + 1);
	}

	mMap.Update(pDeltaTime, mViewRect);

	ProjectileManager::Update(pDeltaTime);
	mStatistics->SetPosition(mPlayer->GetPosition());
	mStatistics->SetVelocity(mPlayer->GetVelocity());
	mCamera.SetTargetPosition(sf::Vector2f(mPlayer->GetPosition().x + 150.f, mPlayer->GetPosition().y + 100.f));
	mCamera.Update(pDeltaTime);
	for (auto &background : mBackgrounds)
	{
		background.Update(mCamera.GetPosition());
	}
	ParticleManager::Update(pDeltaTime);
	ParticleManager::ForEachParticleEffect([this](ParticleEffect &pEffect){
		HandleParticleCollisions(&pEffect);
	});

	mWindow->SetView(mCamera.GetView());
	mCrateItem->SetIsValid(mMap.CanBlockBePlacedAt(mWindow->GetViewMousePos()));
	mGrateItem->SetIsValid(mMap.CanBlockBePlacedAt(mWindow->GetViewMousePos()));
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
	ProjectileManager::Render(pWindow);
	mPickableManager.render(pWindow);
	mEntityManager.Render(pWindow);
	ParticleManager::Render(pWindow);
	pWindow->ResetView(true);
	mInventory->Render(pWindow);
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
		
}

void	World::InitItems()
{
	
}

void	World::InitBase(Yuna::Core::ResourceManager *pResourceManager)
{
	mBase = std::make_shared<Base>(pResourceManager);
	mBase->SetPosition(sf::Vector2f(0, mMap.GetBaseVerticalPosition()));
	mEntityManager.AddBase(mBase);
}

void	World::InitShader(Yuna::Core::ResourceManager *pResourceManager)
{
	mGlobalLightingShader = pResourceManager->LoadShader("assets/shaders/global_lighting.frag");
}