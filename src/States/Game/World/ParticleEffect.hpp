/*
 * File: ParticleEffect.hpp
 * Project: Extermination
 * File Created: Tuesday, 12th July 2022 7:15:15 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:43:07 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"
#include "Block.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <random>

struct Particle {
	sf::Vector2f	mPos;
	sf::Vector2f	mVelocity;
	sf::Color		mColor;
	bool			mIsHit = false;
};

class ParticleEffect
{
private:
	std::vector<Particle>	mParticles;

	sf::CircleShape			mCircle;

	float					mGravity = 0.1f;
	float					mForce = 0.1f;
	sf::Vector2f			mPosition;

	sf::Clock				mLifeTimeClock;
	sf::Time				mLifeTime = sf::seconds(3);

	bool					mIsActive = true;

	void					InitSpray(float pDirection, float pSpread);
	void					InitExplosion();
public:
	friend class Map;

	ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount, float pDirection, float pSpread);
	ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount);
	~ParticleEffect();

	bool operator == (const ParticleEffect& s) const { return mLifeTimeClock.getElapsedTime().asSeconds() == s.mLifeTimeClock.getElapsedTime().asSeconds(); }

	void					SetParticleColor(sf::Color	pColor);

	sf::Vector2f			GetInitialPosition() {return (mPosition);}

	void					Update();
	void					HandleCollision(Block *pBlock);
	void					Render(Yuna::Core::Window *pWindow);

	bool					IsActive(){return (mIsActive);}
	
};

