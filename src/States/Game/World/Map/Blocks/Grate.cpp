/*
 * File: Grate.cpp
 * Project: Extermination
 * File Created: Sunday, 6th March 2022 11:30:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 18th February 2023 2:58:46 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Grate.hpp"

Grate::Grate(/* args */)
{
	mTexturePath = "assets/textures/grate-sheet.png";
	mIsBreakable = true;
	mShootThrough = true;
	mHealth = 200;
	mMaxHealth = 200;
	mHealth = mMaxHealth;
}

Grate::~Grate()
{
}

void Grate::Update()
{
	if ((mHealth / mMaxHealth) < 0.5f) SetTextureRect(sf::IntRect(128, 0, 64, 64));
	else if ((mHealth / mMaxHealth) < 0.7f) SetTextureRect(sf::IntRect(64, 0, 64, 64));
}