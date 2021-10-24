/*
 * File: ConsoleCommands.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:03:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 8:06:30 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Game.hpp"

void	Game::InitExitCommand(bool *active, Yuna::Core::eStateControls *action)
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "Exit the game completely without going back to menu screen";
	command.mHelpShort = "Exit the game";
	command.mFunction = [active, action](const std::vector<std::string> &tParams){
		*active = false;
		*action = Yuna::Core::eStateControls::EXIT;
		(void)tParams;
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "exit");
}