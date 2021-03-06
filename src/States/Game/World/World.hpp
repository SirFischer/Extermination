/*
 * File: World.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 9:12:30 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:48:50 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once

#include <math.h>

#include "Entities/Player/Player.hpp"
#include "Entities/Enemy/Enemy.hpp"
#include "Map/Map.hpp"
#include "../Statistics.hpp"
#include "Camera.hpp"
#include "ProjectileManager.hpp"
#include "ParticleEffect.hpp"

class World
{
private:
	std::shared_ptr<Player>					mPlayer;
	std::list<std::shared_ptr<Entity>>		mEntities;
	ProjectileManager						mProjectileManager;
	std::list<ParticleEffect>				mParticleEffects;

	Yuna::Core::Window						*mWindow = nullptr;

	Camera									mCamera;

	Statistics 								*mStatistics = nullptr;
	Map										mMap;

	CrateItem								*mCrateItem = nullptr;

	std::vector<Background>					mBackgrounds;

	const uint32_t							mMapSize = 100;

	void	InitItems();
	void	InitConsoleCommands(Yuna::Core::ResourceManager *pResourceManager);
	void	InitBackgrounds(Yuna::Core::ResourceManager *pResourceManager);

	void	HandleBulletCollisions(const sf::FloatRect &pRect);
	void	HandleParticleCollisions(ParticleEffect *pEffect);

public:
	World(Yuna::Core::ResourceManager *pResourceManager, Statistics *pStatistics, Yuna::Core::Window *pWindow);
	~World();

	void	Update(Yuna::Core::EventHandler	*pEventHandler, float pDeltaTime);
	void	Render(Yuna::Core::Window		*pWindow);
};

