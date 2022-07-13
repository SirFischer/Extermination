/*
 * File: ParticleEffect.cpp
 * Project: Extermination
 * File Created: Tuesday, 12th July 2022 7:15:34 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:44:45 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "ParticleEffect.hpp"


ParticleEffect::ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount, float pDirection, float pSpread)
{
	mForce = pForce;
	mPosition = pPos;
	mCircle.setRadius(pRadius);
	for (int i = 0; i < pCount; i++)
	{
		Particle particle;
		particle.mColor = sf::Color::Red;
		particle.mPos = pPos;
		mParticles.push_back(particle);
	}
	InitSpray(pDirection, pSpread);
}

ParticleEffect::ParticleEffect(sf::Vector2f pPos, float pForce, float pRadius, int pCount)
{
	mForce = pForce;
	mPosition = pPos;
	mCircle.setRadius(pRadius);
	for (int i = 0; i < pCount; i++)
	{
		Particle particle;
		particle.mColor = sf::Color::Red;
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
		//float	spread = ((1.f/1000.f) * pSpread) * (float)(random() % 1000) - (tSpread / 2.0f);
		float	angle = pDirection + newspread; //(tan(newspread / 2.0) * 2.f);
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


void		ParticleEffect::Update()
{
	for (auto &particle : mParticles)
	{
		if (!particle.mIsHit)
		{
			particle.mVelocity.y += mGravity;
			particle.mPos += particle.mVelocity;
		}
		if (mLifeTimeClock.getElapsedTime().asSeconds() > mLifeTime.asSeconds())
		{
			particle.mColor = sf::Color(particle.mColor.r, particle.mColor.g, particle.mColor.b, (255.f / (((mLifeTimeClock.getElapsedTime().asSeconds() - mLifeTime.asSeconds()) * 4.f) + 1.f)));
			if (particle.mColor.a < 5.f)
				mIsActive = false;
		}
	}
}

void		ParticleEffect::HandleCollision(Block *pBlock)
{
	for (auto &particle : mParticles)
	{
		if (sf::FloatRect(pBlock->GetPosition(), pBlock->GetSize()).contains(particle.mPos))
			particle.mIsHit = true;
	}
}

void		ParticleEffect::Render(Yuna::Core::Window *pWindow)
{
	for (auto &particle : mParticles)
	{
		mCircle.setPosition(particle.mPos);
		mCircle.setFillColor(particle.mColor);
		pWindow->Draw(mCircle);
	}
}