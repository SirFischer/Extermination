/*
 * File: Crate.cpp
 * Project: Extermination
 * File Created: Sunday, 6th March 2022 11:30:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 18th February 2023 2:58:46 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Crate.hpp"

Crate::Crate(/* args */)
{
	mTexturePath = "assets/textures/crate-sheet.png";
	mIsBreakable = true;
	mMaxHealth = 400;
	mHealth = mMaxHealth;
}

Crate::~Crate()
{
}

void Crate::Update()
{
	if ((mHealth / mMaxHealth) < 0.25f) SetTextureRect(sf::IntRect(192, 0, 64, 64));
	else if ((mHealth / mMaxHealth) < 0.5f) SetTextureRect(sf::IntRect(128, 0, 64, 64));
	else if ((mHealth / mMaxHealth) < 0.75f) SetTextureRect(sf::IntRect(64, 0, 64, 64));
}