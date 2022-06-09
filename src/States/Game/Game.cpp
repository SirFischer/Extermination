/*
 * File: Game.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:26:53 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Monday, 6th June 2022 9:25:04 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Game.hpp"

Game::Game(Yuna::Core::Window* tWindow)
:State(tWindow)
,mWorld(&mResourceManager, &mStatistics, mWindow)
,mStatistics(&mResourceManager)
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
	Yuna::Core::Console::mEventHandler = &mEventHandler;
	Yuna::Core::Console::mActionNames = GetActionNames();
	Yuna::Core::Console::ProcessFile("assets/scripts/DefaultBindings.cfg");
	Yuna::Core::Console::ProcessFile("assets/scripts/UserBindings.cfg");
	mWindow->SetVSync(true);
}

void	Game::Update()
{
	Yuna::Core::Console::Update();
	if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_TOGGLE))
	{
		Yuna::Core::Console::ToggleConsole();
		mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_TOGGLE, false);
	}
	if (Yuna::Core::Console::IsOpen())
	{
		if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_CONFIRM))
		{
			Yuna::Core::Console::ProcessConsoleCommand();
			mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_CONFIRM, false);
		}
		if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY))
		{
			Yuna::Core::Console::GetNextInCommandHistory();
			mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY, false);
		}
		if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY))
		{
			Yuna::Core::Console::GetPreviousInCommandHistory();
			mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY, false);
		}
	}
	else
	{
		mWorld.Update(&mEventHandler, mDeltaTime);
		//Update HUD
	}
	if (mFPSClock.getElapsedTime().asSeconds() > 1.f)
	{
		mFPSClock.restart();
		mStatistics.SetFPS(mFPS);
		mStatistics.SetFrameTime(mFrameTime);
	}
	mStatistics.Update();
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
	mHUD.Render(mWindow);
	mf::GUI::Render();
	mStatistics.Render(mWindow);
	mWindow->Render();
}