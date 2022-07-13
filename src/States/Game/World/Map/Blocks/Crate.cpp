/*
 * File: Crate.cpp
 * Project: Extermination
 * File Created: Sunday, 6th March 2022 11:30:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 13th July 2022 7:59:01 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#include "Crate.hpp"

Crate::Crate(/* args */)
{
	mTexturePath = "assets/textures/crate-sheet.png";
	mIsBreakable = true;
	mHealth = 400;
}

Crate::~Crate()
{
}