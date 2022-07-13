/*
 * File: ProjectileManager.cpp
 * Project: Extermination
 * File Created: Thursday, 7th July 2022 9:18:52 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:37:46 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "ProjectileManager.hpp"

ProjectileManager::ProjectileManager(Yuna::Core::ResourceManager *pResourceManager)
{
	mResourceManager = pResourceManager;
}

ProjectileManager::~ProjectileManager()
{
}

void	ProjectileManager::AddProjectile(Projectile *pProjectile)
{
	//adds projectile at the right place in list
	std::list<Projectile *>::iterator it = mProjectiles.begin();
	while (it != mProjectiles.end())
	{
		if ((*it)->mType == pProjectile->mType)
		{
			mProjectiles.insert(it, pProjectile);
			return ;
		}
		it++;
	}
	//no item of same type exists
	mProjectiles.push_front(pProjectile);
}

void	ProjectileManager::HandleCollisions(Block *pBlock)
{
	for (auto &projectile : mProjectiles)
	{
		if (sf::FloatRect(pBlock->GetPosition(), pBlock->GetSize()).intersects(sf::FloatRect(projectile->mPos, sf::Vector2f(8, 4))) ||
			projectile->mLifeClock.getElapsedTime().asSeconds() > 5.f)
		{
			if (pBlock->IsBreakable())
			{
				pBlock->TakeDamage(projectile->mDamage);
			}
			mProjectiles.remove(projectile);
			break ;
		}
	}
}

void					ProjectileManager::HandleCollisions(Entity *pEntity, std::list<ParticleEffect> *pList)
{
	for (auto &projectile : mProjectiles)
	{
		if (pEntity->GetGlobalBounds().intersects(sf::FloatRect(projectile->mPos, sf::Vector2f(8, 4))))
		{
			pEntity->TakeDamage(projectile->mDamage, projectile->mAngle, projectile->mKnockback);
			mProjectiles.remove(projectile);
			pList->push_front(ParticleEffect(projectile->mPos, projectile->mKnockback, 2.f, 50.f, (projectile->mAngle / 180.f) * M_PI, M_PI / 4.f));
			pList->front().SetParticleColor(sf::Color(0x8b0000));
			HandleCollisions(pEntity, pList);
			break ;
		}
	}
}



void	ProjectileManager::Update(float pDeltatime)
{
	for (auto &projectile : mProjectiles)
	{
		//logic goes here
		projectile->mPos += projectile->mVelocity * pDeltatime;
	}
}

void	ProjectileManager::Render(Yuna::Core::Window *pWindow)
{
	int i = -1;
	for (auto &projectile : mProjectiles)
	{
		//check if type is different, if yes load new texture
		if (i <= (int)projectile->mType)
		{
			i = (int)projectile->mType;
			switch (projectile->mType)
			{
			case ProjectileType::BULLET:
				mSprite.setTexture(*mResourceManager->LoadTexture("assets/textures/Bullet.png"));
				break;
			default:
				break;
			}
		}
		mSprite.setPosition(projectile->mPos);
		mSprite.setRotation(projectile->mAngle);
		pWindow->Draw(mSprite);
	}
}