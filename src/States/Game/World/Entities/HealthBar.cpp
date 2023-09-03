#include "HealthBar.hpp"

HealthBar::HealthBar(/* args */)
{
}

HealthBar::~HealthBar()
{
}

void	HealthBar::AddFrame(float pMin, float pMax, sf::Texture *pTexture)
{
	mFrames.push_back((HealthBarFrame){.mMin = pMin, .mMax = pMax, .mTexture = pTexture});
}

void	HealthBar::Update(float pHealth, sf::Vector2f pPosition)
{
	for (auto &frame : mFrames)
	{
		if (pHealth >= frame.mMin && pHealth <= frame.mMax)
		{
			mSprite.setTexture(*frame.mTexture);
			return;
		}
	}
	mSprite.setPosition(pPosition);
}

void	HealthBar::Render(Yuna::Core::Window *pWindow)
{
	pWindow->Draw(mSprite);
}