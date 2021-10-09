#pragma once

#include "Menu.hpp"

enum class eStates {
	MENU	=	0
};

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