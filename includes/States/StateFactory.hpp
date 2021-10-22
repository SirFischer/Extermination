/*
 * File: StateFactory.hpp
 * Project: Extermination
 * File Created: Sunday, 17th October 2021 11:02:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 3:26:46 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "States.hpp"
#include "Menu.hpp"
#include "Splash.hpp"
#include "Game.hpp"

std::unique_ptr<Yuna::Core::State>	stateFactory(uint8_t tID, Yuna::Core::Window* tWindow)
{
	eStates state = (eStates)tID;
	switch (state)
	{
	case eStates::SPLASH:
		return (std::make_unique<Splash>(tWindow));
		break;
	case eStates::MENU:
		return (std::make_unique<Menu>(tWindow));
		break;
	case eStates::GAME:
		return (std::make_unique<Game>(tWindow));
		break;
	default:
		throw std::runtime_error("The ID provided to the stateFactory did not match any state.");
		break;
	}
	return (NULL);
}