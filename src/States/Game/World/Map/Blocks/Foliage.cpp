/*
 * File: Foliage.cpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:53:26 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 12th July 2022 7:38:59 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Foliage.hpp"

Foliage::Foliage(const eFoliageType &pType)
{
	switch (pType)
	{
	case eFoliageType::DEAD_BUSH:
		mTexturePath = "assets/textures/Foliage.png";
		break;
	case eFoliageType::CACTUS_BIG:
		mTexturePath = "assets/textures/cactus-big.png";
		break;
	case eFoliageType::CACTUS_SMALL:
		mTexturePath = "assets/textures/cactus.png";
		break;
	case eFoliageType::SKULL:
		mTexturePath = "assets/textures/skull.png";
		break;
	default:
		mTexturePath = "assets/textures/Foliage.png";
		break;
	}
	mIsBreakable = true;
	mSolid = false;
	mHealth = 1.f;
}

Foliage::~Foliage()
{
}