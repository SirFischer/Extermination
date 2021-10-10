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
}

void	Menu::Update()
{

}

void	Menu::HandleEvents()
{
	mEventHandler.HandleEvent();
}

void	Menu::Render()
{
	mWindow->Clear();
	mf::GUI::Render();
	mWindow->Render();
}