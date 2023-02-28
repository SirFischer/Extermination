/*
 * File: HUD.hpp
 * Project: Extermination
 * File Created: Monday, 28th February 2022 3:54:34 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:16:53 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include "Yuna.hpp"

class HUD
{
private:
	mf::Button *mNextWaveButton = nullptr;

public:
	HUD(/* args */);
	~HUD();

	void	InitNextWaveButton(const std::function<void()> &pClickAction);
	void	HandleNextWaveButton(sf::Event &pEvent);
	void	RenderNextWaveButton(Yuna::Core::Window *pWindow);
	
};

