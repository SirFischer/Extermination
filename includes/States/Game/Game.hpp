/*
 * File: Game.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:25:47 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 26th February 2022 4:21:37 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "World.hpp"
#include "Statistics.hpp"
#include "../../Actions.hpp"
#include "Config.hpp"

class Game : public Yuna::Core::State
{
private:
	World	mWorld;

	sf::Clock	mFPSClock;
	Statistics	mStatistics;

	void	Update();
	void	HandleEvents();
	void	Render();
	
	void	InitGameControls();
	void	InitGameCommands();

	//Commands
	void	InitExitCommand(bool *active, Yuna::Core::eStateControls *action);
	void	InitQtreeRenderingCommand();


public:
	Game(Yuna::Core::Window* tWindow);
	~Game();

	void	Init();

};

