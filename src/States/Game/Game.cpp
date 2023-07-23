/*
 * File: Game.cpp
 * Project: Extermination
 * File Created: Friday, 22nd October 2021 2:26:53 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 26th February 2023 3:22:44 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Game.hpp"

Game::Game(Yuna::Core::Window* tWindow)
:State(tWindow)
,mWorld(&mResourceManager, &mStatistics, mWindow)
,mStatistics(&mResourceManager)
,mConsole(&mEventHandler)
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
	mConsole.Init();
	mWindow->SetVSync(true);
	mWindow->SetCursorVisibility(false);

	//HUD
	mHUD.InitNextWaveButton([world = &mWorld](){
		Yuna::Core::Console::AddString("Next Wave");
		world->NextWave();
	});
}

void	Game::Update()
{
	if (mEventHandler.GetEventState((uint32_t)eAction::CONSOLE_TOGGLE))
	{
		mConsole.Toggle();
		mWindow->SetCursorVisibility(mConsole.IsOpen());
		mEventHandler.SetEventState((uint32_t)eAction::CONSOLE_TOGGLE, false);
	}
	mConsole.Update();
	if (!mConsole.IsOpen())
	{
		mWorld.Update(&mEventHandler, mDeltaTime);
	}
	UpdateFPS();
	mStatistics.Update();
}

void	Game::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
		mHUD.HandleNextWaveButton(event);
	}
}

void	Game::Render()
{
	mWindow->Clear(sf::Color::Cyan);
	mWorld.Render(mWindow);
	mf::GUI::Render();
	if (mWorld.GetEnemyCount() == 0) mHUD.RenderNextWaveButton(mWindow);
	mStatistics.Render(mWindow);
	mWindow->Render();
}

void	Game::UpdateFPS()
{
	if (mFPSClock.getElapsedTime().asSeconds() > 1.f)
	{
		mFPSClock.restart();
		mStatistics.SetFPS(mFPS);
		mStatistics.SetFrameTime(mFrameTime);
	}
}
