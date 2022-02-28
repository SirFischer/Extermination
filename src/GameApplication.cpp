#include "GameApplication.hpp"

#include "States/StateFactory.hpp"

GameApplication::GameApplication(/* args */)
{
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(0);
	mWindow.SetTitle("Extermination");
	Yuna::Core::Console::Init();
}

GameApplication::~GameApplication()
{
}
