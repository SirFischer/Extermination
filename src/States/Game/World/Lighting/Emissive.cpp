#include "Emissive.hpp"

#include <cmath>
#include <vector>

namespace
{
	sf::Texture	mGradientTexture;
	sf::Sprite	mScratchSprite;
	bool		mReady = false;
}

void	Emissive::Init()
{
	if (mReady)
		return;

	std::vector<sf::Uint8> pixels(kGradientSize * kGradientSize * 4);
	const float center = static_cast<float>(kGradientSize) / 2.f;
	const float radius = static_cast<float>(kGradientSize) / 2.f;

	for (unsigned int y = 0; y < kGradientSize; ++y)
	{
		for (unsigned int x = 0; x < kGradientSize; ++x)
		{
			const float dx = (static_cast<float>(x) + 0.5f) - center;
			const float dy = (static_cast<float>(y) + 0.5f) - center;
			const float d = std::sqrt(dx * dx + dy * dy) / radius;

			float a = 0.f;
			if (d <= kGradientInner)
				a = 1.f;
			else if (d < 1.f)
				a = std::pow(1.f - (d - kGradientInner) / (1.f - kGradientInner), kGradientFalloff);

			if (a < 0.f)
				a = 0.f;
			if (a > 1.f)
				a = 1.f;

			const sf::Uint8 value = static_cast<sf::Uint8>(255.f * a);
			const size_t index = (static_cast<size_t>(y) * kGradientSize + x) * 4;

			pixels[index + 0] = value;
			pixels[index + 1] = value;
			pixels[index + 2] = value;
			pixels[index + 3] = value;
		}
	}

	if (!mGradientTexture.create(kGradientSize, kGradientSize))
		return;

	mGradientTexture.update(pixels.data());
	mGradientTexture.setSmooth(true);

	mScratchSprite.setTexture(mGradientTexture, true);
	mScratchSprite.setOrigin(center, center);

	mReady = true;
}

void	Emissive::DrawLight(Yuna::Core::Window *pWindow,
						  const sf::Vector2f &pCenter,
						  float pDiameter,
						  const sf::Color &pTint)
{
	if (!mReady || !pWindow || pDiameter <= 0.f || pTint.a == 0)
		return;

	const float scale = pDiameter / static_cast<float>(kGradientSize);

	mScratchSprite.setPosition(pCenter);
	mScratchSprite.setScale(scale, scale);
	mScratchSprite.setColor(pTint);

	sf::RenderStates states;
	states.blendMode = sf::BlendAdd;
	pWindow->Draw(mScratchSprite, states);
}

const sf::Texture	*Emissive::GetGradientTexture()
{
	return mReady ? &mGradientTexture : nullptr;
}
