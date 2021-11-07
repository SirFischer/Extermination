/*
 * File: InitOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 7:54:51 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 7th November 2021 5:50:53 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"

void	Options::InitOptionsItems()
{
	mf::GUI::ClearWidgets();

	//Exit button
	bool *active = &mActive;
	Yuna::Core::eStateControls *stateAction = &mStateAction;
	uint8_t	*nextState = &mNextState;

	auto *graphicsList = &mGraphicsOptionsList;
	auto *audioList = &mAudioOptionsList;
	auto *controlsList = &mControlsOptionsList;
	auto *mainList = &mMainOptionsList;

	mf::GUI::AddWidget(mf::List::Create()
	->SetPosition(1, 10)->SetPositionPercentage(true, true)
	->SetSize(30, 80)->SetSizePercentage(true, true)
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetItemSpacing(20)
	->AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([graphicsList, audioList, controlsList, mainList](){
		if (*audioList)
			(*audioList)->SetDisabled(true);
		if (*controlsList)
			(*controlsList)->SetDisabled(true);
		if (*mainList)
			(*mainList)->SetDisabled(true);
		(*graphicsList)->SetDisabled(false);
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Graphics")
	->SetSize(200, 50)
	->SetTextPosition(15, 5))
	->AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([graphicsList, audioList, controlsList, mainList](){
		if (*audioList)
			(*audioList)->SetDisabled(true);
		if (*graphicsList)
			(*graphicsList)->SetDisabled(true);
		if (*mainList)
			(*mainList)->SetDisabled(true);
		(*controlsList)->SetDisabled(false);
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Controls")
	->SetSize(200, 50)
	->SetTextPosition(15, 5)));

	mf::GUI::AddWidget(mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png")
	->SetClickEvent([active, stateAction, nextState](){
		*active = false;
		*stateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
		*nextState = (uint8_t)eStates::MENU;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Back")
	->SetSize(110, 50)
	->SetTextPosition(15, 5)
	->SetPosition(1, 93)->SetPositionPercentage(true, true));

	mf::GUI::AddWidget((mOptionsContainer = mf::Container::Create())
	->SetPosition(40, 5)->SetPositionPercentage(true, true)
	->SetSize(50, 90)->SetSizePercentage(true, true)
	->SetBackground(sf::Color(255, 255, 255, 30)));

}

void	Options::InitOptionsControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}