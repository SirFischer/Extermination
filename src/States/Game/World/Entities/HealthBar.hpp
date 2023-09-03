#pragma once

#include "Yuna.hpp"

class HealthBar
{
private:
	struct HealthBarFrame
	{
		float		mMin;
		float		mMax;
		sf::Texture	*mTexture;
	};

	std::vector<HealthBarFrame>	mFrames;
	sf::Sprite					mSprite;

public:
	HealthBar(/* args */);
	~HealthBar();

	void	AddFrame(float pMin, float pMax, sf::Texture *pTexture);

	void	Update(float pHealth, sf::Vector2f pPosition);
	void	Render(Yuna::Core::Window *pWindow);
};
