#include "HealthBar.hpp"

HealthBar::HealthBar(/* args */)
{
}

HealthBar::~HealthBar()
{
}

void	HealthBar::SetScale(sf::Vector2f pScale)
{
	mSprite.setScale(pScale);
}

void	HealthBar::SetOrigin(sf::Vector2f pOrigin)
{
	mSprite.setOrigin(pOrigin);
}

void HealthBar::Mirror(bool mirrored)
{
	auto oldScale = mSprite.getScale();
	if (mirrored)
		mSprite.setScale(-std::abs(oldScale.x), oldScale.y);
	else
		mSprite.setScale(std::abs(oldScale.x), oldScale.y);
	
}

void	HealthBar::AddFrame(float pMin, float pMax, sf::Texture *pTexture)
{
	mFrames.push_back((HealthBarFrame){.mMin = pMin, .mMax = pMax, .mTexture = pTexture});
}

void	HealthBar::Update(float pHealth, sf::Vector2f pPosition)
{
	mSprite.setPosition(pPosition);

	for (auto &frame : mFrames)
	{
		if (pHealth >= frame.mMin && pHealth <= frame.mMax)
		{
			mSprite.setTexture(*frame.mTexture);
			return;
		}
	}
}

void	HealthBar::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mSprite);
}