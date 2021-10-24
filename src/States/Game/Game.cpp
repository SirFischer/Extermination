/*
 * File: Game.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:26:53 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 23rd October 2021 5:09:17 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Game.hpp"

Game::Game(Yuna::Core::Window* tWindow)
:State(tWindow)
,mWorld(&mResourceManager)
{
	
}

Game::~Game()
{
}

void	Game::Init()
{
	mf::GUI::ClearWidgets();
	InitGameControls();
	InitGameCommands();
	Yuna::Core::Console::InitUI();
}

void	Game::Update()
{
	Yuna::Core::Console::Update();
	if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_TOGGLE))
	{
		Yuna::Core::Console::ToggleConsole();
		mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_TOGGLE, false);
	}
	if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_CONFIRM))
	{
		Yuna::Core::Console::ProcessConsoleCommand();
		mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_CONFIRM, false);
	}
	mWorld.Update(&mEventHandler);
}

void	Game::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
	}
}

void	Game::Render()
{
	mWindow->Clear(sf::Color::Cyan);
	mWorld.Render(mWindow);
	mf::GUI::Render();
	mWindow->Render();
}