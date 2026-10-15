/*
 * File: InitOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 7:54:51 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Saturday, 1st January 2022 2:22:57 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"
#include "Utils/Utils.hpp"

void	Options::InitOptionsItems()
{
	mf::GUI::ClearWidgets();


	auto btn = mf::Button::Create();
	btn->SetClickEvent([this, clickSound = &mClickSound](){
		if (this->mAudioOptionsList)
			this->mAudioOptionsList->SetDisabled(true);
		if (this->mControlsOptionsList)
			this->mControlsOptionsList->SetDisabled(true);
		if (this->mMainOptionsList)
			this->mMainOptionsList->SetDisabled(true);
		(this->mGraphicsOptionsList)->SetDisabled(false);
		Utils::playClickSound(clickSound);
	});
	btn->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btn->GetText()->SetString("Graphics");
	btn->GetText()->SetColor(sf::Color::White);
	btn->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btn->SetSize(200, 50);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	Utils::initBtnHover(btn, &mResourceManager, &mHoverSound);

	auto btn2 = mf::Button::Create();
	btn2->SetClickEvent([this](){
		if (this->mAudioOptionsList)
			this->mAudioOptionsList->SetDisabled(true);
		if (this->mGraphicsOptionsList)
			this->mGraphicsOptionsList->SetDisabled(true);
		if (this->mMainOptionsList)
			this->mMainOptionsList->SetDisabled(true);
		this->mControlsOptionsList->SetDisabled(false);
		Utils::playClickSound(&mClickSound);
	});
	btn2->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btn2->GetText()->SetString("Controls");
	btn2->GetText()->SetColor(sf::Color::White);
	btn2->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btn2->SetSize(200, 50);
	btn2->GetText()->SetPos(sf::Vector2f(10, 5));
	Utils::initBtnHover(btn2, &mResourceManager, &mHoverSound);


	auto list = mf::List::Create();
	list->SetPosition(1, 10);
	list->SetPositionPercentage(true, true);
	list->SetSize(30, 80);
	list->SetSizePercentage(true, true);
	list->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	list->SetItemSpacing(20);
	list->AddWidget(btn);
	list->AddWidget(btn2);
	mf::GUI::AddWidget(list);

	auto btn3 = mf::Button::Create();
	btn3->SetClickEvent([this, clickSound = &mClickSound](){
		this->mActive = false;
		this->mStateAction = Yuna::Core::eStateControls::PREVIOUS_STATE;
		this->mNextState = (uint8_t)eStates::MENU;
		Utils::playClickSound(clickSound);
	});
	btn3->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf").get());
	btn3->GetText()->SetString("Back");
	btn3->GetText()->SetColor(sf::Color::White);
	btn3->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	btn3->SetSize(110, 50);
	btn3->GetText()->SetPos(sf::Vector2f(10, 5));
	btn3->SetPosition(1, 93);
	btn3->SetPositionPercentage(true, true);
	Utils::initBtnHover(btn3, &mResourceManager, &mHoverSound);

	mf::GUI::AddWidget(btn3);
	
	mOptionsContainer = mf::Container::Create();
	mOptionsContainer->SetPosition(40, 5);
	mOptionsContainer->SetPositionPercentage(true, true);
	mOptionsContainer->SetSize(50, 90);
	mOptionsContainer->SetSizePercentage(true, true);
	mOptionsContainer->GetBackground()->SetBackground(sf::Color(255, 255, 255, 30));
	mf::GUI::AddWidget(mOptionsContainer);

}

void	Options::InitOptionsControls()
{
	mEventHandler.BindKey(sf::Keyboard::Tab, (uint32_t)eAction::CONSOLE_TOGGLE);
	mEventHandler.BindKey(sf::Keyboard::Enter, (uint32_t)eAction::CONSOLE_CONFIRM);
	mEventHandler.BindKey(sf::Keyboard::Up, (uint32_t)eAction::CONSOLE_NEXT_IN_HISTORY);
	mEventHandler.BindKey(sf::Keyboard::Down, (uint32_t)eAction::CONSOLE_PREVIOUS_IN_HISTORY);
}