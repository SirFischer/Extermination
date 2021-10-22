/*
 * File: Menu.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:06:48 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Friday, 22nd October 2021 1:14:43 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Menu.hpp"

Menu::Menu(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	
}

Menu::~Menu()
{
}

void	Menu::Init()
{
	InitMenuItems();
	InitMenuControls();
	Yuna::Core::Console::InitUI();
}

void	Menu::Update()
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
}

void	Menu::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		mEventHandler.HandleEvent(event);
	}
}

void	Menu::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}