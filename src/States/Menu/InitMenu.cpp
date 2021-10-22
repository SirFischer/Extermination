#include "Menu.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	//Exit button
	bool *active = &mActive;
	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Transparent, sf::Color(50, 50, 50, 120))
	->SetClickEvent([active](){
		*active = false;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Exit")
	->SetTextPosition(10, 5));
}

void	Menu::InitMenuControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
}