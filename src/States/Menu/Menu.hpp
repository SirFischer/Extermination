/*
 * File: Menu.hpp
 * Project: Extermination
 * File Created: Saturday, 24th September 2022 8:30:53 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 24th September 2022 8:34:36 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2022 Deep Vertic
 */
#pragma once

#include <Yuna.hpp>

class Menu : public Yuna::Core::State
{
private:
	
	void	Update();
	void	HandleEvents();
	void	Render();
public:
	Menu(Yuna::Core::Window* tWindow);
	~Menu();

	void	Init();
};

