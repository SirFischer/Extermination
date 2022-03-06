/*
 * File: HUD.hpp
 * Project: Extermination
 * File Created: Monday, 28th February 2022 3:54:34 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 6th March 2022 11:17:33 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"

class HUD
{
private:
	/* data */
public:
	HUD(/* args */);
	~HUD();

	void	Render(Yuna::Core::Window *pWindow);
};

