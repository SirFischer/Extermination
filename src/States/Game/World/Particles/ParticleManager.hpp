/*
 * File: ParticleManager.hpp
 * Project: Extermination
 * File Created: Sunday, 18th December 2022 8:33:15 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 18th December 2022 9:26:25 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once
#include <list>
#include "ParticleEffect.hpp"

#define MAX_PARTICLE_EFFECTS 25

class ParticleManager
{
private:
	ParticleManager(/* args */);

	static std::list<ParticleEffect> mParticleEffects;

public:
	~ParticleManager();

	static void AddParticleEffect(const ParticleEffect &pParticleEffect);
	static void ForEachParticleEffect(std::function<void(ParticleEffect &)> pFunction);

	static void Update(float pDeltatime);
	static void Render(Yuna::Core::Window *pWindow);
};
