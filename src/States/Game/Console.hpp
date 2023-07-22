#pragma once

#include "Yuna.hpp"

class GameConsole {
private:
	Yuna::Core::EventHandler *mEventHandler;

public:
	GameConsole(Yuna::Core::EventHandler *tEventHandler);
	~GameConsole();

	void Init();
	void Update();

	void Toggle() { Yuna::Core::Console::ToggleConsole(); }

	bool IsOpen() { return (Yuna::Core::Console::IsOpen()); }
};