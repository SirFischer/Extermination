/*
 * File: InitControlsOptions.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 5:48:13 pm
 * Author: Marek Fischer
 * -----
 * Last Modified: Tuesday, 28th December 2021 6:41:37 am
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */
#include "Options.hpp"

void	Options::InitControlsOptions()
{
	mControlsOptionsList = mf::List::Create()
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetSize(95, 95)->SetSizePercentage(true, true)
	->SetPosition(2.5, 2.5)->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mControlsOptionsList);
	mControlsOptionsList->SetDisabled(true);

	mf::Button *restoreDefaults = mf::Button::Create();
	restoreDefaults->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Restore defaults")
	->SetSize(375, 50)
	->SetTextPosition(10, 5)
	->SetBackground(*mResourceManager.LoadTexture("assets/textures/Button_01.png"));
	mControlsOptionsList->AddWidget(restoreDefaults);
}
