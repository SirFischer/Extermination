/*
 * File: Game.hpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:25:47 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 3:33:22 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "../../Actions.hpp"

class Game : public Yuna::Core::State
{
private:
	void	Update();
	void	HandleEvents();
	void	Render();
	
	void	InitGameControls();
public:
	Game(Yuna::Core::Window* tWindow);
	~Game();

	void	Init();
};

