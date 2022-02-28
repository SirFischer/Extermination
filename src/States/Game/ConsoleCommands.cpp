/*
 * File: ConsoleCommands.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:03:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 26th February 2022 4:32:12 pm
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

void	Game::InitQtreeRenderingCommand()
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "Enables rendering of the rectangle bounds of the Quad Tree.\n-1 = Render all bounds\n0 = Render nothing\n1 or more = how many layers must be rendered.";
	command.mHelpShort = "Enables rendering of Qtree";
	command.mFunction = [](const std::vector<std::string> &tParams) {
		if (tParams.size() > 1 || !tParams.size())
		{
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		}
		Config::mRenderQTree = std::stoi(tParams.back());
		Yuna::Core::Console::AddString("Qtree rendering set to " + tParams.back());
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "render_qtree");
}