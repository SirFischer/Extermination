/*
 * File: Weapon.cpp
 * Project: Extermination
 * File Created: Wednesday, 16th February 2022 6:35:05 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 29th June 2022 6:47:45 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Weapon.hpp"

Weapon::Weapon(Yuna::Core::ResourceManager *pResourceManager)
{
	mTexturePath = "assets/images/player/gun.png";
	mSprite.setTexture(*pResourceManager->LoadTexture("assets/textures/crosshair.png"));
	
}

Weapon::~Weapon()
{
	
}

void	Weapon::Render(Yuna::Core::Window *pWindow)
{
	sf::Vector2f	pos = pWindow->GetViewMousePos();
	mSprite.setPosition(pos - sf::Vector2f(32, 32));
	pWindow->Draw(mSprite);
}
