/*
 * File: Foliage.hpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:52:12 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 6th June 2022 11:28:18 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Block.hpp"

enum class eFoliageType
{
	DEAD_BUSH,
	CACTUS_BIG
};

class Foliage : public Block
{
private:

public:
	Foliage(const eFoliageType &pType);
	~Foliage();
};