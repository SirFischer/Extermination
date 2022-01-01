/*
 * File: InitOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 7:54:51 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 10:59:53 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"
#include "Utils/Utils.hpp"

void	Options::InitOptionsItems()
{
	mf::GUI::ClearWidgets();


	auto btn = mf::Button::Create()
	->SetClickEvent([this](){
		if (this->mAudioOptionsList)
			this->mAudioOptionsList->SetDisabled(true);
		if (this->mControlsOptionsList)
			this->mControlsOptionsList->SetDisabled(true);
		if (this->mMainOptionsList)
			this->mMainOptionsList->SetDisabled(true);
		(this->mGraphicsOptionsList)->SetDisabled(false);
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Graphics")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/Button_01.png"))
	->SetSize(200, 50)
	->SetTextPosition(15, 5);
	Utils::initBtnHover(btn, &mResourceManager);

	auto btn2 = mf::Button::Create()
	->SetClickEvent([this](){
		if (this->mAudioOptionsList)
			this->mAudioOptionsList->SetDisabled(true);
		if (this->mGraphicsOptionsList)
			this->mGraphicsOptionsList->SetDisabled(true);
		if (this->mMainOptionsList)
			this->mMainOptionsList->SetDisabled(true);
		this->mControlsOptionsList->SetDisabled(false);
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Controls")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/Button_01.png"))
	->SetSize(200, 50)
	->SetTextPosition(15, 5);
	Utils::initBtnHover(btn2, &mResourceManager);


	mf::GUI::AddWidget(mf::List::Create()
	->SetPosition(1, 10)->SetPositionPercentage(true, true)
	->SetSize(30, 80)->SetSizePercentage(true, true)
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetItemSpacing(20)
	->AddWidget(btn)
	->AddWidget(btn2));

	auto btn3 = mf::Button::Create()
	->SetClickEvent([this](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
		this->mNextState = (uint8_t)eStates::MENU;
	})
	->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get())
	->SetText("Back")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/Button_01.png"))
	->SetSize(110, 50)
	->SetTextPosition(15, 5)
	->SetPosition(1, 93)->SetPositionPercentage(true, true);

	Utils::initBtnHover(btn3, &mResourceManager);

	mf::GUI::AddWidget(btn3);
	
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