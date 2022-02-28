/*
 * File: StateFactory.hpp
 * Project: Extermination
 * File Created: Sunday, 17th October 2021 11:02:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 28th February 2022 3:45:35 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "States.hpp"
#include "Menu/Menu.hpp"
#include "Options/Options.hpp"
#include "Splash/Splash.hpp"
#include "Game/Game.hpp"

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
	case eStates::OPTIONS:
		return (std::make_unique<Options>(tWindow));
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