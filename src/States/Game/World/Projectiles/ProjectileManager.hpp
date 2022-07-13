/*
 * File: ProjectileManager.hpp
 * Project: Extermination
 * File Created: Thursday, 7th July 2022 9:18:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:28:56 am
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


class ProjectileManager
{
private:
	//dependencies
	Yuna::Core::ResourceManager *mResourceManager = nullptr;

	std::list<Projectile *>	mProjectiles;
	sf::Sprite				mSprite;

public:
	ProjectileManager(Yuna::Core::ResourceManager *pResourceManager);
	~ProjectileManager();

	void					AddProjectile(Projectile *pProjectile);
	void					HandleCollisions(Block *pBlock);
	void					HandleCollisions(Entity *pEntity, std::list<ParticleEffect> *pList);

	void					Update(float pDeltatime);
	void					Render(Yuna::Core::Window *pWindow);
};


