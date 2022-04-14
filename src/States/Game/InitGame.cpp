/*
 * File: InitGame.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:38:16 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 14th April 2022 8:02:33 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Game.hpp"

void	Game::InitGameControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}

void	Game::InitGameCommands()
{
	InitExitCommand(&mActive, &mStateAction);
	InitQtreeRenderingCommand();
	InitPathNodeRenderingCommand();
}