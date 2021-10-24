/*
 * File: Game.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:25:47 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 23rd October 2021 4:44:42 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "World.hpp"
#include "../../Actions.hpp"

class Game : public Yuna::Core::State
{
private:
	World	mWorld;

	void	Update();
	void	HandleEvents();
	void	Render();
	
	void	InitGameControls();
	void	InitGameCommands();

	//Commands
	void	InitExitCommand(bool *active, Yuna::Core::eStateControls *action);

public:
	Game(Yuna::Core::Window* tWindow);
	~Game();

	void	Init();

};

