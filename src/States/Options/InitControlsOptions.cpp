/*
 * File: InitControlsOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 5:48:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Thursday, 6th January 2022 8:32:10 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"
#include "Utils/Utils.hpp"


void	Options::InitButtonBinding(std::string pText, eAction pAction)
{
	auto container = mf::Container::Create();
	container->SetSize(100, 64)->SetSizePercentage(true, false);
	container->SetBackground(sf::Color::Transparent);
	mControlsOptionsList->AddWidget(container);
	auto text = mf::Text::Create();
	container->AddWidget(text);
	text->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	text->SetBackgroundColor(sf::Color::Transparent);
	text->SetText(pText);
	auto btn = mf::Button::Create();
	container->AddWidget(btn);
	btn->SetTextFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf"));
	btn->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	int32_t tmp  = -1;
	for (auto a : mEventHandler.GetBindingMap())
	{
		if (a.second == (uint32_t)pAction)
		{
			tmp = a.first;
			break;
		}
	}
	btn->SetText(mEventHandler.GetBindingNames()[tmp]);
	btn->SetSize(516, 64)->SetTextPosition(10, 5);
	btn->SetPosition(250, -15);
	btn->SetTextPosition(10, 5);
	Utils::initBtnHover(btn, &mResourceManager);
	eAction *tmpAction = &mActionToBind;
	bool	*tmpListen = &mListenToNextEvent;
	mf::Button **tmpBtn = &mButtonToBind;
	btn->SetClickEvent([pAction, tmpAction, tmpListen, btn, tmpBtn](){
		*tmpAction = pAction;
		*tmpListen = true;
		*tmpBtn = btn;
		btn->SetText("Press any key");
	});
}

void	Options::InitControlsOptions()
{
	if (mControlsOptionsList)
	{
		mOptionsContainer->RemoveWidget(mControlsOptionsList);
		mControlsOptionsList->ClearWidgets(true);
		delete mControlsOptionsList;
	}
	mControlsOptionsList = mf::List::Create()
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetSize(95, 95)->SetSizePercentage(true, true)
	->SetPosition(2.5, 2.5)->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mControlsOptionsList);
	mControlsOptionsList->SetDisabled(true);

	mf::Button *restoreDefaults = mf::Button::Create();
	restoreDefaults->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Restore defaults")
	->SetSize(300, 50)
	->SetTextPosition(10, 5)
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	Utils::initBtnHover(restoreDefaults, &mResourceManager);
	mControlsOptionsList->AddWidget(restoreDefaults);
	auto space = mf::Container::Create();
	space->SetSize(0, 50);
	space->SetBackground(sf::Color::Transparent);
	mControlsOptionsList->AddWidget(space);

	InitButtonBinding("Jump", eAction::JUMP);
	InitButtonBinding("Move left", eAction::MOVE_LEFT);
	InitButtonBinding("Move Right", eAction::MOVE_RIGHT);

	mf::Button *saveBtn = mf::Button::Create();
	mControlsOptionsList->AddWidget(saveBtn);
	saveBtn->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetText("Save")
	->SetTextPosition(10, 5);
	Utils::initBtnHover(saveBtn, &mResourceManager);
	saveBtn->SetClickEvent([](){
		std::cout << "saving to console...\n";
		Yuna::Core::Console::WriteBindingsToFile("assets/scripts/UserBindings.cfg");
	});

}
