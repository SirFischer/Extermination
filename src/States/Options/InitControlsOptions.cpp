/*
 * File: InitControlsOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 5:48:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Wednesday, 22nd June 2022 6:15:31 am
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
	text->SetSize(250, 100);
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
	Utils::initBtnHover(btn, &mResourceManager, &mHoverSound);
	eAction *tmpAction = &mActionToBind;
	bool	*tmpListen = &mListenToNextEvent;
	mf::Button **tmpBtn = &mButtonToBind;
	btn->SetClickEvent([pAction, tmpAction, tmpListen, btn, tmpBtn, clickSound = &mClickSound](){
		*tmpAction = pAction;
		*tmpListen = true;
		*tmpBtn = btn;
		btn->SetText("Press any key");
		Utils::playClickSound(clickSound);
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
	Utils::initBtnHover(restoreDefaults, &mResourceManager, &mHoverSound);
	mControlsOptionsList->AddWidget(restoreDefaults);
	auto space = mf::Container::Create();
	space->SetSize(0, 50);
	space->SetBackground(sf::Color::Transparent);
	mControlsOptionsList->AddWidget(space);

	InitButtonBinding("Jump", eAction::JUMP);
	InitButtonBinding("Move left", eAction::MOVE_LEFT);
	InitButtonBinding("Move Right", eAction::MOVE_RIGHT);
	InitButtonBinding("Use Primary", eAction::USE_ITEM_1);
	InitButtonBinding("Use Secondary", eAction::USE_ITEM_2);
	InitButtonBinding("Next Item", eAction::NEXT_ITEM);
	InitButtonBinding("Previous Item", eAction::PREVIOUS_ITEM);

	mf::Button *saveBtn = mf::Button::Create();
	mControlsOptionsList->AddWidget(saveBtn);
	saveBtn->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"))
	->SetText("Save")
	->SetTextPosition(10, 5);
	Utils::initBtnHover(saveBtn, &mResourceManager, &mHoverSound);
	saveBtn->SetClickEvent([clickSound = &mClickSound](){
		std::cout << "saving to console...\n";
		Yuna::Core::Console::WriteBindingsToFile("assets/scripts/UserBindings.cfg");
		Utils::playClickSound(clickSound);
	});

}
