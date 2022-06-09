/*
 * File: Foliage.hpp
 * Project: Extermination
 * File Created: Sunday, 5th June 2022 7:52:12 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 9th June 2022 9:54:18 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Block.hpp"

enum class eFoliageType
{
	DEAD_BUSH,
	CACTUS_BIG,
	CACTUS_SMALL,
	SKULL
};

class Foliage : public Block
{
private:

public:
	Foliage(const eFoliageType &pType);
	~Foliage();
};