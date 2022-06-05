/*
 * File: Foliage.cpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:53:26 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 5th June 2022 8:09:25 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#include "Foliage.hpp"

Foliage::Foliage(/* args */)
{
	mTexturePath = "assets/textures/Foliage.png";
	mIsBreakable = true;
	mSolid = false;
}

Foliage::~Foliage()
{
}