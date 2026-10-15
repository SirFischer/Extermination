#pragma once

#include <SFML/Graphics.hpp>
#include "Yuna.hpp"
#include "Emissive.hpp"

class MuzzleFlashManager
{
private:
	MuzzleFlashManager();

public:
	~MuzzleFlashManager();

	// Spawns a flash at the muzzle. pAngle is the shot angle in degrees,
	// matching Weapon::Shoot's parameter.
	static void	AddFlash(const sf::Vector2f &pPos, float pAngle);

	static void	Update(float pDeltaTime);
	static void	Render(Yuna::Core::Window *pWindow);
};
