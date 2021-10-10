#include "Menu.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	//Exit button
	bool *active = &mActive;
	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Transparent, sf::Color(50, 50, 50, 120))
	->SetClickEvent([active](){
		*active = false;
	})->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Exit")
	->SetTextPosition(10, 5));
}