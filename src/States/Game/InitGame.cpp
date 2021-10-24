/*
 * File: InitGame.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:38:16 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 8:05:51 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Game.hpp"

void	Game::InitGameControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
}

void	Game::InitGameCommands()
{
	InitExitCommand(&mActive, &mStateAction);
}