/*
 * File: Foliage.cpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:53:26 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 9th June 2022 9:54:36 pm
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
}

Foliage::~Foliage()
{
}