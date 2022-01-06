/*
 * File: Options.cpp
 * Project: Extermination
 * File Created: Saturday, 9th October 2021 10:06:48 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 6th January 2022 8:33:12 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"

Options::Options(Yuna::Core::Window* tWindow)
:State(tWindow)
{
	
}

Options::~Options()
{
}

void	Options::Init()
{
	InitOptionsItems();
	InitOptionsControls();
	InitGraphicsOptions();
	Yuna::Core::Console::InitUI();
	Yuna::Core::Console::mEventHandler = &mEventHandler;
	Yuna::Core::Console::mActionNames = GetActionNames();
	Yuna::Core::Console::ProcessFile("assets/scripts/DefaultBindings.cfg");
	Yuna::Core::Console::ProcessFile("assets/scripts/UserBindings.cfg");
	InitControlsOptions();
}

void	Options::Update()
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
}

void	Options::HandleEvents()
{
	sf::Event event;
	while (mWindow->PollEvent(event))
	{
		if (mListenToNextEvent)
		{
			if (event.type == sf::Event::KeyPressed)
			{
				mEventHandler.BindKey(event.key.code, (uint32_t)mActionToBind);
				mListenToNextEvent = false;
				mButtonToBind->SetText(mEventHandler.GetBindingNames()[event.key.code]);
				InitControlsOptions();
				mControlsOptionsList->SetDisabled(false);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				mEventHandler.BindButton(event.mouseButton.button, (uint32_t)mActionToBind);
				mListenToNextEvent = false;
				mButtonToBind->SetText(mEventHandler.GetBindingNames()[event.key.code + 1000]);
				InitControlsOptions();
				mControlsOptionsList->SetDisabled(false);
			}
		}
		mEventHandler.HandleEvent(event);
	}
}

void	Options::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}