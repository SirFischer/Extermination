/*
 * File: ParticleEffect.cpp
 * Project: Extermination
 * File Created: Tuesday, 12th July 2022 7:15:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 27th December 2022 9:16:43 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "ParticleEffect.hpp"


ParticleEffect::ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount, float pDirection, float pSpread, sf::Color pColor)
{
	mForce = pForce;
	mPosition = pPos;
	mCircle.setRadius(pRadius);
	for (int i = 0; i < pCount; i++)
	{
		Particle particle;
		particle.mColor = pColor;
		particle.mColor.a *= (rand() % 100) / 100.f;
		particle.mPos = pPos;
		mParticles.push_back(particle);
	}
	InitSpray(pDirection, pSpread);
}

ParticleEffect::ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount, sf::Color pColor)
{
	mForce = pForce;
	mPosition = pPos;
	mCircle.setRadius(pRadius);
	for (int i = 0; i < pCount; i++)
	{
		Particle particle;
		particle.mColor = pColor;
		particle.mPos = pPos;
		mParticles.push_back(particle);
	}
	InitExplosion();
}

ParticleEffect::~ParticleEffect()
{
}

void		ParticleEffect::InitSpray(float pDirection, float pSpread)
{
	srand(time(0));
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(pSpread, pSpread / 2.f);
	for (auto &particle : mParticles)
	{
		
		float	newspread = distribution(generator);
		newspread -= (newspread / 2.0f);
		float	angle = pDirection + newspread;
		float	forceVariation = ((1.f/1000.f) * mForce) * (float)(random() % 1000);
		particle.mVelocity = sf::Vector2f(cos(angle) * (forceVariation), sin(angle) * (forceVariation));
	}
}

void		ParticleEffect::InitExplosion()
{
	srand(time(0));
	for (auto &particle : mParticles)
	{
		float	angle = random();
		float	forceVariation = ((1.f/1000.f) * mForce) * (float)(random() % 1000);
		particle.mVelocity = sf::Vector2f(cos(angle) * (forceVariation), sin(angle) * (forceVariation));
	}
}

void		ParticleEffect::SetParticleColor(sf::Color	pColor)
{
	mCircle.setFillColor(pColor);
}


void		ParticleEffect::Update(const float &pDeltatime)
{
	for (auto &particle : mParticles)
	{
		if (!particle.mIsHit)
		{
			particle.mPos += particle.mVelocity * pDeltatime;
			particle.mVelocity.y += mGravity;
		}
		if (mLifeTimeClock.getElapsedTime().asSeconds() > mLifeTime.asSeconds())
		{
			if (particle.mOpacity <= 5.f)
				mIsActive = false;
			particle.mOpacity -=  ((255.f * pDeltatime) / mLifeTime.asSeconds());
			if (particle.mOpacity <= 5.f)
				mIsActive = false;
		}
	}
}

void		ParticleEffect::HandleCollision(Block *pBlock)
{
	for (auto &particle : mParticles)
	{
		if (sf::FloatRect(pBlock->GetPosition(), pBlock->GetSize()).contains(particle.mPos))
		{
			particle.mVelocity = sf::Vector2f(0.f, 0.f);
			particle.mIsHit = true;
		} else {
			particle.mIsHit = false;
		}
	}
}

void		ParticleEffect::Render(Yuna::Core::Window *pWindow)
{
	for (auto &particle : mParticles)
	{
		mCircle.setPosition(particle.mPos);
		mCircle.setFillColor(sf::Color(particle.mColor.r, particle.mColor.g, particle.mColor.b, particle.mOpacity));
		pWindow->Draw(mCircle);
	}
}