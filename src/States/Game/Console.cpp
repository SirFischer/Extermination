#include "Console.hpp"
#include "../../Actions.hpp"

GameConsole::GameConsole(Yuna::Core::EventHandler *tEventHandler)
:mEventHandler(tEventHandler)
{
}

GameConsole::~GameConsole()
{
}

void GameConsole::Init()
{
	Yuna::Core::Console::InitUI();
	Yuna::Core::Console::mEventHandler = mEventHandler;
	Yuna::Core::Console::mActionNames = GetActionNames();
	Yuna::Core::Console::ProcessFile("assets/scripts/DefaultBindings.cfg");
	Yuna::Core::Console::ProcessFile("assets/scripts/UserBindings.cfg");
}

void GameConsole::Update()
{
	Yuna::Core::Console::Update();
	if (Yuna::Core::Console::IsOpen())
	{
		if (mEventHandler->GetEventState((uint32_t)eAction::CONSOLE_CONFIRM))
		{
			Yuna::Core::Console::ProcessConsoleCommand();
			mEventHandler->SetEventState((uint32_t)eAction::CONSOLE_CONFIRM, false);
		}
		if (mEventHandler->GetEventState((uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY))
		{
			Yuna::Core::Console::GetNextInCommandHistory();
			mEventHandler->SetEventState((uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY, false);
		}
		if (mEventHandler->GetEventState((uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY))
		{
			Yuna::Core::Console::GetPreviousInCommandHistory();
			mEventHandler->SetEventState((uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY, false);
		}
	}
}