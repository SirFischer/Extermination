/*
 * File: ConsoleCommands.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 8:03:44 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 14th April 2022 8:06:34 am
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

void	Game::InitPathNodeRenderingCommand()
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "This command enables the rendering of path nodes for easier debuging.\nEnter 1 to enable and 0 to disable this feature.";
	command.mHelpShort = "Enable/Disable pathfinding node rendering";
	command.mFunction = [](const std::vector<std::string> &tParams) {
		if (tParams.size() > 1 || !tParams.size())
		{
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		}
		Config::mRenderPathNodes = (tParams.back() != "0");
		Yuna::Core::Console::AddString(std::string("The pathnode rendering has been set to: ") + ((tParams.back() != "0") ? "enabled" : "disabled"));
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "render_pathnodes");
}