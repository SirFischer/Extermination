#include "GameApplication.hpp"

#include "States/StateFactory.hpp"

GameApplication::GameApplication(/* args */)
{
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(1);
	mWindow.SetTitle("Extermination");
	Yuna::Core::Console::Init();
}

GameApplication::~GameApplication()
{
}
