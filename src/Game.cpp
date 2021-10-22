#include "Game.hpp"

#include "States.hpp"
#include "StateFactory.hpp"

Game::Game(/* args */)
{
	mStateManager.SetStateFactory(stateFactory);
	mStateManager.SetEntryState(0);
	Yuna::Core::Console::Init();
}

Game::~Game()
{
}