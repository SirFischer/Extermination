#include "Menu.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	//Exit button
	bool *active = &mActive;
	Yuna::Core::eStateControls *stateAction = &mStateAction;
	uint8_t	*nextState = &mNextState;

	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Transparent, sf::Color(50, 50, 50, 120))
	->SetClickEvent([active, stateAction, nextState](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::NEXT_STATE;
		*nextState = (uint8_t)eStates::GAME;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Play")
	->SetTextPosition(10, 5)
	->SetPosition(45, 300)->SetPositionPercentage(true, false));

	mf::GUI::AddWidget(mf::Button::Create(sf::Color::Transparent, sf::Color(50, 50, 50, 120))
	->SetClickEvent([active, stateAction](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::EXIT;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Exit")
	->SetTextPosition(10, 5)
	->SetPosition(45, 400)->SetPositionPercentage(true, false));

}

void	Menu::InitMenuControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
}