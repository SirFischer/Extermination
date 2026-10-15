#include "MuzzleFlash.hpp"

#include <cmath>
#include <list>

#define MAX_MUZZLE_FLASHES	16
#define MUZZLE_FLASH_LIFE	0.085f

namespace
{
	struct MuzzleFlash
	{
		sf::Vector2f	mPos;
		float			mAngle;
		float			mElapsed;
		float			mDiameter;
		sf::Color		mTint;
	};

	std::list<MuzzleFlash>	mFlashes;
}

MuzzleFlashManager::MuzzleFlashManager()
{
}

MuzzleFlashManager::~MuzzleFlashManager()
{
}

void	MuzzleFlashManager::AddFlash(const sf::Vector2f &pPos, float pAngle)
{
	MuzzleFlash flash;

	flash.mPos = pPos;
	flash.mAngle = pAngle;
	flash.mElapsed = 0.f;
	flash.mDiameter = 380.f;
	flash.mTint = sf::Color(255, 226, 150, 255);

	mFlashes.push_back(flash);

	while (mFlashes.size() > MAX_MUZZLE_FLASHES)
		mFlashes.pop_front();
}

void	MuzzleFlashManager::Update(float pDeltaTime)
{
	for (MuzzleFlash &flash : mFlashes)
		flash.mElapsed += pDeltaTime;

	while (!mFlashes.empty() && mFlashes.front().mElapsed >= MUZZLE_FLASH_LIFE)
		mFlashes.pop_front();
}

void	MuzzleFlashManager::Render(Yuna::Core::Window *pWindow)
{
	const sf::Texture	*gradient = Emissive::GetGradientTexture();

	if (gradient == nullptr)
		return;

	sf::RenderStates	states;
	states.blendMode = sf::BlendAdd;

	const sf::Vector2u	texSize = gradient->getSize();
	sf::Sprite			core(*gradient);

	core.setOrigin(sf::Vector2f(static_cast<float>(texSize.x) * 0.5f,
								static_cast<float>(texSize.y) * 0.5f));
	core.setScale(sf::Vector2f(0.55f, 0.28f));

	for (const MuzzleFlash &flash : mFlashes)
	{
		const float	ratio = flash.mElapsed / MUZZLE_FLASH_LIFE;
		const float	fade = 1.f - ratio;
		const float	alpha = fade * fade;

		sf::Color	tint = flash.mTint;
		tint.a = static_cast<sf::Uint8>(static_cast<float>(flash.mTint.a) * alpha);

		// The shared gradient peaks at 0.45 so it reads as a soft glow; the
		// flash wants to be punchier, so it draws the light twice.
		Emissive::DrawLight(pWindow, flash.mPos, flash.mDiameter * (0.6f + 0.4f * fade), tint);
		Emissive::DrawLight(pWindow, flash.mPos, flash.mDiameter * (0.6f + 0.4f * fade) * 0.55f, tint);

		core.setPosition(flash.mPos);
		core.setRotation(flash.mAngle);
		core.setColor(tint);

		pWindow->Draw(core, states);
	}
}
