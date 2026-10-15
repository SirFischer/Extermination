/*
 * File: Fog.cpp
 * Project: Extermination
 * File Created: Thursday, 12th May 2022 5:55:25 am
 * Author: Marek Fischer
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Fog.hpp"

#include <cmath>
#include <vector>

namespace
{
	// Deterministic hash-based lattice gradient, so the noise is identical on
	// every run and needs no asset file.
	float	Hash(int pX, int pY, int pSeed)
	{
		unsigned int h = static_cast<unsigned int>(pX) * 374761393u
					   + static_cast<unsigned int>(pY) * 668265263u
					   + static_cast<unsigned int>(pSeed) * 2246822519u;
		h = (h ^ (h >> 13)) * 1274126177u;
		h ^= (h >> 16);
		return static_cast<float>(h & 0xFFFFu) / 65535.f;
	}

	float	Fade(float pT)
	{
		return pT * pT * pT * (pT * (pT * 6.f - 15.f) + 10.f);
	}

	float	Lerp(float pA, float pB, float pT)
	{
		return pA + (pB - pA) * pT;
	}

	// Value noise on a lattice that wraps every pPeriod cells, which makes the
	// resulting texture tile seamlessly.
	float	ValueNoise(float pX, float pY, int pPeriod, int pSeed)
	{
		const int x0 = static_cast<int>(std::floor(pX));
		const int y0 = static_cast<int>(std::floor(pY));
		const float fx = Fade(pX - static_cast<float>(x0));
		const float fy = Fade(pY - static_cast<float>(y0));

		const int wx0 = ((x0 % pPeriod) + pPeriod) % pPeriod;
		const int wy0 = ((y0 % pPeriod) + pPeriod) % pPeriod;
		const int wx1 = (wx0 + 1) % pPeriod;
		const int wy1 = (wy0 + 1) % pPeriod;

		const float v00 = Hash(wx0, wy0, pSeed);
		const float v10 = Hash(wx1, wy0, pSeed);
		const float v01 = Hash(wx0, wy1, pSeed);
		const float v11 = Hash(wx1, wy1, pSeed);

		return Lerp(Lerp(v00, v10, fx), Lerp(v01, v11, fx), fy);
	}

	// Three octaves of the tiling value noise, normalised to [0, 1].
	float	FractalNoise(float pX, float pY, int pPeriod, int pSeed)
	{
		float value = 0.f;
		float amplitude = 1.f;
		float total = 0.f;
		int period = pPeriod;

		for (int octave = 0; octave < 3; ++octave)
		{
			value += ValueNoise(pX, pY, period, pSeed + octave) * amplitude;
			total += amplitude;
			amplitude *= 0.5f;
			pX *= 2.f;
			pY *= 2.f;
			period *= 2;
		}

		return value / total;
	}
}

Fog::Fog()
{
	mMoveFactors[0] = sf::Vector2f(0.35f, 0.35f);
	mMoveFactors[1] = sf::Vector2f(0.65f, 0.65f);
	mSpeeds[0] = 6.f;
	mSpeeds[1] = 14.f;

	GenerateFog();
}

Fog::~Fog()
{
}

void	Fog::GenerateFog()
{
	const sf::Vector2u windowSize = sf::Vector2u(1920, 1080);

	for (int layer = 0; layer < kLayerCount; ++layer)
	{
		std::vector<sf::Uint8> pixels(kTextureSize * kTextureSize * 4);
		const float step = static_cast<float>(kPeriod) / static_cast<float>(kTextureSize);
		const float opacity = layer == 0 ? 0.30f : 0.22f;

		for (int y = 0; y < kTextureSize; ++y)
		{
			for (int x = 0; x < kTextureSize; ++x)
			{
				const float n = FractalNoise(static_cast<float>(x) * step,
											 static_cast<float>(y) * step,
											 kPeriod, layer * 97 + 13);
				const float a = n * n * opacity;
				const size_t index = (static_cast<size_t>(y) * kTextureSize + x) * 4;

				pixels[index + 0] = 220;
				pixels[index + 1] = 224;
				pixels[index + 2] = 232;
				pixels[index + 3] = static_cast<sf::Uint8>(255.f * (a > 1.f ? 1.f : a));
			}
		}

		if (!mFogTextures[layer].create(kTextureSize, kTextureSize))
			continue;

		mFogTextures[layer].update(pixels.data());
		mFogTextures[layer].setRepeated(true);
		mFogTextures[layer].setSmooth(true);

		mFogSprites[layer].setPosition(0.f, 0.f);
		mFogSprites[layer].setTexture(mFogTextures[layer]);
		mFogSprites[layer].setScale(static_cast<float>(windowSize.x) / static_cast<float>(kTextureSize),
									static_cast<float>(windowSize.y) / static_cast<float>(kTextureSize));
	}
}

void	Fog::Update(float pDeltaTime, const sf::Vector2f &pCameraPosition)
{
	mDrift += pDeltaTime;

	// Match Background's convention: the camera position is its centre, so
	// subtract half the reference viewport before applying the parallax factor.
	const sf::Vector2f centred = pCameraPosition - sf::Vector2f(960.f, 540.f);

	for (int layer = 0; layer < kLayerCount; ++layer)
	{
		// Parallax with the camera, plus a slow rightward drift so the fog
		// keeps moving even when the player stands still.
		const float offsetX = centred.x * mMoveFactors[layer].x
							+ mDrift * mSpeeds[layer];
		const float offsetY = centred.y * mMoveFactors[layer].y;

		mFogSprites[layer].setTextureRect(sf::IntRect(
			static_cast<int>(offsetX),
			static_cast<int>(offsetY),
			kTextureSize,
			kTextureSize));
	}
}

void	Fog::Render(Yuna::Core::Window *pWindow)
{
	if (!pWindow)
		return;

	for (int layer = 0; layer < kLayerCount; ++layer)
		pWindow->Draw(mFogSprites[layer]);
}
