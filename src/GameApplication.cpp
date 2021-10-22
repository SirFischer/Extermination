#include "GameApplication.hpp"

#include "StateFactory.hpp"

GameApplication::GameApplication(/* args */)
{
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(0);
	Yuna::Core::Console::Init();
}

GameApplication::~GameApplication()
{
}
