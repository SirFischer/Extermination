/*
 * File: ParticleManager.cpp
 * Project: Extermination
 * File Created: Sunday, 18th December 2022 8:33:22 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 18th December 2022 9:26:01 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "ParticleManager.hpp"

std::list<ParticleEffect> ParticleManager::mParticleEffects = std::list<ParticleEffect>();

ParticleManager::ParticleManager(/* args */)
{
}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::AddParticleEffect(const ParticleEffect &pParticleEffect)
{
	mParticleEffects.push_front(pParticleEffect);
}

void ParticleManager::ForEachParticleEffect(std::function<void(ParticleEffect &)> pFunction)
{
	for (auto &effect : mParticleEffects)
	{
		pFunction(effect);
	}
}

void ParticleManager::Update(float pDeltatime)
{
	for (auto &effect : mParticleEffects)
	{
		if (effect.IsActive())
		{
			effect.Update(pDeltatime);
			//handleParticleCollisions
		}
		else
		{
			mParticleEffects.remove(effect);
			break;
		}
	}
	while (mParticleEffects.size() > MAX_PARTICLE_EFFECTS)
	{
		mParticleEffects.pop_back();
	}
}

void ParticleManager::Render(Yuna::Core::Window *pWindow)
{
	for (auto &effect : mParticleEffects)
	{
		effect.Render(pWindow);
	}
}