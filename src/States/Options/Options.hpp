/*
 * File: Options.hpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:06:35 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 28th February 2022 3:46:03 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#pragma once
#include "Yuna.hpp"
#include "../States.hpp"
#include "../../Actions.hpp"

class Options : public Yuna::Core::State
{
private:

	void	InitOptionsItems();
	void	InitGraphicsOptions();
	void	InitControlsOptions();
	void	InitOptionsControls();
	void	InitButtonBinding(std::string pText, eAction pAction);


	void	Update();
	void	HandleEvents();
	void	Render();

	std::shared_ptr<mf::Container>	mOptionsContainer;

	std::shared_ptr<mf::List>	mGraphicsOptionsList = NULL;
	std::shared_ptr<mf::List>	mAudioOptionsList = NULL;
	std::shared_ptr<mf::List>	mControlsOptionsList = NULL;
	std::shared_ptr<mf::List>	mMainOptionsList = NULL;

	bool		mListenToNextEvent = false;
	eAction		mActionToBind;
	std::shared_ptr<mf::Button>	mButtonToBind = NULL;

	sf::Sound	mHoverSound;
	sf::Sound 	mClickSound;

public:
	void	Init();

	Options(Yuna::Core::Window* tWindow);
	~Options();
};

