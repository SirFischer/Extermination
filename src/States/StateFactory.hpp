/*
 * File: StateFactory.hpp
 * Project: Extermination
 * File Created: Sunday, 17th October 2021 11:02:38 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 24th September 2022 8:32:13 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "States.hpp"

std::unique_ptr<Yuna::Core::State>	stateFactory(uint8_t tID, Yuna::Core::Window* tWindow)
{
	eStates state = (eStates)tID;
	switch (state)
	{

	case eStates::MENU:
		return (std::make_unique<Menu>(tWindow));
		break;

	default:
		throw std::runtime_error("The ID provided to the stateFactory did not match any state.");
		break;
	}
	return (NULL);
}