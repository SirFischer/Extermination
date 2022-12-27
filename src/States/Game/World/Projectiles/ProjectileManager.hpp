/*
 * File: ProjectileManager.hpp
 * Project: Extermination
 * File Created: Thursday, 7th July 2022 9:18:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 18th December 2022 8:52:46 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <list>

#include <Yuna.hpp>
#include "Projectile.hpp"
#include "ProjectileTypes.hpp"
#include "Block.hpp"
#include "Entity.hpp"
#include "ParticleEffect.hpp"
#include "ParticleManager.hpp"

class ProjectileManager
{
private:
	// dependencies
	static Yuna::Core::ResourceManager *mResourceManager;

	static std::list<Projectile *> mProjectiles;
	static sf::Sprite mSprite;

public:
	
	ProjectileManager(Yuna::Core::ResourceManager *pResourceManager);
	~ProjectileManager();

	static void AddProjectile(Projectile *pProjectile);
	static void HandleCollisions(Block *pBlock);
	static void HandleCollisions(Entity *pEntity);

	static void Init(Yuna::Core::ResourceManager *pResourceManager);
	static void Update(float pDeltatime);
	static void Render(Yuna::Core::Window *pWindow);
};
