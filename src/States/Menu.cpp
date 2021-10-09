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
	mf::GUI::ClearWidgets();
	bool *active = &mActive;
	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Green, sf::Color::Blue)
	->SetClickEvent([active](){
		*active = false;
	}));
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