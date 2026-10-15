/*
 * File: Fog.hpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:15 am
 * Author: Marek Fischer
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <Yuna.hpp>

/**
 * Two layers of seamlessly tiling Perlin noise, generated on the CPU at load
 * time and scrolled in world space for parallax plus a slow rightward drift.
 * Drawn with the default alpha blend mode: fog is atmosphere, not light, so it
 * is dimmed by the darkness quad along with the rest of the world.
 */
class Fog
{
private:
	static constexpr int	kLayerCount		= 2;
	static constexpr int	kTextureSize	= 256;
	static constexpr int	kPeriod			= 8;

	sf::Texture		mFogTextures[kLayerCount];
	sf::Sprite		mFogSprites[kLayerCount];
	sf::Vector2f	mMoveFactors[kLayerCount];
	float			mSpeeds[kLayerCount];
	float			mDrift = 0.f;

	void	GenerateFog();

public:
	Fog();
	~Fog();

	void	Render(Yuna::Core::Window *pWindow);
	void	Update(float pDeltaTime, const sf::View &pCameraView);
};
