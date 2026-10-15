#pragma once

#include <SFML/Graphics.hpp>
#include "Yuna.hpp"

namespace Emissive
{
	inline constexpr unsigned int	kGradientSize		= 256;
	inline constexpr float			kGradientInner		= 0.0f;
	inline constexpr float			kGradientFalloff	= 2.2f;
	inline constexpr float			kGradientPeak		= 0.85f;

	void	Init();
	void	DrawLight(Yuna::Core::Window *pWindow,
					  const sf::Vector2f &pCenter,
					  float pDiameter,
					  const sf::Color &pTint = sf::Color::White);
	const sf::Texture	*GetGradientTexture();
}
