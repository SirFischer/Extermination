#include "Menu.hpp"

void	Menu::InitMenuItems()
{
	mf::GUI::ClearWidgets();

	//Exit button
	bool *active = &mActive;
	Yuna::Core::eStateControls *stateAction = &mStateAction;
	uint8_t	*nextState = &mNextState;

	mf::GUI::AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([active, stateAction, nextState](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::NEXT_STATE;
		*nextState = (uint8_t)eStates::GAME;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Play")
	->SetTextPosition(15, 5)
	->SetPosition(3, 200)->SetPositionPercentage(true, false));


	mf::GUI::AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([active, stateAction, nextState](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::NEXT_STATE;
		*nextState = (uint8_t)eStates::OPTIONS;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Options")
	->SetTextPosition(15, 5)
	->SetSize(160, 50)
	->SetPosition(3, 300)->SetPositionPercentage(true, false));

	mf::GUI::AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([active, stateAction](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::EXIT;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Exit")
	->SetTextPosition(15, 5)
	->SetPosition(1, 93)->SetPositionPercentage(true, true));

}

void	Menu::InitMenuControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}