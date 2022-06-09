/*
 * File: Foliage.cpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:53:26 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 6th June 2022 11:35:43 am
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