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
	container->SetSize(100, 64);
	container->SetSizePercentage(true, false);
	container->GetBackground()->SetBackground(sf::Color::Transparent);
	mControlsOptionsList->AddWidget(container);
	auto text = mf::Text::Create();
	container->AddWidget(text);
	text->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	text->GetBackground()->SetBackground(sf::Color::Transparent);
	text->GetText()->SetString(pText);
	text->GetText()->SetColor(sf::Color::White);
	text->SetSize(250, 100);
	auto btn = mf::Button::Create();
	container->AddWidget(btn);
	btn->GetText()->LoadFont(*mResourceManager.LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf"));
	btn->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	int32_t tmp  = -1;
	for (auto a : mEventHandler.GetBindingMap())
	{
		if (a.second == (uint32_t)pAction)
		{
			tmp = a.first;
			break;
		}
	}
	btn->GetText()->SetString(mEventHandler.GetBindingNames()[tmp]);
	btn->GetText()->SetColor(sf::Color::White);
	btn->SetSize(516, 64);
	btn->GetText()->SetPos(sf::Vector2f(10, 5));
	btn->SetPosition(250, -15);
	Utils::initBtnHover(btn, &mResourceManager, &mHoverSound);
	eAction *tmpAction = &mActionToBind;
	bool	*tmpListen = &mListenToNextEvent;
	std::shared_ptr<mf::Button> *tmpBtn = &mButtonToBind;
	btn->SetClickEvent([pAction, tmpAction, tmpListen, btn, tmpBtn, clickSound = &mClickSound](){
		*tmpAction = pAction;
		*tmpListen = true;
		*tmpBtn = btn;
		btn->GetText()->SetString("Press any key");
		Utils::playClickSound(clickSound);
	});
}

void	Options::InitControlsOptions()
{
	if (mControlsOptionsList)
	{
		mOptionsContainer->RemoveWidget(mControlsOptionsList);
		mControlsOptionsList->ClearWidgets();
	}
	mControlsOptionsList = mf::List::Create();
	mControlsOptionsList->GetBackground()->SetBackground(sf::Color(0, 0, 0, 0));
	mControlsOptionsList->SetSize(95, 95);
	mControlsOptionsList->SetSizePercentage(true, true);
	mControlsOptionsList->SetPosition(2.5, 2.5);
	mControlsOptionsList->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mControlsOptionsList);
	mControlsOptionsList->SetDisabled(true);

	auto restoreDefaults = mf::Button::Create();
	restoreDefaults->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	restoreDefaults->GetText()->SetString("Restore defaults");
	restoreDefaults->SetSize(300, 50);
	restoreDefaults->GetText()->SetColor(sf::Color::White);
	restoreDefaults->GetText()->SetPos(sf::Vector2f(10, 5));
	restoreDefaults->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	Utils::initBtnHover(restoreDefaults, &mResourceManager, &mHoverSound);
	mControlsOptionsList->AddWidget(restoreDefaults);
	auto space = mf::Container::Create();
	space->SetSize(0, 50);
	space->GetBackground()->SetBackground(sf::Color::Transparent);
	mControlsOptionsList->AddWidget(space);

	InitButtonBinding("Jump", eAction::JUMP);
	InitButtonBinding("Move left", eAction::MOVE_LEFT);
	InitButtonBinding("Move Right", eAction::MOVE_RIGHT);
	InitButtonBinding("Use Primary", eAction::USE_ITEM_1);
	InitButtonBinding("Use Secondary", eAction::USE_ITEM_2);
	InitButtonBinding("Next Item", eAction::NEXT_ITEM);
	InitButtonBinding("Previous Item", eAction::PREVIOUS_ITEM);

	auto saveBtn = mf::Button::Create();
	mControlsOptionsList->AddWidget(saveBtn);
	saveBtn->GetText()->LoadFont("assets/fonts/AlfaSlabOne-Regular.ttf");
	saveBtn->GetBackground()->SetBackground(*mResourceManager.LoadTexture("assets/textures/button.png"));
	saveBtn->GetText()->SetString("Save");
	saveBtn->GetText()->SetColor(sf::Color::White);
	saveBtn->GetText()->SetPos(sf::Vector2f(10, 5));
	Utils::initBtnHover(saveBtn, &mResourceManager, &mHoverSound);
	saveBtn->SetClickEvent([clickSound = &mClickSound](){
		std::cout << "saving to console...\n";
		Yuna::Core::Console::WriteBindingsToFile("assets/scripts/UserBindings.cfg");
		Utils::playClickSound(clickSound);
	});

}
