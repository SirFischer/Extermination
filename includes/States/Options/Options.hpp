/*
 * File: Options.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:06:35 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 7th November 2021 3:54:18 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "States.hpp"
#include "../../Actions.hpp"

class Options : public Yuna::Core::State
{
private:

	void	InitOptionsItems();
	void	InitGraphicsOptions();
	void	InitOptionsControls();


	void	Update();
	void	HandleEvents();
	void	Render();

	mf::Container	*mOptionsContainer;

	mf::List	*mGraphicsOptionsList = NULL;
	mf::List	*mAudioOptionsList = NULL;
	mf::List	*mControlsOptionsList = NULL;
	mf::List	*mMainOptionsList = NULL;

public:
	void	Init();

	Options(Yuna::Core::Window* tWindow);
	~Options();
};

