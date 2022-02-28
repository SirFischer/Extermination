/*
 * File: Menu.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:06:35 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 28th February 2022 3:45:50 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "../States.hpp"
#include "../../Actions.hpp"

class Menu : public Yuna::Core::State
{
private:
	void	InitMenuItems();
	void	InitMenuControls();


	void	Update();
	void	HandleEvents();
	void	Render();
public:
	void	Init();

	Menu(Yuna::Core::Window* tWindow);
	~Menu();
};

