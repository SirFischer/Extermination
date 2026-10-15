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

void	Game::InitHistoryCommand()
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "Prints the console command history to stdout (the real terminal), newest first.\nUseful when the in-game console is hard to read or when you want the history in a log file.\nOptionally pass a count to limit how many entries are printed.";
	command.mHelpShort = "Print console command history to stdout";
	command.mFunction = [](const std::vector<std::string> &tParams) {
		if (tParams.size() > 1)
		{
			return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
		}
		const std::deque<std::string>	&history = Yuna::Core::Console::GetHistory();
		size_t							count = history.size();
		if (tParams.size() == 1)
		{
			try
			{
				count = std::stoul(tParams.back());
			}
			catch (const std::exception &)
			{
				return (Yuna::Core::Console::eCommandStatus::BAD_ARGUMENTS);
			}
		}
		if (count > history.size())
			count = history.size();
		std::cout << "--- console history (" << count << "/" << history.size() << ", newest first) ---" << std::endl;
		for (size_t i = 0; i < count; ++i)
			std::cout << "  " << history[i] << std::endl;
		std::cout << "--- end of history ---" << std::endl;
		Yuna::Core::Console::AddString("Printed " + std::to_string(count) + " history entries to stdout.");
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "history");
}

void	Game::InitStatsCommand()
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "Prints runtime diagnostics to stdout (the real terminal): FPS, frame time, entity/enemy counts, next-wave countdown and player position/velocity.\nUseful for troubleshooting without relying on screenshots.";
	command.mHelpShort = "Print runtime diagnostics to stdout";
	command.mFunction = [this](const std::vector<std::string> &tParams) {
		(void)tParams;
		std::cout << "--- game stats ---" << std::endl;
		std::cout << "  fps:            " << mStatistics.GetFPS() << std::endl;
		std::cout << "  frame time:     " << mStatistics.GetFrameTime() << " ms" << std::endl;
		std::cout << "  entities:       " << mWorld.GetEntityCount() << std::endl;
		std::cout << "  enemies:        " << mWorld.GetEnemyCount() << std::endl;
		std::cout << "  next wave in:   " << mWorld.GetNextWaveTimeLeft() << " s" << std::endl;
		std::cout << "  player pos:     " << mStatistics.GetPosition().x << ", " << mStatistics.GetPosition().y << std::endl;
		std::cout << "  player vel:     " << mStatistics.GetVelocity().x << ", " << mStatistics.GetVelocity().y << std::endl;
		std::cout << "  coins:          " << mStatistics.GetCoins() << std::endl;
		std::cout << "--- end of stats ---" << std::endl;
		Yuna::Core::Console::AddString("Printed game stats to stdout.");
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "stats");
}

void	Game::InitNextWaveCommand()
{
	Yuna::Core::Console::sCommand command;
	command.mHelpLong = "Immediately launches the next wave, bypassing the auto-launch countdown.\nDebug/cheat command: it lets you drive the game without pressing the on-screen button.";
	command.mHelpShort = "Force-launch the next wave";
	command.mFunction = [this](const std::vector<std::string> &tParams) {
		(void)tParams;
		mWorld.NextWave();
		std::cout << "next_wave: forced wave launch (enemies now: " << mWorld.GetEnemyCount() << ")" << std::endl;
		Yuna::Core::Console::AddString("Next wave launched.");
		return (Yuna::Core::Console::eCommandStatus::SUCCESS);
	};
	Yuna::Core::Console::AddCommand(command, "next_wave");
}