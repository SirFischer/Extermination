/*
 * File: InitGraphicsMenu.cpp
 * Project: Extermination
 * File Created: Sunday, 7th November 2021 10:43:08 am
 * Author: Marek Fischer
 * -----
 * Last Modified: Sunday, 7th November 2021 4:40:34 pm
 * Modified By: Marek Fischer 
 * -----
 * Copyright - 2021 Deep Vertic
 */

#include "Options.hpp"

void	Options::InitGraphicsOptions()
{
	mGraphicsOptionsList = mf::List::Create()
	->SetBackgroundColor(sf::Color(0, 0, 0, 0))
	->SetSize(95, 95)->SetSizePercentage(true, true)
	->SetPosition(2.5, 2.5)->SetPositionPercentage(true, true);
	mOptionsContainer->AddWidget(mGraphicsOptionsList);
	mGraphicsOptionsList->SetDisabled(true);
	mf::Button *fullscreen = mf::Button::Create("assets/textures/Button_01.png", "assets/textures/Button_01_hover.png");
	fullscreen->SetTextFont("assets/fonts/AlfaSlabOne-Regular.ttf")
	->SetText("Fullscreen Off")
	->SetSize(275, 50)
	->SetTextPosition(10, 5)
	->SetClickEvent([this, fullscreen]() {
		this->mWindow->SetFullscreen(!this->mWindow->IsFullscreen());
		fullscreen->SetText(std::string("Fullscreen ") + (this->mWindow->IsFullscreen() ? "On" : "Off"));
	});
	mGraphicsOptionsList->AddWidget(fullscreen);
}
