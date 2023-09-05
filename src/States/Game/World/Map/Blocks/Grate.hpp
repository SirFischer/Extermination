/*
 * File: Grate.hpp
 * Project: Extermination
 * File Created: Sunday, 6th March 2022 11:28:46 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 18th February 2023 2:50:59 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once
#include "Block.hpp"

class Grate : public Block
{
private:

public:
	Grate(/* args */);
	~Grate();

	void Update();
};

