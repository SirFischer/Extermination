/*
 * File: Hands.hpp
 * Project: Extermination
 * File Created: Sunday, 3rd July 2022 1:26:32 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 3rd July 2022 1:33:58 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */

#pragma once

#include "Item.hpp"

class Hands : public Item
{
private:

public:
	Hands()
	{
		mIsHands = true;
	}
	~Hands(){}
};

